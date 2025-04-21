#ifndef GEOCOORDINATE_H
#define GEOCOORDINATE_H

#include <QObject>

// Instead of inheriting from QObject, we'll make it a regular C++ class
// and use Q_GADGET for meta-object support
class GeoCoordinate
{
    Q_GADGET
    Q_PROPERTY(double latitude READ latitude WRITE setLatitude)
    Q_PROPERTY(double longitude READ longitude WRITE setLongitude)
    Q_PROPERTY(double altitude READ altitude WRITE setAltitude)
    Q_PROPERTY(bool isValid READ isValid)
    
public:
    GeoCoordinate();
    GeoCoordinate(double latitude, double longitude, double altitude = 0.0);
    
    // Copy constructor and assignment operator (explicitly defined)
    GeoCoordinate(const GeoCoordinate &other);
    GeoCoordinate& operator=(const GeoCoordinate &other);
    
    double latitude() const;
    double longitude() const;
    double altitude() const;
    bool isValid() const;
    
    void setLatitude(double latitude);
    void setLongitude(double longitude);
    void setAltitude(double altitude);
    
    bool operator==(const GeoCoordinate &other) const;
    bool operator!=(const GeoCoordinate &other) const;
    
private:
    double m_latitude;
    double m_longitude;
    double m_altitude;
    bool m_isValid;
};

// Declare it as a metatype so it can be used in signals/slots
Q_DECLARE_METATYPE(GeoCoordinate)

#endif // GEOCOORDINATE_H
