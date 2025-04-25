#include "CompassBridge.h"

#import <CoreLocation/CoreLocation.h>
#import <Foundation/Foundation.h>

// Forward declarations for Objective-C classes
@interface CompassDelegate : NSObject <CLLocationManagerDelegate>
@property (nonatomic, assign) CompassBridge* bridge;
@property (nonatomic, assign) BOOL isCalibrating;
@end

// Implementation of our Objective-C delegate
@implementation CompassDelegate

- (id)initWithBridge:(CompassBridge*)bridge
{
    self = [super init];
    if (self) {
        _bridge = bridge;
        _isCalibrating = NO;
    }
    return self;
}

- (void)locationManager:(CLLocationManager *)manager didUpdateHeading:(CLHeading *)newHeading
{
    if (self.bridge) {
        if (newHeading.headingAccuracy < 0) {
            // Accuracy is invalid, might be calibrating
            if (!_isCalibrating) {
                _isCalibrating = YES;
                self.bridge->updateCalibrationStatus(true);
            }
            return;
        } else if (_isCalibrating && newHeading.headingAccuracy >= 0) {
            // Finished calibrating
            _isCalibrating = NO;
            self.bridge->updateCalibrationStatus(false);
        }
        
        // Get magnetic heading
        CLLocationDirection heading = newHeading.magneticHeading;
        
        // Log raw heading value for debugging
        // NSLog(@"Raw heading: %.2f degrees", heading);
        
        // Pass raw heading and accuracy to the C++ bridge for now
        // We'll add correction in SkyViewController
        self.bridge->updateHeading(heading, newHeading.headingAccuracy);
    }
}

- (BOOL)locationManagerShouldDisplayHeadingCalibration:(CLLocationManager *)manager
{
    // Return YES to allow heading calibration (figure 8 pattern)
    return YES;
}

@end

// C++ implementation using native iOS APIs
class CompassBridgeImpl {
public:
    CompassBridgeImpl(CompassBridge* bridge) : m_bridge(bridge) {
        // Create location manager for compass heading
        m_locationManager = [[CLLocationManager alloc] init];
        m_delegate = [[CompassDelegate alloc] initWithBridge:bridge];
        [m_locationManager setDelegate:m_delegate];
        
        // Configure just for heading updates
        [m_locationManager setHeadingFilter:1.0];  // 1 degree change
        [m_locationManager setHeadingOrientation:CLDeviceOrientationPortrait];
    }
    
    ~CompassBridgeImpl() {
        stopCompass();
        
        // Release resources
        [m_locationManager release];
        [m_delegate release];
    }
    
    void startCompass() {
        // Request location authorization
        if ([m_locationManager respondsToSelector:@selector(requestWhenInUseAuthorization)]) {
            [m_locationManager requestWhenInUseAuthorization];
        }
        
        // Start heading updates
        if ([CLLocationManager headingAvailable]) {
            [m_locationManager startUpdatingHeading];
        } else {
            NSLog(@"Warning: Compass heading is not available on this device!");
        }
    }
    
    void stopCompass() {
        [m_locationManager stopUpdatingHeading];
    }
    
    bool isCompassAvailable() {
        return [CLLocationManager headingAvailable];
    }
    
    void resetCalibration() {
        // This doesn't directly reset calibration, but forces iOS to recalibrate
        [m_locationManager stopUpdatingHeading];
        [m_locationManager startUpdatingHeading];
    }
    
private:
    CompassBridge* m_bridge;
    CLLocationManager* m_locationManager;
    CompassDelegate* m_delegate;
};

// Implementation of our C++ bridge class
CompassBridge::CompassBridge(QObject* parent) 
    : QObject(parent), 
      m_heading(0.0),
      m_calibrating(false),
      m_headingAccuracy(0.0)
{
    m_implementation = new CompassBridgeImpl(this);
}

CompassBridge::~CompassBridge() 
{
    delete m_implementation;
}

void CompassBridge::startCompass()
{
    m_implementation->startCompass();
}

void CompassBridge::stopCompass()
{
    m_implementation->stopCompass();
}

bool CompassBridge::isCompassAvailable() const
{
    return m_implementation->isCompassAvailable();
}

void CompassBridge::resetCalibration()
{
    m_implementation->resetCalibration();
}

double CompassBridge::heading() const
{
    return m_heading;
}

bool CompassBridge::isCalibrating() const
{
    return m_calibrating;
}

double CompassBridge::headingAccuracy() const
{
    return m_headingAccuracy;
}

// Internal callback methods - called from the Objective-C layer
void CompassBridge::updateHeading(double heading, double accuracy)
{
    // Update heading
    if (m_heading != heading) {
        m_heading = heading;
        emit headingChanged(m_heading);
    }
    
    // Update accuracy
    if (m_headingAccuracy != accuracy) {
        m_headingAccuracy = accuracy;
        emit headingAccuracyChanged(m_headingAccuracy);
    }
}

void CompassBridge::updateCalibrationStatus(bool calibrating)
{
    if (m_calibrating != calibrating) {
        m_calibrating = calibrating;
        emit calibrationChanged(m_calibrating);
    }
}
