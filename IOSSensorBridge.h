#ifndef IOSSENSORBRIDGE_H
#define IOSSENSORBRIDGE_H

#include <QObject>
#include <QString>
#include <string>

#include "GeoCoordinate.h"

struct RotationMatrix {
    float m11, m12, m13;
    float m21, m22, m23;
    float m31, m32, m33;
};

// Forward declaration of implementation class
class IOSSensorBridgeImpl;

// C++ bridge class
class IOSSensorBridge : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double azimuth READ azimuth NOTIFY azimuthChanged)
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
    GeoCoordinate location() const;
    bool isLocationAuthorized() const;
    QString lastGPSError() const;
    double locationAccuracy() const;
    double locationSpeed() const;
    double locationCourse() const;
    
    // Methods called from Objective-C code
    void updateHeading(double heading);
    void updateLocation(double latitude, double longitude, double altitude = 0.0,
                      double horizontalAccuracy = 0.0, double verticalAccuracy = -1.0,
                      double speed = 0.0, double course = 0.0);
    void updateLocationError(const std::string& errorMessage);
    void updateLocationAuthorizationStatus(bool authorized);
    void updateRotationMatrix(float m11, float m12, float m13,
                         float m21, float m22, float m23,
                         float m31, float m32, float m33)
    {
    m_rotationMatrix.m11 = m11;
    m_rotationMatrix.m12 = m12;
    m_rotationMatrix.m13 = m13;
    m_rotationMatrix.m21 = m21;
    m_rotationMatrix.m22 = m22;
    m_rotationMatrix.m23 = m23;
    m_rotationMatrix.m31 = m31;
    m_rotationMatrix.m32 = m32;
    m_rotationMatrix.m33 = m33;  
    emit rotationMatrixChanged(m_rotationMatrix);
    }
  
    RotationMatrix rotationMatrix() const { return m_rotationMatrix; }
  
signals:
    void azimuthChanged(double azimuth);
    void rotationMatrixChanged(const RotationMatrix& matrix);
    void locationChanged(GeoCoordinate location);
    void locationErrorOccurred(const QString& errorMessage);
    void locationAuthorizationChanged(bool authorized);
    void locationMetadataChanged();
    
private:
    IOSSensorBridgeImpl* m_implementation;
    
    // Cached sensor values
    double m_azimuth;
    GeoCoordinate m_location;
    RotationMatrix m_rotationMatrix;
  
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
