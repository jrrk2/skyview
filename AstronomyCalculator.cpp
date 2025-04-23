#include "AstronomyCalculator.h"
#include <QtMath>
#include <QDebug>

AstronomyCalculator::AstronomyCalculator()
{
    // Default location (San Francisco)
    m_location = GeoCoordinate(37.7749, -122.4194);
    
    // Default time (current)
    m_dateTime = QDateTime::currentDateTimeUtc();
}

void AstronomyCalculator::setLocation(const GeoCoordinate& location)
{
    m_location = location;
}

void AstronomyCalculator::setDateTime(const QDateTime& dateTime)
{
    m_dateTime = dateTime;
}

double AstronomyCalculator::calculateLST()
{
    // Calculate local sidereal time
    // This is a more precise implementation than before
    
    // Convert date to Julian Date
    double julianDate = m_dateTime.date().toJulianDay();
    
    // Calculate time in UT1 decimal hours
    double ut1Hours = m_dateTime.time().hour() + 
                      m_dateTime.time().minute() / 60.0 + 
                      m_dateTime.time().second() / 3600.0;
    
    // Calculate days from J2000.0
    double d = julianDate - 2451545.0;
    
    // Calculate Greenwich Mean Sidereal Time (GMST) at UT1=0
    double t = d / 36525.0;  // Julian centuries since J2000.0
    double gmst0 = 100.46061837 + 36000.770053608 * t + 0.000387933 * t * t - (t * t * t) / 38710000.0;
    
    // Add UT1 contribution
    double gmst = normalizeAngle(gmst0 + 15.0 * ut1Hours * 1.0027379093, 0.0, 360.0);
    
    // Calculate Local Sidereal Time by adding the longitude
    double lst = normalizeAngle(gmst + m_location.longitude(), 0.0, 360.0);
    
    return lst;
}

void AstronomyCalculator::equatorialToHorizontal(double ra, double dec, double* azimuth, double* altitude)
{
    // Calculate Local Sidereal Time in radians
    double lst = calculateLST() * M_PI / 180.0; // Convert to radians
    
    // Convert RA to radians
    double raRad = degreesToRadians(ra * 15.0); // RA in hours to radians
    
    // Convert Dec to radians
    double decRad = degreesToRadians(dec);
    
    // Convert latitude to radians
    double latRad = degreesToRadians(m_location.latitude());
    
    // Calculate Hour Angle in radians
    double H = lst - raRad;
    
    // Normalize to -π to +π range
    if (H < 0) H += 2 * M_PI;
    if (H > M_PI) H = H - 2 * M_PI;
    
    // Calculate azimuth using the celestialprogramming.com formula
    double az = qAtan2(qSin(H), qCos(H)*qSin(latRad) - qTan(decRad)*qCos(latRad));
    
    // Calculate altitude using same formula as before
    double alt = qAsin(qSin(latRad)*qSin(decRad) + qCos(latRad)*qCos(decRad)*qCos(H));
    
    // Adjust azimuth as in the JavaScript code
    az -= M_PI;
    if (az < 0) az += 2 * M_PI;
    
    // Convert to degrees
    *azimuth = radiansToDegrees(az);
    *altitude = radiansToDegrees(alt);
}

double AstronomyCalculator::angularSeparation(double az1, double alt1, double az2, double alt2)
{
    // Convert to radians
    double az1Rad = degreesToRadians(az1);
    double alt1Rad = degreesToRadians(alt1);
    double az2Rad = degreesToRadians(az2);
    double alt2Rad = degreesToRadians(alt2);
    
    // Calculate angular separation using the haversine formula
    double dAz = az2Rad - az1Rad;
    double dAlt = alt2Rad - alt1Rad;
    
    double a = qSin(dAlt/2) * qSin(dAlt/2) + 
               qCos(alt1Rad) * qCos(alt2Rad) * qSin(dAz/2) * qSin(dAz/2);
    double c = 2 * qAtan2(qSqrt(a), qSqrt(1-a));
    
    // Convert back to degrees
    return radiansToDegrees(c);
}

double AstronomyCalculator::degreesToRadians(double degrees) const
{
    return degrees * M_PI / 180.0;
}

double AstronomyCalculator::radiansToDegrees(double radians) const
{
    return radians * 180.0 / M_PI;
}

double AstronomyCalculator::normalizeAngle(double angle, double min, double max) const
{
    double range = max - min;
    double normalized = fmod(angle - min, range);
    
    if (normalized < 0.0) {
        normalized += range;
    }
    
    return normalized + min;
}

// Now implement these methods in AstronomyCalculator.cpp:

double AstronomyCalculator::correctForRefraction(double apparentAltitude) const
{
    // Convert to radians
    double altRad = degreesToRadians(apparentAltitude);
    
    // Calculate refraction in arcminutes for standard conditions
    double refractionArcmin;
    
    if (apparentAltitude > 15.0) {
        // Above 15° altitude - simpler formula
        refractionArcmin = 1.02 / qTan(altRad + degreesToRadians(10.3 / (apparentAltitude + 5.11)));
    }
    else if (apparentAltitude >= 0.0) {
        // Low altitude - more complex formula
        double r = 0.1594 + apparentAltitude * (0.0196 + 0.00002 * apparentAltitude);
        refractionArcmin = r * (1.0 / qTan(altRad));
    }
    else {
        // Below horizon - use horizon value
        refractionArcmin = 34.0;
    }
    
    // Convert arcminutes to degrees and return true altitude
    double refractionDegrees = refractionArcmin / 60.0;
    return apparentAltitude - refractionDegrees;
}

void AstronomyCalculator::horizontalToJ2000(double azimuth, double altitude, double* raJ2000, double* decJ2000, double* hourAngle)
{
    // Apply refraction correction to get true altitude
    double trueAltitude = correctForRefraction(altitude);
    
    // Convert to radians
    double azRad = degreesToRadians(azimuth);
    double altRad = degreesToRadians(trueAltitude);
    double latRad = degreesToRadians(m_location.latitude());
    
    // Calculate declination
    double sinDec = qSin(altRad) * qSin(latRad) + qCos(altRad) * qCos(latRad) * qCos(azRad);
    double decRad = qAsin(sinDec);
    
    // Calculate hour angle using atan2 (more robust than acos)
    double cosHA = (qSin(altRad) - qSin(latRad) * sinDec) / (qCos(latRad) * qCos(decRad));
    double sinHA = -1.0 * qCos(altRad) * qSin(azRad) / qCos(decRad);
    double haRad = qAtan2(sinHA, cosHA);
    
    // Convert hour angle to hours
    double haHours = haRad * (12.0 / M_PI);
    
    // Ensure HA is in proper range (-12 to +12 hours)
    if (haHours < -12.0)
        haHours += 24.0;
    else if (haHours > 12.0)
        haHours -= 24.0;
    
    // Calculate Local Sidereal Time
    double lst = calculateLST() / 15.0; // Convert to hours
    
    // Calculate right ascension
    double rightAscension = lst - haHours;
    
    // Normalize to 0-24 range
    rightAscension = normalizeAngle(rightAscension, 0.0, 24.0);
    
    // Convert RA from hours to degrees
    double raDegrees = rightAscension * 15.0;
    double decDegrees = radiansToDegrees(decRad);
    
    // Calculate Julian centuries since J2000.0
    QDateTime currentDate = QDateTime::currentDateTimeUtc();
    double julianDate = currentDate.date().toJulianDay();
    double T = (julianDate - 2451545.0) / 36525.0;
    
    // Calculate correction factors (inverse of the standard precession)
    double M = 1.2812323 * T + 0.0003879 * T * T + 0.0000101 * T * T * T;
    double N = 0.5567530 * T - 0.0001185 * T * T + 0.0000116 * T * T * T;
    
    // Apply the inverse correction to get J2000 coordinates
    double deltaRA = M + N * qSin(degreesToRadians(raDegrees)) * qTan(degreesToRadians(decDegrees));
    double deltaDec = N * qCos(degreesToRadians(raDegrees));
    
    // Calculate J2000 coordinates
    *raJ2000 = (raDegrees - deltaRA) / 15.0; // Convert back to hours
    *decJ2000 = decDegrees - deltaDec;
    
    // Return hour angle if requested
    if (hourAngle != nullptr) {
        *hourAngle = haHours;
    }
}

// Now replace the original horizontalToEquatorial method with our new J2000 version:

void AstronomyCalculator::horizontalToEquatorial(double azimuth, double altitude, double* ra, double* dec)
{
    double hourAngle;
    horizontalToJ2000(azimuth, altitude, ra, dec, &hourAngle);
}
