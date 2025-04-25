#ifndef SKYVIEWCONTROLLER_H
#define SKYVIEWCONTROLLER_H

#include <QObject>
#include <QDateTime>
#include <QMatrix3x3>
#include <QVector3D>
#include <QElapsedTimer>
#include "GeoCoordinate.h"
#include <QHash>
#include <QTimer>
#include <QString>
#include <QUrl>
#include "IOSSensorBridge.h"
#include "AstronomyCalculator.h"
#include "CompassBridge.h" // Add compass bridge header

// Forward declarations
class SolarSystemCalculator;

struct DSOObject {
    QString name;
    double rightAscension;  // in hours
    double declination;     // in degrees
    double angularSize;     // in arcminutes (diameter or width)
    QUrl imageUrl;          // local path to image
    int croppedWidth;       // Width of cropped image in pixels
    int croppedHeight;      // Height of cropped image in pixels  
    double scaleFactor;     // Scale factor based on 1.23 arcsec/pixel scale
    int displaySize;        // Recommended display size in pixels
};

class SkyViewController : public QObject
{
    Q_OBJECT
    
    // Properties exposed to QML
    Q_PROPERTY(double m11 READ m11 NOTIFY debugDataChanged)
    Q_PROPERTY(double m12 READ m12 NOTIFY debugDataChanged)
    Q_PROPERTY(double m13 READ m13 NOTIFY debugDataChanged)
    Q_PROPERTY(double m21 READ m21 NOTIFY debugDataChanged)
    Q_PROPERTY(double m22 READ m22 NOTIFY debugDataChanged)
    Q_PROPERTY(double m23 READ m23 NOTIFY debugDataChanged)
    Q_PROPERTY(double m31 READ m31 NOTIFY debugDataChanged)
    Q_PROPERTY(double m32 READ m32 NOTIFY debugDataChanged)
    Q_PROPERTY(double m33 READ m33 NOTIFY debugDataChanged)    
    Q_PROPERTY(double azimuth READ azimuth NOTIFY azimuthChanged)
    Q_PROPERTY(double altitude READ altitude NOTIFY altitudeChanged)
    Q_PROPERTY(QVariantList visibleDSOs READ visibleDSOs NOTIFY visibleDSOsChanged)
    Q_PROPERTY(GeoCoordinate location READ location WRITE setLocation NOTIFY locationChanged)
    Q_PROPERTY(bool isGPSEnabled READ isGPSEnabled NOTIFY gpsStatusChanged)
    Q_PROPERTY(double locationAccuracy READ locationAccuracy NOTIFY locationMetadataChanged)
    Q_PROPERTY(QString locationStatus READ locationStatus NOTIFY locationStatusChanged)
    Q_PROPERTY(double rightAscension READ rightAscension NOTIFY rightAscensionChanged)
    Q_PROPERTY(double declination READ declination NOTIFY declinationChanged)
    Q_PROPERTY(QString formattedRA READ formattedRA NOTIFY rightAscensionChanged)
    Q_PROPERTY(QString formattedDEC READ formattedDEC NOTIFY declinationChanged)
    Q_PROPERTY(QVariantList visibleSolarSystemObjects READ getVisibleSolarSystemObjects NOTIFY visibleSolarSystemObjectsChanged)
    // Add new compass bridge property
    Q_PROPERTY(double headingAccuracy READ headingAccuracy NOTIFY headingAccuracyChanged)
    
public:
    explicit SkyViewController(QObject *parent = nullptr);
    ~SkyViewController();
    AstronomyCalculator m_astronomyCalculator;
  
    // Getters
    double azimuth() const;
    double altitude() const;
    QVariantList visibleDSOs() const;
    GeoCoordinate location() const;
    bool isGPSEnabled() const;
    double locationAccuracy() const;
    QString locationStatus() const;
    double rightAscension() const;
    double declination() const;
    QString formattedRA() const;
    QString formattedDEC() const;
    // Add to the public section:
    double m11() const { return m_rotationMatrix.m11; }
    double m12() const { return m_rotationMatrix.m12; }
    double m13() const { return m_rotationMatrix.m13; }
    double m21() const { return m_rotationMatrix.m21; }
    double m22() const { return m_rotationMatrix.m22; }
    double m23() const { return m_rotationMatrix.m23; }
    double m31() const { return m_rotationMatrix.m31; }
    double m32() const { return m_rotationMatrix.m32; }
    double m33() const { return m_rotationMatrix.m33; }
    // Helper method to filter rotation matrix
    void filterRotationMatrix(const RotationMatrix& newMatrix);    
    // Helper method to extract azimuth and altitude from filtered matrix
    void updateOrientationFromMatrix();
    // Get compass bridge status
    double headingAccuracy() const;
    
    // Setters
    void setLocation(const GeoCoordinate &location);
    
    // Q_INVOKABLE methods that can be called from QML
    Q_INVOKABLE void addCustomDSO(const QString &name, double ra, double dec, 
                                    const QUrl &imageUrl, double size, 
                                  int croppedWidth, int croppedHeight, double scaleFactor);
    Q_INVOKABLE void loadDefaultDSOs();
    Q_INVOKABLE void startSensors();
    Q_INVOKABLE void stopSensors();
    Q_INVOKABLE void setGPSAccuracy(int accuracy); // 0=Best, 1=Navigation, 2=Balanced, 3=LowPower
    Q_INVOKABLE void useManualLocation(bool manual);
    Q_INVOKABLE void requestLocationPermission();
    Q_INVOKABLE QVariantList getVisibleSolarSystemObjects() const;
    Q_INVOKABLE void updateSolarSystemObjects();
    Q_INVOKABLE void resetCompassCalibration();
    
signals:
    void azimuthChanged(double azimuth);
    void altitudeChanged(double altitude);
    void visibleDSOsChanged();
    void locationChanged();
    void gpsStatusChanged(bool enabled);
    void locationMetadataChanged();
    void locationStatusChanged(const QString &status);
    void rightAscensionChanged(double ra);
    void declinationChanged(double dec);
    void debugDataChanged();	       
    void visibleSolarSystemObjectsChanged();
    void headingAccuracyChanged(double accuracy);
    
private slots:
    void onAzimuthChanged(double azimuth);
    void onRotationMatrixChanged(const RotationMatrix& matrix);
    void onLocationChanged(GeoCoordinate location);
    void onLocationError(const QString &errorMessage);
    void onLocationAuthorizationChanged(bool authorized);
    void onLocationMetadataChanged();
    void updateVisibleDSOs();
    // Add new slot for compass heading
    void onCompassHeadingChanged(double heading);
    void onCompassCalibrationChanged(bool calibrating);
    void onCompassAccuracyChanged(double accuracy);
    
private:
    // iOS Sensor Bridge
    IOSSensorBridge *m_sensorBridge;
    
    // New CompassBridge
    CompassBridge *m_compassBridge;
    double m_headingAccuracy;

    // Use AstronomyCalculator for celestial calculations
    SolarSystemCalculator *m_solarSystemCalculator;
    QVariantList m_visibleSolarSystemObjects;
  
    // Current orientation
    double m_debugRoll, m_debugPitch, m_debugYaw, m_debugDirX, m_debugDirY, m_debugDirZ;
    double m_azimuth_comp;    // compass direction in degrees (0 = North, 90 = East)
    double m_altitude;   // tilt angle in degrees (-90 = down, 0 = horizontal, 90 = up)
    RotationMatrix m_rotationMatrix;
  
    // Location and time
    GeoCoordinate *m_location = nullptr;
    bool m_manualLocationMode;
    double m_locationAccuracy;
    QString m_locationStatus;
    
    // DSO database
    QList<DSOObject> m_dsoObjects;
    QVariantList m_visibleDSOs;  // Objects currently in view
    
    // View parameters
    double m_fieldOfView;  // Field of view in degrees
    double m_rightAscension;  // in hours
    double m_declination;     // in degrees

    // Matrix history buffer for filtering
    static const int MATRIX_BUFFER_SIZE = 10;
    std::array<RotationMatrix, MATRIX_BUFFER_SIZE> m_matrixBuffer;
    int m_matrixBufferIndex = 0;
    bool m_matrixBufferFilled = false;
    QElapsedTimer m_lastMatrixUpdateTime;
    
    // Helper functions for filtering
    void filterMatrixComponents(const RotationMatrix& newMatrix);
    int findMostFrequentBin(const std::map<int, int>& histogram);
    void processFilteredMatrix(const RotationMatrix& matrix);
};

#endif // SKYVIEWCONTROLLER_H
