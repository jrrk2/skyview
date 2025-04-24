#ifndef SOLARSYSTEMCALCULATOR_H
#define SOLARSYSTEMCALCULATOR_H

#include <QObject>
#include <QString>
#include <QDateTime>
#include <QVector>
#include <QMap>
#include <QUrl>
#include "GeoCoordinate.h"

// Forward declarations
class SkyViewController;

/**
 * @brief Representation of a solar system object
 */
struct SolarSystemObject {
    int id;                  // Object ID
    QString name;            // Object name
    double semiMajorAxis;    // Semi-major axis in AU
    double eccentricity;     // Eccentricity
    double inclination;      // Inclination in radians
    double longAscNode;      // Longitude of ascending node in radians
    double argPerihelion;    // Argument of perihelion in radians
    double meanAnomaly;      // Mean anomaly in radians at epoch
    double epochJD;          // Epoch as Julian Date
    double angularSize;      // Angular size in arcseconds at 1 AU
    double magnitude;        // Absolute magnitude
    double phaseCoefficient; // Phase coefficient for magnitude calculation
    QUrl imageUrl;           // URL to an image of this object
};

/**
 * @brief Class for calculating positions of solar system objects
 */
class SolarSystemCalculator : public QObject
{
    Q_OBJECT

public:
    explicit SolarSystemCalculator(SkyViewController* parent = nullptr);
    ~SolarSystemCalculator();
    void calculateCurrentPositions();

    /**
     * @brief Initialize the solar system objects
     */
    void initialize();

    /**
     * @brief Calculate position for all solar system objects at the given time
     * @param jd Julian date in TDB/TT scale
     * @param observer Observer's location on Earth
     */
    void updatePositions(double jd, const GeoCoordinate& observer);

    /**
     * @brief Get list of visible solar system objects
     * @return List of visible objects
     */
    QVariantList getVisibleObjects() const;

    /**
     * @brief Set the field of view in degrees
     * @param fov Field of view
     */
    void setFieldOfView(double fov);

private:
    SkyViewController* m_controller;
    QVector<SolarSystemObject> m_objects;
    QVariantList m_visibleObjects;
    double m_fieldOfView;

    /**
     * @brief Calculate the position of a solar system object at a given time
     * @param object Solar system object
     * @param jd Julian date in TDB/TT scale
     * @param earthPos Earth's position vector from Sun
     * @param sunPos Sun's position vector from solar system barycenter
     * @param ra Right ascension (output)
     * @param dec Declination (output)
     * @param distance Distance from Earth in AU (output)
     * @param phase Phase angle (output)
     * @param mag Visual magnitude (output)
     */
    void calculatePosition(const SolarSystemObject& object, double jd, 
                          const QVector3D& earthPos, const QVector3D& sunPos,
                          double& ra, double& dec, double& distance, 
                          double& phase, double& mag);

    /**
     * @brief Set up the planets of the solar system
     */
    void initializePlanets();

    /**
     * @brief Calculate the position of an object using Keplerian elements
     * @param object Object to calculate for
     * @param jd Julian date
     * @param pos Output position vector in AU
     */
    void calculateKeplerianPosition(const SolarSystemObject& object, double jd, QVector3D& pos);
    double calculateMeanMotion(double semiMajorAxis);
};

#endif // SOLARSYSTEMCALCULATOR_H
