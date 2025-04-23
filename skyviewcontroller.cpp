#include "MessierCatalog.h" // Include the generated header
#include "skyviewcontroller.h"
#include <QtMath>
#include <QVariantMap>
#include <QMatrix4x4>
#include <QMatrix3x3>
#include <QVector3D>

SkyViewController::SkyViewController(QObject *parent)
    : QObject(parent),
      m_sensorBridge(new IOSSensorBridge(this)),
      m_azimuth(0.0),
      m_altitude(0.0),
      m_manualLocationMode(false),
      m_locationAccuracy(0.0),
      m_locationStatus("GPS initializing"),
      m_fieldOfView(50.0), // Default 50 degree field of view
      m_rightAscension(0.0),
      m_declination(0.0)
{
    // Connect sensor signals
    connect(m_sensorBridge, &IOSSensorBridge::azimuthChanged, this, &SkyViewController::onAzimuthChanged);
    connect(m_sensorBridge, &IOSSensorBridge::rotationMatrixChanged, this, &SkyViewController::onRotationMatrixChanged);
    connect(m_sensorBridge, &IOSSensorBridge::locationChanged, this, &SkyViewController::onLocationChanged);
    connect(m_sensorBridge, &IOSSensorBridge::locationErrorOccurred, this, &SkyViewController::onLocationError);
    connect(m_sensorBridge, &IOSSensorBridge::locationAuthorizationChanged, this, &SkyViewController::onLocationAuthorizationChanged);
    connect(m_sensorBridge, &IOSSensorBridge::locationMetadataChanged, this, &SkyViewController::onLocationMetadataChanged);
    
    // Load some default DSOs
    loadDefaultDSOs();
}

SkyViewController::~SkyViewController()
{
    delete m_location;
    stopSensors();
}

double SkyViewController::azimuth() const
{
    return m_azimuth;
}

double SkyViewController::altitude() const
{
    return m_altitude;
}

QVariantList SkyViewController::visibleDSOs() const
{
    return m_visibleDSOs;
}

GeoCoordinate SkyViewController::location() const
{
    // Set default location (can be updated with GPS)
  return (m_location != nullptr ?
	  *m_location :
	  GeoCoordinate(0, 0)); // Off Africa coast
}

void SkyViewController::setLocation(const GeoCoordinate &location)
{
    bool changed = true;
    
    if (m_location != nullptr) {
        changed = (*m_location != location);
    }
    
    if (changed) {
        // Delete old location if it exists
        delete m_location;
        
        // Create new location
        m_location = new GeoCoordinate(location);
        
        // If we're manually setting the location, switch to manual mode
        if (!m_manualLocationMode) {
            m_manualLocationMode = true;
            emit gpsStatusChanged(false);
        }
        
        emit locationChanged();
        updateVisibleDSOs();
    }
}
  
bool SkyViewController::isGPSEnabled() const
{
    return !m_manualLocationMode && m_sensorBridge->isLocationAuthorized();
}

double SkyViewController::locationAccuracy() const
{
    return m_locationAccuracy;
}

QString SkyViewController::locationStatus() const
{
    return m_locationStatus;
}

void SkyViewController::setGPSAccuracy(int accuracy)
{
    IOSSensorBridge::GPSAccuracy gpsAccuracy;
    
    switch (accuracy) {
        case 0:
            gpsAccuracy = IOSSensorBridge::GPSAccuracy::Best;
            break;
        case 1:
            gpsAccuracy = IOSSensorBridge::Navigation;
            break;
        case 2:
            gpsAccuracy = IOSSensorBridge::Balanced;
            break;
        case 3:
            gpsAccuracy = IOSSensorBridge::GPSAccuracy::LowPower;
            break;
        default:
            gpsAccuracy = IOSSensorBridge::Best;
    }
    
    m_sensorBridge->setGPSAccuracy(gpsAccuracy);
}

void SkyViewController::useManualLocation(bool manual)
{
    if (m_manualLocationMode != manual) {
        m_manualLocationMode = manual;
        
        if (!manual) {
            // Switching to GPS mode, check if we have a recent GPS location
            GeoCoordinate lastGpsLocation = m_sensorBridge->location();
            if (lastGpsLocation.isValid()) {
                m_location = &lastGpsLocation;
                emit locationChanged();
                updateVisibleDSOs();
            }
        }
        
        emit gpsStatusChanged(!manual);
        
        // Update status text
        if (manual) {
            m_locationStatus = "Manual location";
        } else {
            m_locationStatus = "Using GPS";
        }
        emit locationStatusChanged(m_locationStatus);
    }
}

void SkyViewController::requestLocationPermission()
{
    // This will trigger the iOS permission dialog
    startSensors();
}

void SkyViewController::addCustomDSO(const QString &name, double ra, double dec, const QUrl &imageUrl, double size,
				     int croppedWidth, int croppedHeight, double scaleFactor)
{
    // Add a custom DSO to the database
    DSOObject dso;
    dso.name = name;
    dso.rightAscension = ra;
    dso.declination = dec;
    dso.imageUrl = imageUrl;
    
    m_dsoObjects.append(dso);
    updateVisibleDSOs();
}

void SkyViewController::startSensors()
{
    m_sensorBridge->startSensors();
}

void SkyViewController::stopSensors()
{
    m_sensorBridge->stopSensors();
}

void SkyViewController::onAzimuthChanged(double azimuth)
{
    // Update compass direction
    m_azimuth = azimuth;
    emit azimuthChanged(m_azimuth);
    updateVisibleDSOs();
}

void SkyViewController::onRotationMatrixChanged(const RotationMatrix& matrix) {
    m_rotationMatrix = matrix;
    
    // CoreMotion rotation matrix represents device orientation in a North-East-Down reference frame
    
    // Extract view direction - using negative Z axis of device in world space (third row)
    // We negate because we're looking through the back of the device
    float x = -matrix.m31;  // Device Z axis X component in world
    float y = -matrix.m32;  // Device Z axis Y component in world
    float z = -matrix.m33;  // Device Z axis Z component in world
    
    // Normalize the vector
    float length = sqrt(x*x + y*y + z*z);
    if (length > 0.0001f) {
        x /= length;
        y /= length;
        z /= length;
    }
    
    // Debug output
    // qDebug() << "Vector:" << x << y << z;
    
    // Calculate azimuth and altitude from direction vector
    
    // Azimuth is angle in x-y plane (from North, clockwise)
    double newAzimuth = qRadiansToDegrees(qAtan2(y, x));
    if (newAzimuth < 0) 
        newAzimuth += 360.0;
    
    // Altitude is angle from horizon (positive when pointing up)
    // We need to invert the z value to get the correct sign
    double newAltitude = qRadiansToDegrees(qAsin(z));  // Changed from -z to z
    
    // Only update if changed significantly
    if (qAbs(newAltitude - m_altitude) > 0.5) {
        m_altitude = newAltitude;
        emit altitudeChanged(m_altitude);
    }
    
    if (qAbs(newAzimuth - m_azimuth) > 0.5) {
        m_azimuth = newAzimuth;
        emit azimuthChanged(m_azimuth);
    }
    
    updateVisibleDSOs();
}

void SkyViewController::onLocationChanged(GeoCoordinate location)
{
    // Only update location if we're not in manual mode
    if (!m_manualLocationMode) {
        bool isFirstLocation = (m_location == nullptr);
        
        // Delete old location if it exists
        delete m_location;
        
        // Create new location
        m_location = new GeoCoordinate(location);
        
        // First location update
        if (isFirstLocation) {
            m_locationStatus = "GPS location acquired";
            emit locationStatusChanged(m_locationStatus);
        }
        
        emit locationChanged();
        updateVisibleDSOs();
    }
}

void SkyViewController::onLocationError(const QString &errorMessage)
{
    m_locationStatus = "GPS error: " + errorMessage;
    emit locationStatusChanged(m_locationStatus);
}

void SkyViewController::onLocationAuthorizationChanged(bool authorized)
{
    if (authorized) {
        m_locationStatus = "GPS authorized";
    } else {
        m_locationStatus = "GPS not authorized";
    }
    
    emit locationStatusChanged(m_locationStatus);
    emit gpsStatusChanged(authorized && !m_manualLocationMode);
}

void SkyViewController::onLocationMetadataChanged()
{
    m_locationAccuracy = m_sensorBridge->locationAccuracy();
    
    // Update status with accuracy information
    if (!m_manualLocationMode) {
        if (m_locationAccuracy > 0) {
            m_locationStatus = QString("GPS accuracy: %1 m").arg(m_locationAccuracy, 0, 'f', 1);
        } else {
            m_locationStatus = "GPS active";
        }
        emit locationStatusChanged(m_locationStatus);
    }
    
    emit locationMetadataChanged();
}

// Now implement the getters in skyviewcontroller.cpp:

double SkyViewController::rightAscension() const
{
    return m_rightAscension;
}

double SkyViewController::declination() const
{
    return m_declination;
}

QString SkyViewController::formattedRA() const
{
    // Format RA as HH:MM:SS
    int hours = static_cast<int>(m_rightAscension);
    double minutesDecimal = (m_rightAscension - hours) * 60.0;
    int minutes = static_cast<int>(minutesDecimal);
    double seconds = (minutesDecimal - minutes) * 60.0;
    
    return QString("%1h %2m %3s").arg(hours, 2, 10, QChar('0'))
                                .arg(minutes, 2, 10, QChar('0'))
                                .arg(static_cast<int>(seconds), 2, 10, QChar('0'));
}

QString SkyViewController::formattedDEC() const
{
    // Format DEC as DD°MM'SS"
    bool isNegative = m_declination < 0;
    double absDec = qAbs(m_declination);
    int degrees = static_cast<int>(absDec);
    double minutesDecimal = (absDec - degrees) * 60.0;
    int minutes = static_cast<int>(minutesDecimal);
    double seconds = (minutesDecimal - minutes) * 60.0;
    
    QString sign = isNegative ? "-" : "+";
    return QString("%1%2° %3' %4\"").arg(sign)
                                   .arg(degrees, 2, 10, QChar('0'))
                                   .arg(minutes, 2, 10, QChar('0'))
                                   .arg(static_cast<int>(seconds), 2, 10, QChar('0'));
}

// Updated updateVisibleDSOs method with proper horizon filtering
// This should be placed in skyviewcontroller.cpp

void SkyViewController::updateVisibleDSOs()
{
    // Clear the current list of visible objects
    m_visibleDSOs.clear();
    
    // Skip if location isn't ready yet
    if (m_location == nullptr) {
        qDebug() << "Skipping updateVisibleDSOs() - waiting for valid location";
        return;
    }
    
    // Update astronomy calculator with current time and location
    m_astronomyCalculator.setLocation(*m_location);
    m_astronomyCalculator.setDateTime(QDateTime::currentDateTimeUtc());
    
    // Calculate the RA and DEC of the center of view
    double raJ2000, decJ2000, hourAngle;
    m_astronomyCalculator.horizontalToJ2000(m_azimuth, m_altitude, &raJ2000, &decJ2000, &hourAngle);

    // Update RA and DEC if they've changed significantly
    if (qAbs(raJ2000 - m_rightAscension) > 0.01 || qAbs(decJ2000 - m_declination) > 0.01) {
        m_rightAscension = raJ2000;
        m_declination = decJ2000;
        emit rightAscensionChanged(m_rightAscension);
        emit declinationChanged(m_declination);
    }
    
    // Debug current viewing direction
    // qDebug() << "Current view direction: Azimuth" << m_azimuth << "Altitude" << m_altitude;
    
    // Check each DSO to see if it should be displayed
    for (const DSOObject &dso : m_dsoObjects) {
        double dsoAzimuth, dsoAltitude;
        
        // Convert equatorial coordinates to horizontal using our calculator
        m_astronomyCalculator.equatorialToHorizontal(dso.rightAscension, dso.declination, &dsoAzimuth, &dsoAltitude);
        
        // If debugging a specific object, output its coordinates
        if (dso.name.contains("M0")) {
	  qDebug() << dso.name << " calculated position:"
                     << "Az:" << dsoAzimuth
                     << "Alt:" << dsoAltitude;
        }
        
        // Calculate angular distance between viewing direction and DSO
        double angularSeparation = m_astronomyCalculator.angularSeparation(
            m_azimuth, m_altitude, dsoAzimuth, dsoAltitude);
        
        // Transform the sky coordinates to screen coordinates
        
        // 1. First, determine if object is in the field of view
        if (angularSeparation > m_fieldOfView / 2.0) {
            continue; // Skip objects outside the field of view
        }
        
        // 2. Create the data map for this object
        QVariantMap dsoMap;
        dsoMap["name"] = dso.name;
        dsoMap["ra"] = dso.rightAscension;
        dsoMap["dec"] = dso.declination;
        dsoMap["imageUrl"] = dso.imageUrl;
        dsoMap["azimuth"] = dsoAzimuth;
        dsoMap["altitude"] = dsoAltitude;
        dsoMap["angularSize"] = dso.angularSize;         // Original size in arcminutes
        dsoMap["croppedWidth"] = dso.croppedWidth;       // Cropped width in pixels 
        dsoMap["croppedHeight"] = dso.croppedHeight;     // Cropped height in pixels
        
        // 3. Determine display size
        int displaySize = dso.displaySize > 0 ? dso.displaySize : 60;
        
        // Use the distance from center of view to adjust size slightly
        // Objects at the edge of view are slightly smaller 
        double distanceFactor = 1.0 - (angularSeparation / m_fieldOfView);
        displaySize = static_cast<int>(displaySize * (0.8 + 0.2 * distanceFactor));
        
        dsoMap["displaySize"] = displaySize;
        
        // 4. Calculate screen position
        // Calculate azimuth difference properly across the 0/360 boundary
        double azDiff = dsoAzimuth - m_azimuth;
        if (azDiff > 180) azDiff -= 360;
        if (azDiff < -180) azDiff += 360;
        
        // Convert angular difference to normalized screen coordinates
        double normAzDiff = -azDiff / (m_fieldOfView / 2.0);
        
        // For altitude, we need to map objects differently:
        // - When we look at horizon (alt = 0), horizon should be at bottom of screen
        // - When we look up (alt > 0), objects above horizon move up the screen
        // - When we look down (alt < 0), objects below horizon would be visible
        
        // Calculate normalized altitude difference
        double normAltDiff;
        
        // This approach keeps the horizon at the bottom of the screen
        // regardless of where the user is looking
        if (m_altitude <= 0) {
            // When looking at or below horizon
            normAltDiff = -dsoAltitude / (m_fieldOfView / 2.0);
        } else {
            // When looking above horizon
            normAltDiff = -(dsoAltitude - m_altitude) / (m_fieldOfView / 2.0);
        }
        
        // Only include objects above the horizon or with special visibility flag
        if (dsoAltitude < -20) {
            // Skip objects well below horizon
            continue;
        }
        
        // Clamp values to ensure they're in display range (-0.9 to 0.9)
        normAzDiff = qBound(-0.9, normAzDiff, 0.9);
        normAltDiff = qBound(-0.9, normAltDiff, 0.9);
        
        dsoMap["viewX"] = normAzDiff;
        dsoMap["viewY"] = normAltDiff;
        
        // For debugging, add some info
        dsoMap["angularDistance"] = angularSeparation;
        
        // Add to the list of visible objects
        m_visibleDSOs.append(dsoMap);
    }
    
    // qDebug() << "Showing" << m_visibleDSOs.size() << "objects";
    emit visibleDSOsChanged();
}

// Updated loadDefaultDSOs to use additional fields
void SkyViewController::loadDefaultDSOs()
{
    // Clear existing objects
    m_dsoObjects.clear();
    
    // Load data from MessierCatalog
    for (const auto& messierObj : MessierCatalog) {
        DSOObject dso;
        dso.name = QString::fromStdString(messierObj.name);
        
        // Add common name if available
        if (!messierObj.commonName.empty()) {
            dso.name += " - " + QString::fromStdString(messierObj.commonName);
        }
        
        dso.rightAscension = messierObj.raHours;
        dso.declination = messierObj.decDegrees;
        
        // Use the larger of width/height for the angular size
        dso.angularSize = std::max(messierObj.sizeArcminWidth, messierObj.sizeArcminHeight);
        
        // Add the cropping information
        dso.croppedWidth = messierObj.croppedWidth;
        dso.croppedHeight = messierObj.croppedHeight;
        dso.scaleFactor = messierObj.scaleFactor;
        dso.displaySize = messierObj.displaySize;
        
        // Use our embedded image provider URL format
        QString id = QString::fromStdString(messierObj.name).toLower();
        dso.imageUrl = QUrl("qrc:/images/" + id + ".jpg");
        
        // Add to the collection
        m_dsoObjects.append(dso);
	/*        
        qDebug() << "Loaded DSO:" << dso.name 
                 << "RA:" << dso.rightAscension 
                 << "Dec:" << dso.declination 
                 << "Size:" << dso.angularSize
                 << "Display Size:" << dso.displaySize;
	*/
    }
    
    qDebug() << "Loaded" << m_dsoObjects.size() << "Messier objects";
    
    // Update visible objects based on current orientation
    updateVisibleDSOs();
}

