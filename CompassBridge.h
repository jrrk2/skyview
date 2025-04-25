#ifndef COMPASSBRIDGE_H
#define COMPASSBRIDGE_H

#include <QObject>
#include <string>

// Forward declaration of implementation class
class CompassBridgeImpl;

// C++ bridge class
class CompassBridge : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double heading READ heading NOTIFY headingChanged)
    Q_PROPERTY(bool isCalibrating READ isCalibrating NOTIFY calibrationChanged)
    Q_PROPERTY(double headingAccuracy READ headingAccuracy NOTIFY headingAccuracyChanged)
    
public:
    explicit CompassBridge(QObject* parent = nullptr);
    ~CompassBridge();
    
    // Control methods
    Q_INVOKABLE void startCompass();
    Q_INVOKABLE void stopCompass();
    Q_INVOKABLE bool isCompassAvailable() const;
    Q_INVOKABLE void resetCalibration();
    
    // Property getters
    double heading() const;
    bool isCalibrating() const;
    double headingAccuracy() const;
    
    // Methods called from Objective-C code
    void updateHeading(double heading, double accuracy);
    void updateCalibrationStatus(bool calibrating);
    
signals:
    void headingChanged(double heading);
    void calibrationChanged(bool calibrating);
    void headingAccuracyChanged(double accuracy);
    
private:
    CompassBridgeImpl* m_implementation;
    
    // Cached values
    double m_heading;
    bool m_calibrating;
    double m_headingAccuracy;
};

#endif // COMPASSBRIDGE_H
