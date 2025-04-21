#ifndef SKYVIEWCONTROLLER_H
#define SKYVIEWCONTROLLER_H

#include <QObject>
#include <QDateTime>
#include "GeoCoordinate.h"
#include <QHash>
#include <QString>
#include <QUrl>
#include "IOSSensorBridge.h"
#include "AstronomyCalculator.h"

// Structure to hold deep sky object information
struct DSOObject {
    QString name;
    double rightAscension;  // in hours
    double declination;     // in degrees
    QUrl imageUrl;          // local path to image
};

class SkyViewController : public QObject
{
    Q_OBJECT
    
    // Properties exposed to QML
    Q_PROPERTY(double azimuth READ azimuth NOTIFY azimuthChanged)
    Q_PROPERTY(double altitude READ altitude NOTIFY altitudeChanged)
    Q_PROPERTY(QVariantList visibleDSOs READ visibleDSOs NOTIFY visibleDSOsChanged)
    Q_PROPERTY(GeoCoordinate location READ location WRITE setLocation NOTIFY locationChanged)
    Q_PROPERTY(bool isGPSEnabled READ isGPSEnabled NOTIFY gpsStatusChanged)
    Q_PROPERTY(double locationAccuracy READ locationAccuracy NOTIFY locationMetadataChanged)
    Q_PROPERTY(QString locationStatus READ locationStatus NOTIFY locationStatusChanged)
    
public:
    explicit SkyViewController(QObject *parent = nullptr);
    ~SkyViewController();
    
    // Getters
    double azimuth() const;
    double altitude() const;
    QVariantList visibleDSOs() const;
    GeoCoordinate location() const;
    bool isGPSEnabled() const;
    double locationAccuracy() const;
    QString locationStatus() const;
    
    // Setters
    void setLocation(const GeoCoordinate &location);
    
    // Q_INVOKABLE methods that can be called from QML
    Q_INVOKABLE void addCustomDSO(const QString &name, double ra, double dec, const QUrl &imageUrl);
    Q_INVOKABLE void loadDefaultDSOs();
    Q_INVOKABLE void startSensors();
    Q_INVOKABLE void stopSensors();
    Q_INVOKABLE void setGPSAccuracy(int accuracy); // 0=Best, 1=Navigation, 2=Balanced, 3=LowPower
    Q_INVOKABLE void useManualLocation(bool manual);
    Q_INVOKABLE void requestLocationPermission();
    
signals:
    void azimuthChanged(double azimuth);
    void altitudeChanged(double altitude);
    void visibleDSOsChanged();
    void locationChanged();
    void gpsStatusChanged(bool enabled);
    void locationMetadataChanged();
    void locationStatusChanged(const QString &status);
    
private slots:
    void onAzimuthChanged(double azimuth);
    void onPitchChanged(double pitch);
    void onLocationChanged(GeoCoordinate location);
    void onLocationError(const QString &errorMessage);
    void onLocationAuthorizationChanged(bool authorized);
    void onLocationMetadataChanged();
    void updateVisibleDSOs();
    
private:
    // Use AstronomyCalculator for celestial calculations
    AstronomyCalculator m_astronomyCalculator;
    
    // iOS Sensor Bridge
    IOSSensorBridge *m_sensorBridge;
    
    // Current orientation
    double m_azimuth;    // compass direction in degrees (0 = North, 90 = East)
    double m_altitude;   // tilt angle in degrees (-90 = down, 0 = horizontal, 90 = up)
    
    // Location and time
    GeoCoordinate m_location;
    bool m_manualLocationMode;
    double m_locationAccuracy;
    QString m_locationStatus;
    
    // DSO database
    QList<DSOObject> m_dsoObjects;
    QVariantList m_visibleDSOs;  // Objects currently in view
    
    // View parameters
    double m_fieldOfView;  // Field of view in degrees
};

#endif // SKYVIEWCONTROLLER_H
