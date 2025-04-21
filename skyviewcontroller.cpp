#include "MessierCatalog.h" // Include the generated header
#include "skyviewcontroller.h"
#include <QtMath>
#include <QVariantMap>

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
      m_declination(0.0) // Default 50 degree field of view
{
    // Connect sensor signals
    connect(m_sensorBridge, &IOSSensorBridge::azimuthChanged, this, &SkyViewController::onAzimuthChanged);
    connect(m_sensorBridge, &IOSSensorBridge::pitchChanged, this, &SkyViewController::onPitchChanged);
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

/*
// Updated loadDefaultDSOs method that uses the converted MessierCatalog
void SkyViewController::loadDefaultDSOs()
{
    // Clear existing objects
    m_dsoObjects.clear();
    
    // Load data from the C++ MessierCatalog
    for (const MessierObject& messierObj : MessierCatalog) {
        DSOObject dso;
        
        // Set basic properties
        dso.name = QString::fromStdString(messierObj.name);
        if (!messierObj.commonName.empty()) {
            dso.name += " - " + QString::fromStdString(messierObj.commonName);
        }
        
        dso.rightAscension = messierObj.raHours;
        dso.declination = messierObj.decDegrees;
        
        // Get the larger dimension for scaling
        dso.angularSize = std::max(messierObj.sizeArcminWidth, messierObj.sizeArcminHeight);
        
        // Set image URL based on Messier number (e.g., "M31" -> "m31.jpg")
        QString id = QString::fromStdString(messierObj.name).toLower();
        dso.imageUrl = QUrl("qrc:/images/" + id + ".jpg");
        
        // Add to our collection
        m_dsoObjects.append(dso);
        
        qDebug() << "Loaded" << dso.name << "RA:" << dso.rightAscension 
                 << "Dec:" << dso.declination << "Size:" << dso.angularSize;
    }
    
    qDebug() << "Loaded" << m_dsoObjects.size() << "Messier objects";
    
    // Update the UI
    updateVisibleDSOs();
}
*/

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
void SkyViewController::onPitchChanged(double pitch)
{
    // Based on observed behavior:
    // - Pitch = 0° when flat on desk (pointing down), should be altitude = -90°
    // - Pitch = 90° when pointing at horizon, should be altitude = 0°
    // - Pitch = 180° when pointing straight up, should be altitude = 90°
    
    double newAltitude;
    
    // Normalize pitch to 0-180 range if needed
    if (pitch < 0) {
        pitch += 360;
    }
    
    // Simple linear transformation from device orientation to astronomical altitude
    if (pitch <= 180) {
        newAltitude = -90 + pitch;
    } else {
        // Handle the case where pitch wraps around (if device reports >180)
        newAltitude = 270 - pitch;
    }
    
    // Keep altitude in valid range (-90 to +90)
    newAltitude = qBound(-90.0, newAltitude, 90.0);
    
    if (qAbs(newAltitude - m_altitude) > 1.0) {
        m_altitude = newAltitude;
        emit altitudeChanged(m_altitude);
        updateVisibleDSOs();
    }
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

/*
void SkyViewController::updateVisibleDSOs()
{
   if (m_location == nullptr) {
        qDebug() << "Skipping updateVisibleDSOs() - waiting for valid location";
        return;
    }

    // Clear the current list of visible objects
    m_visibleDSOs.clear();
    
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
    
    // Use a wide field of view for testing
    const double testFieldOfView = 50.0; // 90 degrees - large portion of the sky
    
    // Check each DSO to see if it should be displayed
    for (const DSOObject &dso : m_dsoObjects) {
        double dsoAzimuth, dsoAltitude;
        
        // Convert equatorial coordinates to horizontal using our calculator
        m_astronomyCalculator.equatorialToHorizontal(dso.rightAscension, dso.declination, &dsoAzimuth, &dsoAltitude);
        
        // Calculate angular distance between viewing direction and DSO
        double angularSeparation = m_astronomyCalculator.angularSeparation(
            m_azimuth, m_altitude, dsoAzimuth, dsoAltitude);
        
        // Scale factor based on angular size - normalize to display well
        // Minimum size ensures small objects are still visible
        // Angular sizes in catalog are in arcminutes (1/60 of a degree)
        const double minSize = 30.0;  // Minimum display size (pixels)
        const double maxSize = 300.0; // Maximum display size (pixels)
        
        // Convert arcminutes to degrees and scale
        double sizeScaleFactor = dso.angularSize / 60.0 * 10.0; // Scale factor
        // Apply log scaling for better distribution of sizes
        double displaySize = 400.0; // qMin(maxSize, minSize + 50.0 * log10(1.0 + sizeScaleFactor));
        
        // If the DSO is within our wide field of view, add it to visible list
        if (angularSeparation <= testFieldOfView / 2.0) {
            QVariantMap dsoMap;
            dsoMap["name"] = dso.name;
            dsoMap["ra"] = dso.rightAscension;
            dsoMap["dec"] = dso.declination;
            dsoMap["imageUrl"] = dso.imageUrl;
            dsoMap["azimuth"] = dsoAzimuth;
            dsoMap["altitude"] = dsoAltitude;
            dsoMap["angularSize"] = dso.angularSize;  // Original size in arcminutes
            dsoMap["displaySize"] = displaySize;      // Scaled size for display
            
            // Calculate position in view coordinates (-1 to 1 range)
            // Calculate azimuth difference properly across the 0/360 boundary
            double azDiff = dsoAzimuth - m_azimuth;
            if (azDiff > 180) azDiff -= 360;
            if (azDiff < -180) azDiff += 360;
            
            // Convert angular difference to normalized screen coordinates
            double normAzDiff = -azDiff / (testFieldOfView / 2.0);
            double normAltDiff = -(dsoAltitude - m_altitude) / (testFieldOfView / 2.0);
            
            // Clamp values to ensure they're in display range (-0.9 to 0.9)
            normAzDiff = qBound(-0.9, normAzDiff, 0.9);
            normAltDiff = qBound(-0.9, normAltDiff, 0.9);
            
            dsoMap["viewX"] = normAzDiff;
            dsoMap["viewY"] = normAltDiff;
            
            // For debugging, add angular separation
            dsoMap["angularDistance"] = angularSeparation;
            
            m_visibleDSOs.append(dsoMap);
        }
    }
    
    emit visibleDSOsChanged();
}
*/

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
    
    // Use a wide field of view for testing
    const double testFieldOfView = 120.0; // 120 degrees - large portion of the sky
    
    // Check each DSO to see if it should be displayed
    for (const DSOObject &dso : m_dsoObjects) {
        double dsoAzimuth, dsoAltitude;
        
        // Convert equatorial coordinates to horizontal using our calculator
        m_astronomyCalculator.equatorialToHorizontal(dso.rightAscension, dso.declination, &dsoAzimuth, &dsoAltitude);
        
        // Calculate angular distance between viewing direction and DSO
        double angularSeparation = m_astronomyCalculator.angularSeparation(
            m_azimuth, m_altitude, dsoAzimuth, dsoAltitude);
        
        // If the DSO is within our wide field of view, add it to visible list
        if (angularSeparation <= testFieldOfView / 2.0) {
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
            
            // Use the exact display size from the catalog if available,
            // otherwise use a reasonable default
            int displaySize = dso.displaySize > 0 ? dso.displaySize : 60;
            
            // Use the distance from center of view to adjust size slightly
            // Objects at the edge of view are slightly smaller 
            double distanceFactor = 1.0 - (angularSeparation / testFieldOfView);
            displaySize = static_cast<int>(displaySize * (0.8 + 0.2 * distanceFactor));
            
            dsoMap["displaySize"] = displaySize;
            
            // Calculate position in view coordinates (-1 to 1 range)
            // Calculate azimuth difference properly across the 0/360 boundary
            double azDiff = dsoAzimuth - m_azimuth;
            if (azDiff > 180) azDiff -= 360;
            if (azDiff < -180) azDiff += 360;
            
            // Convert angular difference to normalized screen coordinates
            double normAzDiff = -azDiff / (testFieldOfView / 2.0);
            double normAltDiff = -(dsoAltitude - m_altitude) / (testFieldOfView / 2.0);
            
            // Clamp values to ensure they're in display range (-0.9 to 0.9)
            normAzDiff = qBound(-0.9, normAzDiff, 0.9);
            normAltDiff = qBound(-0.9, normAltDiff, 0.9);
            
            dsoMap["viewX"] = normAzDiff;
            dsoMap["viewY"] = normAltDiff;
            
            // For debugging, add some info
            dsoMap["angularDistance"] = angularSeparation;
            dsoMap["scaleFactor"] = dso.scaleFactor;
            
            m_visibleDSOs.append(dsoMap);
        }
    }
    
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
        
        qDebug() << "Loaded DSO:" << dso.name 
                 << "RA:" << dso.rightAscension 
                 << "Dec:" << dso.declination 
                 << "Size:" << dso.angularSize
                 << "Display Size:" << dso.displaySize;
    }
    
    qDebug() << "Loaded" << m_dsoObjects.size() << "Messier objects";
    
    // Update visible objects based on current orientation
    updateVisibleDSOs();
}
