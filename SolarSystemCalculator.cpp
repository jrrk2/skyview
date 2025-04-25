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

    // Mercury - J2000 elements
    SolarSystemObject mercury;
    mercury.id = 1;
    mercury.name = "Mercury";
    mercury.semiMajorAxis = 0.38709927;
    mercury.eccentricity = 0.20563593;
    mercury.inclination = 7.00497902 * DEG_TO_RAD;
    mercury.longAscNode = 48.33076593 * DEG_TO_RAD;
    mercury.argPerihelion = 77.45779628 * DEG_TO_RAD;
    mercury.meanAnomaly = 252.25032350 * DEG_TO_RAD;
    mercury.epochJD = JD_J2000;
    mercury.angularSize = 6.74; // arcseconds at 1 AU
    mercury.magnitude = -0.6;
    mercury.phaseCoefficient = 3.8;
    mercury.imageUrl = QUrl("qrc:/images/mercury.jpg");
    m_objects.append(mercury);

    // Venus - J2000 elements
    SolarSystemObject venus;
    venus.id = 2;
    venus.name = "Venus";
    venus.semiMajorAxis = 0.72333566;
    venus.eccentricity = 0.00677672;
    venus.inclination = 3.39467605 * DEG_TO_RAD;
    venus.longAscNode = 76.67984255 * DEG_TO_RAD;
    venus.argPerihelion = 131.60246718 * DEG_TO_RAD;
    venus.meanAnomaly = 181.97909950 * DEG_TO_RAD;
    venus.epochJD = JD_J2000;
    venus.angularSize = 16.92; // arcseconds at 1 AU
    venus.magnitude = -4.6;
    venus.phaseCoefficient = 0.65;
    venus.imageUrl = QUrl("qrc:/images/venus.jpg");
    m_objects.append(venus);

    // Mars - J2000 elements
    SolarSystemObject mars;
    mars.id = 4;
    mars.name = "Mars";
    mars.semiMajorAxis = 1.52371034;
    mars.eccentricity = 0.09339410;
    mars.inclination = 1.84969142 * DEG_TO_RAD;
    mars.longAscNode = 49.55953891 * DEG_TO_RAD;
    mars.argPerihelion = 336.04084219 * DEG_TO_RAD;
    mars.meanAnomaly = 355.45332150 * DEG_TO_RAD;
    mars.epochJD = JD_J2000;
    mars.angularSize = 9.36; // arcseconds at 1 AU
    mars.magnitude = -1.52;
    mars.phaseCoefficient = 1.6;
    mars.imageUrl = QUrl("qrc:/images/mars.jpg");
    m_objects.append(mars);

    // Jupiter - J2000 elements
    SolarSystemObject jupiter;
    jupiter.id = 5;
    jupiter.name = "Jupiter";
    jupiter.semiMajorAxis = 5.20288700;
    jupiter.eccentricity = 0.04838624;
    jupiter.inclination = 1.30439695 * DEG_TO_RAD;
    jupiter.longAscNode = 100.47390909 * DEG_TO_RAD;
    jupiter.argPerihelion = 14.72847983 * DEG_TO_RAD;
    jupiter.meanAnomaly = 34.39644051 * DEG_TO_RAD;
    jupiter.epochJD = JD_J2000;
    jupiter.angularSize = 196.74; // arcseconds at 1 AU
    jupiter.magnitude = -9.4;
    jupiter.phaseCoefficient = 0.0;
    jupiter.imageUrl = QUrl("qrc:/images/jupiter.jpg");
    m_objects.append(jupiter);

    // Saturn - J2000 elements
    SolarSystemObject saturn;
    saturn.id = 6;
    saturn.name = "Saturn";
    saturn.semiMajorAxis = 9.53667594;
    saturn.eccentricity = 0.05386179;
    saturn.inclination = 2.48599187 * DEG_TO_RAD;
    saturn.longAscNode = 113.66242448 * DEG_TO_RAD;
    saturn.argPerihelion = 92.59887831 * DEG_TO_RAD;
    saturn.meanAnomaly = 49.95424423 * DEG_TO_RAD;
    saturn.epochJD = JD_J2000;
    saturn.angularSize = 165.6; // arcseconds at 1 AU
    saturn.magnitude = -8.88;
    saturn.phaseCoefficient = 0.0;
    saturn.imageUrl = QUrl("qrc:/images/saturn.jpg");
    m_objects.append(saturn);

    // Uranus - J2000 elements
    SolarSystemObject uranus;
    uranus.id = 7;
    uranus.name = "Uranus";
    uranus.semiMajorAxis = 19.18916464;
    uranus.eccentricity = 0.04725744;
    uranus.inclination = 0.77263783 * DEG_TO_RAD;
    uranus.longAscNode = 74.01692503 * DEG_TO_RAD;
    uranus.argPerihelion = 170.95427630 * DEG_TO_RAD;
    uranus.meanAnomaly = 313.23810451 * DEG_TO_RAD;
    uranus.epochJD = JD_J2000;
    uranus.angularSize = 70.5; // arcseconds at 1 AU
    uranus.magnitude = -7.19;
    uranus.phaseCoefficient = 0.0;
    uranus.imageUrl = QUrl("qrc:/images/uranus.jpg");
    m_objects.append(uranus);

    // Neptune - J2000 elements
    SolarSystemObject neptune;
    neptune.id = 8;
    neptune.name = "Neptune";
    neptune.semiMajorAxis = 30.06992276;
    neptune.eccentricity = 0.00859048;
    neptune.inclination = 1.77004347 * DEG_TO_RAD;
    neptune.longAscNode = 131.78422574 * DEG_TO_RAD;
    neptune.argPerihelion = 44.97135093 * DEG_TO_RAD;
    neptune.meanAnomaly = 304.88003451 * DEG_TO_RAD;
    neptune.epochJD = JD_J2000;
    neptune.angularSize = 68.3; // arcseconds at 1 AU
    neptune.magnitude = -6.87;
    neptune.phaseCoefficient = 0.0;
    neptune.imageUrl = QUrl("qrc:/images/neptune.jpg");
    m_objects.append(neptune);
}

void SolarSystemCalculator::calculatePosition(const SolarSystemObject& object, double jd,
                                           const QVector3D& earthPos, const QVector3D& sunPos,
                                           double& ra, double& dec, double& distance, 
                                           double& phase, double& mag)
{
    // Calculate heliocentric position
    QVector3D objectPos;
    calculateKeplerianPosition(object, jd, objectPos);
    
    // Object position relative to Earth
    QVector3D objectPosFromEarth = objectPos - earthPos;
    
    // Calculate RA and Dec
    distance = objectPosFromEarth.length();
    
    // RA and Dec
    ra = qAtan2(objectPosFromEarth.y(), objectPosFromEarth.x()) * RAD_TO_DEG;
    if (ra < 0) ra += 360.0;
    
    dec = qAsin(objectPosFromEarth.z() / distance) * RAD_TO_DEG;
    
    // Calculate Sun-Object-Earth phase angle
    QVector3D objectPosFromSun = objectPos - sunPos;
    double sunDistance = objectPosFromSun.length();
    
    // Cosine of phase angle
    double cosPhaseAngle = QVector3D::dotProduct(objectPosFromEarth, objectPosFromSun) / 
                           (distance * sunDistance);
    
    // Ensure cosine is in valid range [-1, 1]
    cosPhaseAngle = qBound(-1.0, cosPhaseAngle, 1.0);
    
    // Calculate phase (0 to 1, where 1 is fully illuminated)
    phase = (1.0 + cosPhaseAngle) / 2.0;
    
    // Calculate apparent magnitude
    mag = object.magnitude + 5.0 * qLn(sunDistance * distance) / qLn(10.0) - 
          2.5 * qLn(phase) / qLn(10.0) * object.phaseCoefficient;
}

void SolarSystemCalculator::calculateKeplerianPosition(const SolarSystemObject& object, double jd, QVector3D& pos)
{
    // Time since epoch in centuries
    double t = (jd - object.epochJD) / 36525.0;
    
    // Mean anomaly at date (adjusted for time since epoch)
    double M = object.meanAnomaly + calculateMeanMotion(object.semiMajorAxis) * (jd - object.epochJD);
    // Normalize to [0, 2*PI]
    M = fmod(M, TWO_PI);
    if (M < 0) M += TWO_PI;
    
    // Solve Kepler's equation using an iterative approach
    double E = M;  // Initial guess
    for (int i = 0; i < 10; i++) {  // Usually converges in <10 iterations
        E = M + object.eccentricity * qSin(E);
    }
    
    // Calculate true anomaly
    double xv = object.semiMajorAxis * (qCos(E) - object.eccentricity);
    double yv = object.semiMajorAxis * qSqrt(1.0 - object.eccentricity * object.eccentricity) * qSin(E);
    
    // Distance from the Sun
    double r = qSqrt(xv*xv + yv*yv);
    
    // True anomaly
    double v = qAtan2(yv, xv);
    
    // Calculate position in the orbital plane
    double xh = r * qCos(v + object.argPerihelion);
    double yh = r * qSin(v + object.argPerihelion);
    double zh = 0.0;
    
    // Apply inclination and longitude of ascending node rotation
    double cosNode = qCos(object.longAscNode);
    double sinNode = qSin(object.longAscNode);
    double cosInc = qCos(object.inclination);
    double sinInc = qSin(object.inclination);
    
    // Rotate to the ecliptic plane
    double xecl = xh * cosNode - yh * sinNode * cosInc;
    double yecl = xh * sinNode + yh * cosNode * cosInc;
    double zecl = yh * sinInc;
    
    // Convert to equatorial coordinates (apply obliquity of ecliptic)
    double eps = 23.43929111 * DEG_TO_RAD;  // J2000 obliquity
    double xequ = xecl;
    double yequ = yecl * qCos(eps) - zecl * qSin(eps);
    double zequ = yecl * qSin(eps) + zecl * qCos(eps);
    
    // Set the position vector
    pos.setX(xequ);
    pos.setY(yequ);
    pos.setZ(zequ);
}

// Calculate mean motion in radians per day
double SolarSystemCalculator::calculateMeanMotion(double semiMajorAxis)
{
    // Kepler's third law: n^2 * a^3 = G * (M_sun + M_planet)
    // For planets, M_sun >> M_planet, so n^2 * a^3 ≈ G * M_sun
    // This gives n ≈ √(G * M_sun / a^3)
    
    // G * M_sun in AU^3/day^2
    const double GM_SUN = 0.0002959122082855911026;
    
    // Mean motion in radians per day
    return sqrt(GM_SUN / pow(semiMajorAxis, 3)) * TWO_PI;
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

// Add these methods to SolarSystemCalculator.cpp

void SolarSystemCalculator::initializeSunAndMoon()
{
    // Clear any existing sun/moon data
    m_sunObject = SolarSystemObject();
    m_moonObject = SolarSystemObject();
    
    // Initialize the Sun
    m_sunObject.id = 0;
    m_sunObject.name = "Sun";
    m_sunObject.magnitude = -26.74;
    m_sunObject.angularSize = 1919.26; // arcseconds (approx 31.6 arcminutes at 1 AU)
    m_sunObject.imageUrl = QUrl("qrc:/images/sun.jpg");
    
    // Initialize the Moon
    m_moonObject.id = 10;
    m_moonObject.name = "Moon";
    m_moonObject.magnitude = -12.74;
    m_moonObject.angularSize = 1800.0; // arcseconds (approx 30 arcminutes, varies with distance)
    m_moonObject.imageUrl = QUrl("qrc:/images/moon.jpg");
    
    // Note: We don't set orbital elements for Sun/Moon since we'll calculate their positions differently
}

void SolarSystemCalculator::calculateSunPosition(double jd, QVector3D& pos)
{
    // Time in Julian centuries since J2000.0
    double T = (jd - 2451545.0) / 36525.0;
    
    // Mean longitude of the Sun
    double L0 = 280.46646 + 36000.76983 * T + 0.0003032 * T * T;
    
    // Mean anomaly of the Sun
    double M = 357.52911 + 35999.05029 * T - 0.0001537 * T * T;
    
    // Convert to radians
    double Mrad = M * DEG_TO_RAD;
    
    // Equation of the center
    double C = (1.914602 - 0.004817 * T - 0.000014 * T * T) * qSin(Mrad)
               + (0.019993 - 0.000101 * T) * qSin(2 * Mrad)
               + 0.000289 * qSin(3 * Mrad);
    
    // True longitude of the Sun
    double L = L0 + C;
    
    // Convert to radians
    double Lrad = L * DEG_TO_RAD;
    
    // Earth's distance from the Sun in AU
    double R = 1.000001018 * (1 - 0.016708634 * qCos(Mrad) - 0.000139589 * qCos(2 * Mrad));
    
    // Obliquity of the ecliptic
    double eps = (23.439291 - 0.0130042 * T) * DEG_TO_RAD;
    
    // Sun's rectangular coordinates (x,y,z) in equatorial system
    double x = R * qCos(Lrad);
    double y = R * qSin(Lrad) * qCos(eps);
    double z = R * qSin(Lrad) * qSin(eps);
    
    // Set the Sun's position (note: we negate it because we're calculating Earth->Sun vector)
    pos.setX(-x);
    pos.setY(-y);
    pos.setZ(-z);
}

void SolarSystemCalculator::calculateMoonPosition(double jd, const QVector3D& earthPos, QVector3D& moonPos)
{
    // Time in Julian centuries since J2000.0
    double T = (jd - 2451545.0) / 36525.0;
    
    // Moon's mean longitude
    double L = 218.3164477 + 481267.88123421 * T
               - 0.0015786 * T * T
               + T * T * T / 538841.0
               - T * T * T * T / 65194000.0;
    
    // Moon's mean elongation
    double D = 297.8501921 + 445267.1114034 * T
               - 0.0018819 * T * T
               + T * T * T / 545868.0
               - T * T * T * T / 113065000.0;
    
    // Sun's mean anomaly
    double M = 357.5291092 + 35999.0502909 * T
               - 0.0001536 * T * T
               + T * T * T / 24490000.0;
    
    // Moon's mean anomaly
    double M_ = 134.9633964 + 477198.8675055 * T
                + 0.0087414 * T * T
                + T * T * T / 69699.0
                - T * T * T * T / 14712000.0;
    
    // Moon's argument of latitude
    double F = 93.2720950 + 483202.0175233 * T
               - 0.0036539 * T * T
               - T * T * T / 3526000.0
               + T * T * T * T / 863310000.0;
    
    // Convert to radians
    double Lrad = L * DEG_TO_RAD;
    double Drad = D * DEG_TO_RAD;
    double Mrad = M * DEG_TO_RAD;
    double M_rad = M_ * DEG_TO_RAD;
    double Frad = F * DEG_TO_RAD;
    
    // Corrections for ecliptic longitude
    double dL = 0;
    dL += 22640 * qSin(M_rad);
    dL += 769 * qSin(2 * M_rad);
    dL += -4586 * qSin(M_rad - 2 * Drad);
    dL += 2370 * qSin(2 * Drad);
    dL += -668 * qSin(Mrad);
    dL += -412 * qSin(2 * Frad);
    // (more terms would go here for higher precision)
    
    // Corrections for ecliptic latitude
    double dB = 0;
    dB += 18520 * qSin(Frad + M_rad - Drad);
    dB += -526 * qSin(Frad - M_rad);
    // (more terms would go here for higher precision)
    
    // Corrections for distance
    double dR = 0;
    dR += -20905355 * qCos(M_rad);
    dR += -3699111 * qCos(2 * Drad - M_rad);
    dR += -2955968 * qCos(2 * Drad);
    // (more terms would go here for higher precision)
    
    // Ecliptic longitude and latitude
    double lambda = L + dL / 1000000; // in degrees
    double beta = dB / 1000000; // in degrees
    
    // Distance in Earth radii
    double delta = 385000.56 + dR / 1000; // in km
    
    // Convert to AU
    delta = delta / 149597870.7;
    
    // Convert to radians
    lambda = lambda * DEG_TO_RAD;
    beta = beta * DEG_TO_RAD;
    
    // Obliquity of the ecliptic
    double eps = (23.439291 - 0.0130042 * T) * DEG_TO_RAD;
    
    // Moon's rectangular coordinates (x,y,z) in equatorial system
    double x = delta * qCos(beta) * qCos(lambda);
    double y = delta * qCos(beta) * qSin(lambda) * qCos(eps) - delta * qSin(beta) * qSin(eps);
    double z = delta * qCos(beta) * qSin(lambda) * qSin(eps) + delta * qSin(beta) * qCos(eps);
    
    // Set the Moon's position relative to Earth
    moonPos.setX(x);
    moonPos.setY(y);
    moonPos.setZ(z);
}

void SolarSystemCalculator::calculateSunAndMoon(double jd, const GeoCoordinate& observer)
{
    // Earth's position (not used for Sun/Moon but needed for planet calculations)
    QVector3D earthPos(0, 0, 0);
    
    // Calculate Sun position
    QVector3D sunPos;
    calculateSunPosition(jd, sunPos);
    
    // Calculate Moon position relative to Earth
    QVector3D moonPos;
    calculateMoonPosition(jd, earthPos, moonPos);
    
    // Add Sun to visible objects if in field of view
    double sunRA = qAtan2(sunPos.y(), sunPos.x()) * RAD_TO_DEG;
    if (sunRA < 0) sunRA += 360.0;
    double sunDec = qAsin(sunPos.z() / sunPos.length()) * RAD_TO_DEG;
    double sunDistance = sunPos.length(); // in AU
    
    // Convert to azimuth/altitude
    double sunAz, sunAlt;
    m_controller->m_astronomyCalculator.equatorialToHorizontal(sunRA/15.0, sunDec, &sunAz, &sunAlt);
    
    // Get current viewing direction
    double viewAz = m_controller->azimuth();
    double viewAlt = m_controller->altitude();
    
    // Calculate angular distance from viewing center
    double dAz = sunAz - viewAz;
    if (dAz > 180) dAz -= 360;
    if (dAz < -180) dAz += 360;
    
    double dAlt = sunAlt - viewAlt;
    double angularDistance = qSqrt(dAz*dAz + dAlt*dAlt);
    
    // Add Sun to visible objects if in field of view
    if (angularDistance <= m_fieldOfView/2) {
        // Normalized screen coordinates
        double normAzDiff = -dAz / (m_fieldOfView/2);
        double normAltDiff = -dAlt / (m_fieldOfView/2);
        
        // Clamp values
        normAzDiff = qBound(-0.9, normAzDiff, 0.9);
        normAltDiff = qBound(-0.9, normAltDiff, 0.9);
        
        // Create data map for Sun
        QVariantMap sunMap;
        sunMap["name"] = m_sunObject.name;
        sunMap["ra"] = sunRA;
        sunMap["dec"] = sunDec;
        sunMap["azimuth"] = sunAz;
        sunMap["altitude"] = sunAlt;
        sunMap["distance"] = sunDistance;
        sunMap["magnitude"] = m_sunObject.magnitude;
        sunMap["angularSize"] = m_sunObject.angularSize / sunDistance; // in arcseconds
        sunMap["viewX"] = normAzDiff;
        sunMap["viewY"] = normAltDiff;
        sunMap["imageUrl"] = m_sunObject.imageUrl;
        sunMap["displaySize"] = 80;  // Make the sun reasonably large on screen
        sunMap["isSun"] = true;      // Special flag for rendering
        
        m_visibleObjects.append(sunMap);
    }
    
    // Add Moon to visible objects if in field of view
    double moonRA = qAtan2(moonPos.y(), moonPos.x()) * RAD_TO_DEG;
    if (moonRA < 0) moonRA += 360.0;
    double moonDec = qAsin(moonPos.z() / moonPos.length()) * RAD_TO_DEG;
    double moonDistance = moonPos.length(); // in AU
    
    // Convert to azimuth/altitude
    double moonAz, moonAlt;
    m_controller->m_astronomyCalculator.equatorialToHorizontal(moonRA/15.0, moonDec, &moonAz, &moonAlt);
    
    // Calculate angular distance from viewing center for Moon
    dAz = moonAz - viewAz;
    if (dAz > 180) dAz -= 360;
    if (dAz < -180) dAz += 360;
    
    dAlt = moonAlt - viewAlt;
    angularDistance = qSqrt(dAz*dAz + dAlt*dAlt);
    
    // Calculate moon phase (0 to 1, where 0 is new moon and 1 is full moon)
    double moonPhase = 0.5 * (1 - qCos(qAtan2(sunPos.y() - moonPos.y(), sunPos.x() - moonPos.x()) - 
                                        qAtan2(moonPos.y(), moonPos.x())));
    
    // Add Moon to visible objects if in field of view
    if (angularDistance <= m_fieldOfView/2) {
        // Normalized screen coordinates
        double normAzDiff = -dAz / (m_fieldOfView/2);
        double normAltDiff = -dAlt / (m_fieldOfView/2);
        
        // Clamp values
        normAzDiff = qBound(-0.9, normAzDiff, 0.9);
        normAltDiff = qBound(-0.9, normAltDiff, 0.9);
        
        // Create data map for Moon
        QVariantMap moonMap;
        moonMap["name"] = m_moonObject.name;
        moonMap["ra"] = moonRA;
        moonMap["dec"] = moonDec;
        moonMap["azimuth"] = moonAz;
        moonMap["altitude"] = moonAlt;
        moonMap["distance"] = moonDistance;
        moonMap["magnitude"] = m_moonObject.magnitude;
        moonMap["angularSize"] = m_moonObject.angularSize;
        moonMap["phase"] = moonPhase;
        moonMap["viewX"] = normAzDiff;
        moonMap["viewY"] = normAltDiff;
        moonMap["imageUrl"] = m_moonObject.imageUrl;
        moonMap["displaySize"] = 50;  // Make the moon reasonably large on screen
        moonMap["isMoon"] = true;     // Special flag for rendering
        
        m_visibleObjects.append(moonMap);
    }
}

// Update the updatePositions method to also include the Sun and Moon
void SolarSystemCalculator::updatePositions(double jd, const GeoCoordinate& observer)
{
    // Clear previous positions
    m_visibleObjects.clear();

    // Sun's position (from barycenter)
    QVector3D sunPos(0, 0, 0);  // Simplified - Sun is approximately at the barycenter
    
    // Add Sun and Moon (special calculations)
    calculateSunAndMoon(jd, observer);
    
    // Get current viewing direction
    double azimuth = m_controller->azimuth() * DEG_TO_RAD;
    double altitude = m_controller->altitude() * DEG_TO_RAD;
    
    // Calculate for each planet (existing code)
    for (const SolarSystemObject& object : m_objects) {
        double ra, dec, distance, phase, mag;
        
        // Calculate position
        calculateAccuratePlanetPosition(object.name, jd, observer, ra, dec, distance, phase, mag);
        
        // Convert RA/Dec to Azimuth/Altitude for field of view calculations
        double az, alt;
        m_controller->m_astronomyCalculator.equatorialToHorizontal(ra/15.0, dec, &az, &alt);
        
        // Angular distance from viewing center
        double dAz = az - m_controller->azimuth();
        if (dAz > 180) dAz -= 360;
        if (dAz < -180) dAz += 360;
        
        double dAlt = alt - m_controller->altitude();
        double angularDistance = qSqrt(dAz*dAz + dAlt*dAlt);
        
        // Only include objects within field of view
        if (angularDistance <= m_fieldOfView/2) {
            // Convert angular difference to normalized screen coordinates
            double normAzDiff = -dAz / (m_fieldOfView/2);
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
            objectMap["displaySize"] = qMax(10.0, angSize * 0.1);  // Size on screen
            
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
    initializeSunAndMoon();
    //    debugMarsJ2000Position();
}

void SolarSystemCalculator::calculateAccuratePlanetPosition(const QString& planetName, double jd, const GeoCoordinate& observer, double& ra, double& dec, double& distance, double& phase, double& mag) {
    // Convert QString to C-string
    QByteArray bodyNameBytes = planetName.toLatin1();
    const char* bodyName = bodyNameBytes.constData();
    
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
}
