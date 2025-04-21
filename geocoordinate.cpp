#include "GeoCoordinate.h"
#include <QtMath>

GeoCoordinate::GeoCoordinate()
    : m_latitude(0.0),
      m_longitude(0.0),
      m_altitude(0.0),
      m_isValid(false)
{
}

GeoCoordinate::GeoCoordinate(double latitude, double longitude, double altitude)
    : m_latitude(latitude),
      m_longitude(longitude),
      m_altitude(altitude),
      m_isValid(true)
{
    // Validate latitude/longitude ranges
    if (latitude < -90.0 || latitude > 90.0 || longitude < -180.0 || longitude > 180.0) {
        m_isValid = false;
    }
}

// Copy constructor
GeoCoordinate::GeoCoordinate(const GeoCoordinate &other)
    : m_latitude(other.m_latitude),
      m_longitude(other.m_longitude),
      m_altitude(other.m_altitude),
      m_isValid(other.m_isValid)
{
}

// Assignment operator
GeoCoordinate& GeoCoordinate::operator=(const GeoCoordinate &other)
{
    if (this != &other) {
        m_latitude = other.m_latitude;
        m_longitude = other.m_longitude;
        m_altitude = other.m_altitude;
        m_isValid = other.m_isValid;
    }
    return *this;
}

double GeoCoordinate::latitude() const
{
    return m_latitude;
}

double GeoCoordinate::longitude() const
{
    return m_longitude;
}

double GeoCoordinate::altitude() const
{
    return m_altitude;
}

bool GeoCoordinate::isValid() const
{
    return m_isValid;
}

void GeoCoordinate::setLatitude(double latitude)
{
    m_latitude = latitude;
    
    // Update validity
    m_isValid = (m_latitude >= -90.0 && m_latitude <= 90.0 && 
                 m_longitude >= -180.0 && m_longitude <= 180.0);
}

void GeoCoordinate::setLongitude(double longitude)
{
    m_longitude = longitude;
    
    // Update validity
    m_isValid = (m_latitude >= -90.0 && m_latitude <= 90.0 && 
                 m_longitude >= -180.0 && m_longitude <= 180.0);
}

void GeoCoordinate::setAltitude(double altitude)
{
    m_altitude = altitude;
}

bool GeoCoordinate::operator==(const GeoCoordinate &other) const
{
    return qFuzzyCompare(m_latitude, other.m_latitude) &&
           qFuzzyCompare(m_longitude, other.m_longitude) &&
           qFuzzyCompare(m_altitude, other.m_altitude);
}

bool GeoCoordinate::operator!=(const GeoCoordinate &other) const
{
    return !(*this == other);
}
