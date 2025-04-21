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
    // Calculate Local Sidereal Time
    double lst = calculateLST();
    
    // Convert LST from degrees to hours
    lst /= 15.0;
    
    // Calculate Hour Angle in hours
    double ha = lst - ra;
    // Normalize to 0-24 range
    ha = normalizeAngle(ha, 0.0, 24.0);
    // Convert hour angle to degrees
    ha *= 15.0;
    
    // Convert all angles to radians
    double haRad = degreesToRadians(ha);
    double decRad = degreesToRadians(dec);
    double latRad = degreesToRadians(m_location.latitude());
    
    // Calculate altitude
    double sinAlt = qSin(decRad) * qSin(latRad) + qCos(decRad) * qCos(latRad) * qCos(haRad);
    double altRad = qAsin(sinAlt);
    
    // Calculate azimuth
    double cosAz = (qSin(decRad) - qSin(altRad) * qSin(latRad)) / (qCos(altRad) * qCos(latRad));
    // Clamp cosAz to valid range for acos
    cosAz = qBound(-1.0, cosAz, 1.0);
    
    double azRad = qAcos(cosAz);
    
    // Adjust azimuth based on hour angle
    if (qSin(haRad) >= 0) {
        azRad = 2.0 * M_PI - azRad;
    }
    
    // Convert back to degrees
    *altitude = radiansToDegrees(altRad);
    *azimuth = radiansToDegrees(azRad);
}

void AstronomyCalculator::horizontalToEquatorial(double azimuth, double altitude, double* ra, double* dec)
{
    // Convert to radians
    double azRad = degreesToRadians(azimuth);
    double altRad = degreesToRadians(altitude);
    double latRad = degreesToRadians(m_location.latitude());
    
    // Calculate declination
    double sinDec = qSin(altRad) * qSin(latRad) + qCos(altRad) * qCos(latRad) * qCos(azRad);
    double decRad = qAsin(sinDec);
    
    // Calculate hour angle
    double cosHA = (qSin(altRad) - qSin(decRad) * qSin(latRad)) / (qCos(decRad) * qCos(latRad));
    // Clamp to valid range for acos
    cosHA = qBound(-1.0, cosHA, 1.0);
    double haRad = qAcos(cosHA);
    
    // Adjust hour angle based on azimuth
    if (qSin(azRad) >= 0) {
        haRad = 2.0 * M_PI - haRad;
    }
    
    // Convert hour angle to hours
    double ha = radiansToDegrees(haRad) / 15.0;
    
    // Calculate Local Sidereal Time
    double lst = calculateLST() / 15.0; // Convert to hours
    
    // Calculate right ascension
    double rightAscension = normalizeAngle(lst - ha, 0.0, 24.0);
    
    // Set results
    *ra = rightAscension;
    *dec = radiansToDegrees(decRad);
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
