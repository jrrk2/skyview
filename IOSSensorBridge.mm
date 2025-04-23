// IOSSensorBridge.mm
// This file contains the native iOS implementations for sensors

#include "IOSSensorBridge.h"

#import <CoreMotion/CoreMotion.h>
#import <CoreLocation/CoreLocation.h>

// Forward declarations for Objective-C classes
@interface SensorDelegate : NSObject <CLLocationManagerDelegate>
@property (nonatomic, assign) IOSSensorBridge* bridge;
@end

// Implementation of our Objective-C delegate
@implementation SensorDelegate

- (void)locationManager:(CLLocationManager *)manager didUpdateHeading:(CLHeading *)newHeading {
    if (self.bridge) {
        self.bridge->updateHeading(newHeading.magneticHeading);
    }
}

- (void)locationManager:(CLLocationManager *)manager didUpdateLocations:(NSArray<CLLocation *> *)locations {
    if (self.bridge && locations.count > 0) {
        CLLocation* location = [locations lastObject];
        
        // Get basic coordinates
        double latitude = location.coordinate.latitude;
        double longitude = location.coordinate.longitude;
        
        // Get altitude if available
        double altitude = location.altitude;
        
        // Get accuracy information
        double horizontalAccuracy = location.horizontalAccuracy;
        double verticalAccuracy = location.verticalAccuracy;
        
        // Get speed and course if available
        double speed = location.speed;
        double course = location.course;
        
        // Pass all location data to the C++ bridge
        self.bridge->updateLocation(latitude, longitude, altitude, 
                                   horizontalAccuracy, verticalAccuracy,
                                   speed, course);
    }
}

- (void)locationManager:(CLLocationManager *)manager didFailWithError:(NSError *)error {
    if (self.bridge) {
        NSString *errorMessage = [error localizedDescription];
        self.bridge->updateLocationError([errorMessage UTF8String]);
    }
}

- (void)locationManager:(CLLocationManager *)manager didChangeAuthorizationStatus:(CLAuthorizationStatus)status {
    if (self.bridge) {
        bool authorized = (status == kCLAuthorizationStatusAuthorizedWhenInUse || 
                           status == kCLAuthorizationStatusAuthorizedAlways);
        self.bridge->updateLocationAuthorizationStatus(authorized);
    }
}

@end

// C++ implementation using native iOS APIs
class IOSSensorBridgeImpl {
public:
    IOSSensorBridgeImpl(IOSSensorBridge* bridge) : m_bridge(bridge) {
        // Create the motion manager for device motion
        m_motionManager = [[CMMotionManager alloc] init];
        
        // Create location manager for compass heading and GPS
        m_locationManager = [[CLLocationManager alloc] init];
        m_delegate = [[SensorDelegate alloc] init];
        [m_delegate setBridge:bridge];
        [m_locationManager setDelegate:m_delegate];
        
        // Configure location manager
        [m_locationManager setDesiredAccuracy:kCLLocationAccuracyHundredMeters];
        [m_locationManager setDistanceFilter:10.0]; // Update when moved 1 meter
        [m_locationManager setHeadingFilter:1.0];  // 1 degree change
        
        // Set update intervals
        [m_motionManager setDeviceMotionUpdateInterval:0.1]; // 10 Hz
    }
    
    ~IOSSensorBridgeImpl() {
        stopSensors();
        
        // Release resources
        [m_motionManager release];
        [m_locationManager release];
        [m_delegate release];
    }
    
    void startSensors() {
        // Start device motion updates (accelerometer, gyro, magnetometer fusion)
        if ([m_motionManager isDeviceMotionAvailable]) {
            [m_motionManager startDeviceMotionUpdatesToQueue:[NSOperationQueue mainQueue]
                                              withHandler:^(CMDeviceMotion * _Nullable motion, NSError * _Nullable error) {
                if (motion && m_bridge) {
                    // Get the device orientation in space
                    CMAttitude* attitude = motion.attitude;
		    CMRotationMatrix matrix = attitude.rotationMatrix;
                    // Send the attitude data to our C++ bridge
		    m_bridge->updateRotationMatrix(matrix.m11, matrix.m12, matrix.m13,
                             matrix.m21, matrix.m22, matrix.m23,
                             matrix.m31, matrix.m32, matrix.m33);
                }
            }];
        }
        
        // Request location authorization
        [m_locationManager requestWhenInUseAuthorization];
        
        // Start location updates for GPS position
        [m_locationManager startUpdatingLocation];
        
        // Start heading updates for compass direction
        if ([CLLocationManager headingAvailable]) {
            [m_locationManager startUpdatingHeading];
        }
    }
    
    void stopSensors() {
        [m_motionManager stopDeviceMotionUpdates];
        [m_locationManager stopUpdatingLocation];
        [m_locationManager stopUpdatingHeading];
    }
    
    void setGPSAccuracy(IOSSensorBridge::GPSAccuracy accuracy) {
        switch (accuracy) {
            case IOSSensorBridge::GPSAccuracy::Best:
                [m_locationManager setDesiredAccuracy:kCLLocationAccuracyBest];
                break;
            case IOSSensorBridge::Navigation:
                [m_locationManager setDesiredAccuracy:kCLLocationAccuracyBestForNavigation];
                break;
            case IOSSensorBridge::Balanced:
                [m_locationManager setDesiredAccuracy:kCLLocationAccuracyNearestTenMeters];
                break;
            case IOSSensorBridge::LowPower:
                [m_locationManager setDesiredAccuracy:kCLLocationAccuracyHundredMeters];
                break;
        }
    }
    
    void setGPSUpdateInterval(double meters) {
        [m_locationManager setDistanceFilter:meters];
    }
    
    bool isGPSAvailable() {
        return [CLLocationManager locationServicesEnabled];
    }
    
    bool isCompassAvailable() {
        return [CLLocationManager headingAvailable];
    }
    
private:
    IOSSensorBridge* m_bridge;
    CMMotionManager* m_motionManager;
    CLLocationManager* m_locationManager;
    SensorDelegate* m_delegate;
};

// Implementation of our C++ bridge class
IOSSensorBridge::IOSSensorBridge(QObject* parent) 
    : QObject(parent), 
      m_azimuth(0.0), 
      m_gpsEnabled(false),
      m_locationAuthorized(false),
      m_lastGPSError(""),
      m_locationAccuracy(0.0),
      m_locationSpeed(0.0),
      m_locationCourse(0.0) {
    m_implementation = new IOSSensorBridgeImpl(this);
}

IOSSensorBridge::~IOSSensorBridge() {
    delete m_implementation;
}

void IOSSensorBridge::startSensors() {
    m_implementation->startSensors();
}

void IOSSensorBridge::stopSensors() {
    m_implementation->stopSensors();
}

double IOSSensorBridge::azimuth() const {
    return m_azimuth;
}

GeoCoordinate IOSSensorBridge::location() const {
    return m_location;
}

bool IOSSensorBridge::isGPSAvailable() const {
    return m_implementation->isGPSAvailable();
}

bool IOSSensorBridge::isCompassAvailable() const {
    return m_implementation->isCompassAvailable();
}

void IOSSensorBridge::setGPSAccuracy(GPSAccuracy accuracy) {
    m_implementation->setGPSAccuracy(accuracy);
}

void IOSSensorBridge::setGPSUpdateInterval(double meters) {
    m_implementation->setGPSUpdateInterval(meters);
}

QString IOSSensorBridge::lastGPSError() const {
    return m_lastGPSError;
}

bool IOSSensorBridge::isLocationAuthorized() const {
    return m_locationAuthorized;
}

double IOSSensorBridge::locationAccuracy() const {
    return m_locationAccuracy;
}

double IOSSensorBridge::locationSpeed() const {
    return m_locationSpeed;
}

double IOSSensorBridge::locationCourse() const {
    return m_locationCourse;
}

// Internal callback methods - called from the Objective-C layer
void IOSSensorBridge::updateHeading(double heading) {
    m_azimuth = heading;
    emit azimuthChanged(m_azimuth);
}

void IOSSensorBridge::updateLocation(double latitude, double longitude, double altitude,
                                   double horizontalAccuracy, double verticalAccuracy,
                                   double speed, double course) {
    // Update the location with altitude if available
    if (verticalAccuracy >= 0) {
        m_location = GeoCoordinate(latitude, longitude, altitude);
    } else {
        m_location = GeoCoordinate(latitude, longitude);
    }
    
    // Store additional metadata
    m_locationAccuracy = horizontalAccuracy;
    m_locationSpeed = speed;
    m_locationCourse = course;
    
    // Signal that we have new GPS data
    m_gpsEnabled = true;
    emit locationChanged(m_location);
    emit locationMetadataChanged();
}

void IOSSensorBridge::updateLocationError(const std::string& errorMessage) {
    m_lastGPSError = QString::fromStdString(errorMessage);
    emit locationErrorOccurred(m_lastGPSError);
}

void IOSSensorBridge::updateLocationAuthorizationStatus(bool authorized) {
    m_locationAuthorized = authorized;
    emit locationAuthorizationChanged(m_locationAuthorized);
}
