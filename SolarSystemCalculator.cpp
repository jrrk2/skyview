#include "SolarSystemCalculator.h"
#include "skyviewcontroller.h"
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

void SolarSystemCalculator::initialize()
{
    initializePlanets();
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

void SolarSystemCalculator::updatePositions(double jd, const GeoCoordinate& observer)
{
    // Clear previous positions
    m_visibleObjects.clear();

    // Earth's position - special case, we need it for all other calculations
    QVector3D earthPos(0, 0, 0);
    {
        // Simplified Earth elements for calculating Earth position relative to the Sun
        SolarSystemObject earth;
        earth.semiMajorAxis = 1.00000261;
        earth.eccentricity = 0.01671123;
        earth.inclination = 0.00001531 * DEG_TO_RAD;
        earth.longAscNode = 180.0 * DEG_TO_RAD;
        earth.argPerihelion = 102.93768193 * DEG_TO_RAD;
        earth.meanAnomaly = 100.46457166 * DEG_TO_RAD;
        earth.epochJD = JD_J2000;
        
        // Calculate Earth position
        calculateKeplerianPosition(earth, jd, earthPos);
    }

    // Sun's position (from barycenter)
    QVector3D sunPos(0, 0, 0);  // Simplified - Sun is approximately at the barycenter
    
    // Get current viewing direction
    double azimuth = m_controller->azimuth() * DEG_TO_RAD;
    double altitude = m_controller->altitude() * DEG_TO_RAD;
    
    // Calculate for each planet
    for (const SolarSystemObject& object : m_objects) {
        double ra, dec, distance, phase, mag;
        
        // Calculate position
        calculatePosition(object, jd, earthPos, sunPos, ra, dec, distance, phase, mag);
        
        // Convert RA/Dec to Azimuth/Altitude for field of view calculations
        double az, alt;
        m_controller->m_astronomyCalculator.equatorialToHorizontal(ra/DEG_TO_RAD, dec/DEG_TO_RAD, &az, &alt);
        
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

void SolarSystemCalculator::calculateCurrentPositions()
{
    // Get current time
    QDateTime now = QDateTime::currentDateTimeUtc();
    
    // Convert to Julian date
    // Julian date calculation - days since Jan 1, 4713 BC at noon
    QDate date = now.date();
    QTime time = now.time();
    
    int a = (14 - date.month()) / 12;
    int y = date.year() + 4800 - a;
    int m = date.month() + 12 * a - 3;
    
    double jd = date.day() + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 32045;
    
    // Add time of day
    double timeValue = time.hour() / 24.0 + time.minute() / 1440.0 + time.second() / 86400.0;
    jd += timeValue;
    
    // Get observer's location from controller
    GeoCoordinate location = m_controller->location();
    
    // Update planet positions
    updatePositions(jd, location);
}
