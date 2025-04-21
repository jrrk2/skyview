#ifndef IOSSENSORBRIDGE_H
#define IOSSENSORBRIDGE_H

#include <QObject>
#include <QString>
#include <string>
#include "GeoCoordinate.h"

// Forward declaration of implementation class
class IOSSensorBridgeImpl;

// C++ bridge class
class IOSSensorBridge : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double azimuth READ azimuth NOTIFY azimuthChanged)
    Q_PROPERTY(double pitch READ pitch NOTIFY pitchChanged)
    Q_PROPERTY(double roll READ roll NOTIFY rollChanged)
    Q_PROPERTY(double yaw READ yaw NOTIFY yawChanged)
    Q_PROPERTY(GeoCoordinate location READ location NOTIFY locationChanged)
    Q_PROPERTY(bool locationAuthorized READ isLocationAuthorized NOTIFY locationAuthorizationChanged)
    Q_PROPERTY(QString lastGPSError READ lastGPSError NOTIFY locationErrorOccurred)
    Q_PROPERTY(double locationAccuracy READ locationAccuracy NOTIFY locationMetadataChanged)
    Q_PROPERTY(double locationSpeed READ locationSpeed NOTIFY locationMetadataChanged)
    Q_PROPERTY(double locationCourse READ locationCourse NOTIFY locationMetadataChanged)
    
public:
    // Enum for GPS accuracy settings - moved inside the class
    enum GPSAccuracy {
        Best,           // Most accurate, highest battery usage
        Navigation,     // Best for turn-by-turn navigation
        Balanced,       // ~10 meter accuracy, medium battery usage
        LowPower        // ~100 meter accuracy, low battery usage
    };
    Q_ENUM(GPSAccuracy)
    
    explicit IOSSensorBridge(QObject* parent = nullptr);
    ~IOSSensorBridge();
    
    // Sensor control methods
    Q_INVOKABLE void startSensors();
    Q_INVOKABLE void stopSensors();
    
    // GPS configuration methods
    Q_INVOKABLE void setGPSAccuracy(GPSAccuracy accuracy);
    Q_INVOKABLE void setGPSUpdateInterval(double meters);
    Q_INVOKABLE bool isGPSAvailable() const;
    Q_INVOKABLE bool isCompassAvailable() const;
    
    // Property getters
    double azimuth() const;
    double pitch() const;
    double roll() const;
    double yaw() const;
    GeoCoordinate location() const;
    bool isLocationAuthorized() const;
    QString lastGPSError() const;
    double locationAccuracy() const;
    double locationSpeed() const;
    double locationCourse() const;
    
    // Methods called from Objective-C code
    void updateHeading(double heading);
    void updateAttitude(double pitch, double roll, double yaw);
    void updateLocation(double latitude, double longitude, double altitude = 0.0,
                      double horizontalAccuracy = 0.0, double verticalAccuracy = -1.0,
                      double speed = 0.0, double course = 0.0);
    void updateLocationError(const std::string& errorMessage);
    void updateLocationAuthorizationStatus(bool authorized);
    
signals:
    void azimuthChanged(double azimuth);
    void pitchChanged(double pitch);
    void rollChanged(double roll);
    void yawChanged(double yaw);
    void locationChanged(GeoCoordinate location);
    void locationErrorOccurred(const QString& errorMessage);
    void locationAuthorizationChanged(bool authorized);
    void locationMetadataChanged();
    
private:
    IOSSensorBridgeImpl* m_implementation;
    
    // Cached sensor values
    double m_azimuth;
    double m_pitch;
    double m_roll;
    double m_yaw;
    GeoCoordinate m_location;
    
    // GPS status
    bool m_gpsEnabled;
    bool m_locationAuthorized;
    QString m_lastGPSError;
    
    // Location metadata
    double m_locationAccuracy; // Horizontal accuracy in meters
    double m_locationSpeed;    // Speed in meters per second
    double m_locationCourse;   // Course/heading in degrees (0-359.9)
};

#endif // IOSSENSORBRIDGE_H
