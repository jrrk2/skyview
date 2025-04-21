#ifndef ASTRONOMYCALCULATOR_H
#define ASTRONOMYCALCULATOR_H

#include <QDateTime>
#include "geocoordinate.h"

class AstronomyCalculator
{
public:
    AstronomyCalculator();
    
    // Set observer's location and time
    void setLocation(const GeoCoordinate& location);
    void setDateTime(const QDateTime& dateTime);
    
    // Convert between coordinate systems
    void equatorialToHorizontal(double ra, double dec, double* azimuth, double* altitude);
    void horizontalToEquatorial(double azimuth, double altitude, double* ra, double* dec);
    
    // Calculate local sidereal time
    double calculateLST();
    
    // Calculate angular separation between two points in the sky
    double angularSeparation(double az1, double alt1, double az2, double alt2);
    
private:
    GeoCoordinate m_location;
    QDateTime m_dateTime;
    
    // Helper functions
    double degreesToRadians(double degrees) const;
    double radiansToDegrees(double radians) const;
    double normalizeAngle(double angle, double min, double max) const;
};

#endif // ASTRONOMYCALCULATOR_H
