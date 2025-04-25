#include "SolarSystemCalculator.h"
#include "skyviewcontroller.h"
#include "jpl.h"
#include <QDebug>
#include <QVector3D>
#include <QtMath>
#include <QUrl>

// Constants
const double PI = M_PI;
const double TWO_PI = M_PI * 2.0;
const double DEG_TO_RAD = M_PI / 180.0;
const double RAD_TO_DEG = 180.0 / M_PI;
const double AU_TO_KM = 149597870.7; // km
const double JD_J2000 = 2451545.0;

SolarSystemCalculator::SolarSystemCalculator(SkyViewController* parent)
    : QObject(parent)
    , m_controller(parent)
    , m_fieldOfView(50.0)
{
}

SolarSystemCalculator::~SolarSystemCalculator()
{
}

void SolarSystemCalculator::initializePlanets()
{
    // Clear any existing objects
    m_objects.clear();

    SolarSystemObject m_sunObject;
    m_sunObject.id = 0;
    m_sunObject.name = "Sun";
    m_sunObject.magnitude = -26.74;
    m_sunObject.angularSize = 1919.26; // arcseconds (approx 31.6 arcminutes at 1 AU)
    m_sunObject.imageUrl = QUrl("qrc:/images/sun.jpg");
    m_objects.append(m_sunObject);

    SolarSystemObject m_moonObject;
    m_moonObject.id = 10;
    m_moonObject.name = "Moon";
    m_moonObject.magnitude = -12.74;
    m_moonObject.angularSize = 1800.0; // arcseconds (approx 30 arcminutes, varies with distance)
    m_moonObject.imageUrl = QUrl("qrc:/images/moon.jpg");
    m_objects.append(m_moonObject);
    
    // Mercury - J2000 elements
    SolarSystemObject mercury;
    mercury.id = 1;
    mercury.name = "Mercury";
    mercury.angularSize = 6.74; // arcseconds at 1 AU
    mercury.magnitude = -0.6;
    mercury.imageUrl = QUrl("qrc:/images/mercury.jpg");
    m_objects.append(mercury);

    // Venus - J2000 elements
    SolarSystemObject venus;
    venus.id = 2;
    venus.name = "Venus";
    venus.angularSize = 16.92; // arcseconds at 1 AU
    venus.magnitude = -4.6;
    venus.imageUrl = QUrl("qrc:/images/venus.jpg");
    m_objects.append(venus);

    // Mars - J2000 elements
    SolarSystemObject mars;
    mars.id = 4;
    mars.name = "Mars";
    mars.angularSize = 9.36; // arcseconds at 1 AU
    mars.magnitude = -1.52;
    mars.imageUrl = QUrl("qrc:/images/mars.jpg");
    m_objects.append(mars);

    // Jupiter - J2000 elements
    SolarSystemObject jupiter;
    jupiter.id = 5;
    jupiter.name = "Jupiter";
    jupiter.angularSize = 196.74; // arcseconds at 1 AU
    jupiter.magnitude = -9.4;
    jupiter.imageUrl = QUrl("qrc:/images/jupiter.jpg");
    m_objects.append(jupiter);

    // Saturn - J2000 elements
    SolarSystemObject saturn;
    saturn.id = 6;
    saturn.name = "Saturn";
    saturn.angularSize = 165.6; // arcseconds at 1 AU
    saturn.magnitude = -8.88;
    saturn.imageUrl = QUrl("qrc:/images/saturn.jpg");
    m_objects.append(saturn);

    // Uranus - J2000 elements
    SolarSystemObject uranus;
    uranus.id = 7;
    uranus.name = "Uranus";
    uranus.angularSize = 70.5; // arcseconds at 1 AU
    uranus.magnitude = -7.19;
    uranus.imageUrl = QUrl("qrc:/images/uranus.jpg");
    m_objects.append(uranus);

    // Neptune - J2000 elements
    SolarSystemObject neptune;
    neptune.id = 8;
    neptune.name = "Neptune";
    neptune.angularSize = 68.3; // arcseconds at 1 AU
    neptune.magnitude = -6.87;
    neptune.imageUrl = QUrl("qrc:/images/neptune.jpg");
    m_objects.append(neptune);
}

QVariantList SolarSystemCalculator::getVisibleObjects() const
{
    return m_visibleObjects;
}

void SolarSystemCalculator::setFieldOfView(double fov)
{
    m_fieldOfView = fov;
}

// Correct Julian Date calculation for midnight vs noon convention
double SolarSystemCalculator::calculateJulianDate(const QDateTime& dateTime) {
    // Extract date and time
    QDate date = dateTime.date();
    QTime time = dateTime.time();
    
    // Get year, month, day
    int year = date.year();
    int month = date.month();
    int day = date.day();
    bool checked = true;
    
    // Handle months January and February (months 1 and 2) as months 13 and 14 of the previous year
    int Y, M;
    if (month < 3) {
        Y = year - 1;
        M = month + 12;
    } else {
        Y = year;
        M = month;
    }
    
    // Calculate the correction term for Gregorian calendar
    int C = 0;
    if (checked) {
        int A = Y / 100;
        int B = A / 4;
        C = 2 - A + B;
    }
    
    // Calculate Julian Day Number (JDN)
    double E = floor(365.25 * (Y + 4716));
    double F = floor(30.6001 * (M + 1));
    double jdn = (double)(C + day) + E + F - 1524.5;
    
    // Add time of day (converting from hours to fractional days)
    double timeInDays = time.hour() / 24.0 + time.minute() / 1440.0 + time.second() / 86400.0;
    
    return jdn + timeInDays;
}

void SolarSystemCalculator::calculateCurrentPositions()
{
    // Get current time
    QDateTime now = QDateTime::currentDateTimeUtc();
    
    // Convert to Julian date
    // Julian date calculation - days since Jan 1, 4713 BC at noon
    
    double jd = calculateJulianDate(now);
 
    // Get observer's location from controller
    GeoCoordinate location = m_controller->location();
    
    // Update planet positions
    updatePositions(jd, location);
}

// Update the updatePositions method to also include the Sun and Moon
void SolarSystemCalculator::updatePositions(double jd, const GeoCoordinate& observer)
{
    // Clear previous positions
    m_visibleObjects.clear();

    // Calculate for each planet (existing code)
    for (const SolarSystemObject& object : m_objects) {
        double ra, dec, distance, phase, mag, az, alt;
        
        // Calculate position
        calculateAccuratePlanetPosition(object.id, object.name, jd, observer, ra, dec, distance, phase, mag, alt, az);
        
        // Angular distance from viewing center
        double dAz = az - m_controller->azimuth();
        if (dAz > 180) dAz -= 360;
        if (dAz < -180) dAz += 360;
        
        double dAlt = alt - m_controller->altitude();
        double angularDistance = qSqrt(dAz*dAz + dAlt*dAlt);
        
        // Only include objects within field of view
        if (angularDistance <= m_fieldOfView/2) {
            // Convert angular difference to normalized screen coordinates
            double normAzDiff = dAz / (m_fieldOfView/2);
            double normAltDiff = -dAlt / (m_fieldOfView/2);
            
            // Clamp values to ensure they're in display range (-0.9 to 0.9)
            normAzDiff = qBound(-0.9, normAzDiff, 0.9);
            normAltDiff = qBound(-0.9, normAltDiff, 0.9);
            
            // Calculate apparent angular size (arcseconds)
            double angSize = object.angularSize / distance;
            
            // Create data map for this object
            QVariantMap objectMap;
            objectMap["name"] = object.name;
            objectMap["ra"] = ra;
            objectMap["dec"] = dec;
            objectMap["azimuth"] = az;
            objectMap["altitude"] = alt;
            objectMap["distance"] = distance;
            objectMap["magnitude"] = mag;
            objectMap["angularSize"] = angSize;
            objectMap["phase"] = phase;
            objectMap["viewX"] = normAzDiff;
            objectMap["viewY"] = normAltDiff;
            objectMap["imageUrl"] = object.imageUrl;
            objectMap["displaySize"] = qMin(80.0, qMax(10.0, angSize * 0.1));  // Size on screen
            
            m_visibleObjects.append(objectMap);
        }
    }
}

// Add this method to your SolarSystemCalculator class
void SolarSystemCalculator::debugMarsJ2000Position() {
    // Use the exact J2000 epoch time that matches the JPL ephemeris
    // JPL data is for 2451545.25 (2000-01-01 18:00:00 UT)
    double jdTest = 2451545.25;
    
    // Get observer location - can use any location since we're only checking
    // the RA/DEC which are Earth-centered coordinates
    GeoCoordinate earthLocation(0.0, 0.0); // Equator at Greenwich
    
    // Clear the visible objects list for this test
    m_visibleObjects.clear();
    
    // Run the position calculation with our test date
    updatePositions(jdTest, earthLocation);
    
    // Look for Mars in the calculated objects
    bool foundMars = false;
    double calculatedRA = 0.0;
    double calculatedDEC = 0.0;
    double calculatedMag = 0.0;
    
    // Fix: Use proper QVariant iteration and conversion
    for (int i = 0; i < m_visibleObjects.size(); i++) {
        QVariantMap object = m_visibleObjects[i].toMap();
        if (object["name"].toString() == "Mars") {
            foundMars = true;
            calculatedRA = object["ra"].toDouble();
            calculatedDEC = object["dec"].toDouble();
            calculatedMag = object["magnitude"].toDouble();
            break;
        }
    }
    
    if (!foundMars) {
        qDebug() << "Mars not found in visible objects! Check field of view settings.";
        // Temporarily expand field of view if needed
        double savedFOV = m_fieldOfView;
        m_fieldOfView = 180.0; // See whole sky
        updatePositions(jdTest, earthLocation);
        m_fieldOfView = savedFOV; // Restore original
        
        // Try again with the same correction as above
        for (int i = 0; i < m_visibleObjects.size(); i++) {
            QVariantMap object = m_visibleObjects[i].toMap();
            if (object["name"].toString() == "Mars") {
                foundMars = true;
                calculatedRA = object["ra"].toDouble();
                calculatedDEC = object["dec"].toDouble();
                calculatedMag = object["magnitude"].toDouble();
                break;
            }
        }
        
        if (!foundMars) {
            qDebug() << "Mars still not found! Check planet initialization.";
            return;
        }
    }    
    
    // Convert RA from degrees to HMS
    double ra_hours = calculatedRA / 15.0;
    int ra_h = (int)ra_hours;
    double ra_m_decimal = (ra_hours - ra_h) * 60.0;
    int ra_m = (int)ra_m_decimal;
    double ra_s = (ra_m_decimal - ra_m) * 60.0;
    
    // Convert Dec from degrees to DMS
    int dec_sign = (calculatedDEC < 0) ? -1 : 1;
    double dec_abs = fabs(calculatedDEC);
    int dec_d = (int)dec_abs;
    double dec_m_decimal = (dec_abs - dec_d) * 60.0;
    int dec_m = (int)dec_m_decimal;
    double dec_s = (dec_m_decimal - dec_m) * 60.0;
    
    // Print results
    qDebug() << "=== MARS POSITION AT J2000 MIDNIGHT (JD 2451544.5) ===";
    qDebug() << "Calculated using existing SolarSystemCalculator:";
    qDebug().nospace() << "RA: " << ra_h << "h " << ra_m << "m " << ra_s << "s";
    qDebug().nospace() << "Dec: " << (dec_sign < 0 ? "-" : "+") << dec_d << "° " << dec_m << "' " << dec_s << "\"";
    qDebug() << "Magnitude: " << calculatedMag;
    qDebug() << "";
    qDebug() << "NASA JPL Horizons Ephemeris:";
    qDebug() << "RA: 22h 00m 36.72s";
    qDebug() << "Dec: -13° 19' 13.4\"";
    qDebug() << "Magnitude: 1.089";
    
    // Calculate difference
    double ra_calc_seconds = ra_h * 3600.0 + ra_m * 60.0 + ra_s;
    double ra_jpl_seconds = 22 * 3600.0 + 0 * 60.0 + 36.72;
    double ra_diff_seconds = fabs(ra_calc_seconds - ra_jpl_seconds);
    
    double dec_calc_seconds = dec_sign * (dec_d * 3600.0 + dec_m * 60.0 + dec_s);
    double dec_jpl_seconds = -1 * (13 * 3600.0 + 19 * 60.0 + 13.4);
    double dec_diff_seconds = fabs(dec_calc_seconds - dec_jpl_seconds);
    
    qDebug() << "=== DIFFERENCE ===";
    qDebug() << "RA difference: " << ra_diff_seconds << " arcseconds";
    qDebug() << "Dec difference: " << dec_diff_seconds << " arcseconds";
    qDebug() << "Acceptable accuracy: < 60 arcseconds (< 1 arcminute)";
}

// Update the initialize method to include Sun and Moon
void SolarSystemCalculator::initialize()
{
    initializePlanets();
    // initializeSunAndMoon();
    // debugMarsJ2000Position();
}

void SolarSystemCalculator::calculateAccuratePlanetPosition(int ix, const QString& planetName, double jd, const GeoCoordinate& observer, double& ra, double& dec, double& distance, double& phase, double& mag, double& alt, double& az) {
    // Convert QString to C-string
    QByteArray bodyNameBytes = planetName.toLatin1();
    const char* bodyName = bodyNameBytes.constData();
    static double prev[11]; // increase this if we discover new planets (?)
    
    // Call the external ephemeris function
    double *buffer = ephem(bodyName, jd, observer.latitude(), observer.longitude());
    
    // The function prints results, but we also need to capture them
    // Assuming buffer[3], buffer[4], buffer[5] contain the results in radians
    // and are accessible here after calling ephem
    ra = buffer[3] * 180.0 / M_PI;  // Convert to degrees
    dec = buffer[4] * 180.0 / M_PI; // Convert to degrees
    distance = buffer[11];
    phase = buffer[6];
    mag = buffer[5];
    // Convert RA/Dec to Azimuth/Altitude for field of view calculations
    m_controller->m_astronomyCalculator.equatorialToHorizontal(ra/15.0, dec, &az, &alt);
    if (jd > prev[ix])
      {
	prev[ix] = jd + 0.001;
	qDebug() << bodyName << ra << dec << alt << az << distance;
      }
}
