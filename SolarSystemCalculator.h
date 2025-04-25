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
    double angularSize;      // Angular size in arcseconds at 1 AU
    double magnitude;        // Absolute magnitude
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
    // Add this method to your SolarSystemCalculator class
    void debugMarsJ2000Position();
    void calculateAccuratePlanetPosition(int ix, const QString&, double, const GeoCoordinate&,
					 double&, double&, double &nce, double &, double&, double&, double&);
    double calculateJulianDate(const QDateTime& dateTime);

private:
    SkyViewController* m_controller;
    QVector<SolarSystemObject> m_objects;
    SolarSystemObject m_sunObject;
    SolarSystemObject m_moonObject;
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
};

#endif // SOLARSYSTEMCALCULATOR_H
