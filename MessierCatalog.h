#ifndef MESSIER_CATALOG_H
#define MESSIER_CATALOG_H

#include <vector>
#include <string>

// Messier object types
enum class ObjectType {
    GlobularCluster,
    OpenCluster,
    Nebula,
    PlanetaryNebula,
    SupernovaRemnant,
    Galaxy,
    GalaxyCluster,
    DoubleStar,
    Asterism,
    StarCloud,
    Other
};

// Convert object type to string
inline const char* objectTypeToString(ObjectType type) {
    switch (type) {
        case ObjectType::GlobularCluster: return "Globular Cluster";
        case ObjectType::OpenCluster: return "Open Cluster";
        case ObjectType::Nebula: return "Nebula";
        case ObjectType::PlanetaryNebula: return "Planetary Nebula";
        case ObjectType::SupernovaRemnant: return "Supernova Remnant";
        case ObjectType::Galaxy: return "Galaxy";
        case ObjectType::GalaxyCluster: return "Galaxy Cluster";
        case ObjectType::DoubleStar: return "Double Star";
        case ObjectType::Asterism: return "Asterism";
        case ObjectType::StarCloud: return "Star Cloud";
        case ObjectType::Other: return "Other";
    }
    return "Unknown";
}

// Messier object structure
struct MessierObject {
    int id;
    std::string name;
    std::string commonName;  // Empty if none
    ObjectType objectType;
    std::string constellation;
    double raHours;
    double decDegrees;
    double magnitude;
    double distanceKly;
    double sizeArcminWidth;
    double sizeArcminHeight;
    std::string description;
    std::string imageUrl;
    int discoveryYear;  // -1 if unknown
    std::string bestViewed;
    int croppedWidth;      // Width of cropped image in pixels
    int croppedHeight;     // Height of cropped image in pixels
    double scaleFactor;    // Recommended UI scale factor
    int displaySize;       // Recommended display size in pixels
};

// Complete Messier catalog
const std::vector<MessierObject> MessierCatalog = {
    {
        1, // id
        "M1", // name
        "Crab Nebula", // common name
        ObjectType::SupernovaRemnant, // object type
        "Taurus", // constellation
        5.57556, // RA (hours)
        22.0133, // Dec (degrees)
        20, // magnitude
        6.5, // distance (kly)
        6, // width (arcmin)
        4, // height (arcmin)
        "Remains of a supernova observed in 1054 AD", // description
        "images/m1.jpg", // image URL
        1731, // discovery year
        "Winter", // best viewed
        400, // cropped width (px)
        263, // cropped height (px)
        0.489173, // scale factor
        47  // display size (px)
    },
    {
        3, // id
        "M3", // name
        "", // common name
        ObjectType::GlobularCluster, // object type
        "Canes Venatici", // constellation
        13.7032, // RA (hours)
        28.3773, // Dec (degrees)
        6.4, // magnitude
        33.9, // distance (kly)
        18, // width (arcmin)
        18, // height (arcmin)
        "Contains approximately 500,000 stars", // description
        "images/m3.jpg", // image URL
        1764, // discovery year
        "Spring", // best viewed
        400, // cropped width (px)
        263, // cropped height (px)
        1.7999, // scale factor
        150  // display size (px)
    },
    {
        13, // id
        "M13", // name
        "Hercules Globular Cluster", // common name
        ObjectType::GlobularCluster, // object type
        "Hercules", // constellation
        16.6949, // RA (hours)
        36.4613, // Dec (degrees)
        5.8, // magnitude
        22.2, // distance (kly)
        20, // width (arcmin)
        20, // height (arcmin)
        "Contains several hundred thousand stars", // description
        "images/m13.jpg", // image URL
        1714, // discovery year
        "Summer", // best viewed
        400, // cropped width (px)
        247, // cropped height (px)
        1.99875, // scale factor
        150  // display size (px)
    },
    {
        16, // id
        "M16", // name
        "Eagle Nebula", // common name
        ObjectType::OpenCluster, // object type
        "Serpens", // constellation
        18.3125, // RA (hours)
        -13.7917, // Dec (degrees)
        6, // magnitude
        7, // distance (kly)
        35, // width (arcmin)
        28, // height (arcmin)
        "Contains the famous 'Pillars of Creation'", // description
        "images/m16.jpg", // image URL
        1746, // discovery year
        "Summer", // best viewed
        400, // cropped width (px)
        267, // cropped height (px)
        3.12923, // scale factor
        150  // display size (px)
    },
    {
        17, // id
        "M17", // name
        "Omega Nebula", // common name
        ObjectType::Nebula, // object type
        "Sagittarius", // constellation
        18.3464, // RA (hours)
        -16.1717, // Dec (degrees)
        20, // magnitude
        5, // distance (kly)
        11, // width (arcmin)
        11, // height (arcmin)
        "Also known as the Swan Nebula or Horseshoe Nebula", // description
        "images/m17.jpg", // image URL
        1745, // discovery year
        "Summer", // best viewed
        400, // cropped width (px)
        270, // cropped height (px)
        1.0988, // scale factor
        107  // display size (px)
    },
    {
        27, // id
        "M27", // name
        "Dumbbell Nebula", // common name
        ObjectType::PlanetaryNebula, // object type
        "Vulpecula", // constellation
        19.9934, // RA (hours)
        22.7212, // Dec (degrees)
        14.1, // magnitude
        1.2, // distance (kly)
        8, // width (arcmin)
        5.7, // height (arcmin)
        "One of the brightest planetary nebulae in the sky", // description
        "images/m27.jpg", // image URL
        1764, // discovery year
        "Summer", // best viewed
        400, // cropped width (px)
        268, // cropped height (px)
        0.675007, // scale factor
        65  // display size (px)
    },
    {
        31, // id
        "M31", // name
        "Andromeda Galaxy", // common name
        ObjectType::Galaxy, // object type
        "Andromeda", // constellation
        0.712314, // RA (hours)
        41.2687, // Dec (degrees)
        3.4, // magnitude
        2500, // distance (kly)
        178, // width (arcmin)
        63, // height (arcmin)
        "The nearest major galaxy to the Milky Way", // description
        "images/m31.jpg", // image URL
        964, // discovery year
        "Autumn", // best viewed
        1024, // cropped width (px)
        1024, // cropped height (px)
        10.5888, // scale factor
        200  // display size (px)
    },
    {
        32, // id
        "M32", // name
        "", // common name
        ObjectType::Galaxy, // object type
        "Andromeda", // constellation
        0.711618, // RA (hours)
        40.8652, // Dec (degrees)
        8.1, // magnitude
        2900, // distance (kly)
        8.7, // width (arcmin)
        6.5, // height (arcmin)
        "A satellite galaxy of the Andromeda Galaxy", // description
        "images/m32.jpg", // image URL
        1749, // discovery year
        "Autumn", // best viewed
        155, // cropped width (px)
        400, // cropped height (px)
        0.751565, // scale factor
        73  // display size (px)
    },
    {
        34, // id
        "M34", // name
        "", // common name
        ObjectType::OpenCluster, // object type
        "Perseus", // constellation
        2.70194, // RA (hours)
        42.7217, // Dec (degrees)
        20, // magnitude
        1.4, // distance (kly)
        35, // width (arcmin)
        35, // height (arcmin)
        "Contains about 100 stars and spans 35 light years", // description
        "images/m34.jpg", // image URL
        1764, // discovery year
        "Autumn", // best viewed
        400, // cropped width (px)
        261, // cropped height (px)
        3.49935, // scale factor
        150  // display size (px)
    },
    {
        35, // id
        "M35", // name
        "", // common name
        ObjectType::OpenCluster, // object type
        "Gemini", // constellation
        6.15139, // RA (hours)
        24.3367, // Dec (degrees)
        20, // magnitude
        2.8, // distance (kly)
        28, // width (arcmin)
        28, // height (arcmin)
        "A large open cluster visible to the naked eye", // description
        "images/m35.jpg", // image URL
        1745, // discovery year
        "Winter", // best viewed
        400, // cropped width (px)
        250, // cropped height (px)
        2.79825, // scale factor
        150  // display size (px)
    },
    {
        36, // id
        "M36", // name
        "", // common name
        ObjectType::OpenCluster, // object type
        "Auriga", // constellation
        5.60556, // RA (hours)
        34.135, // Dec (degrees)
        6, // magnitude
        4.1, // distance (kly)
        12, // width (arcmin)
        12, // height (arcmin)
        "A young open cluster in Auriga", // description
        "images/m36.jpg", // image URL
        1764, // discovery year
        "Winter", // best viewed
        400, // cropped width (px)
        257, // cropped height (px)
        1.19925, // scale factor
        117  // display size (px)
    },
    {
        37, // id
        "M37", // name
        "", // common name
        ObjectType::OpenCluster, // object type
        "Auriga", // constellation
        5.87167, // RA (hours)
        32.545, // Dec (degrees)
        5.6, // magnitude
        4.5, // distance (kly)
        24, // width (arcmin)
        24, // height (arcmin)
        "The richest open cluster in Auriga", // description
        "images/m37.jpg", // image URL
        1764, // discovery year
        "Winter", // best viewed
        400, // cropped width (px)
        249, // cropped height (px)
        2.3985, // scale factor
        150  // display size (px)
    },
    {
        38, // id
        "M38", // name
        "", // common name
        ObjectType::OpenCluster, // object type
        "Auriga", // constellation
        5.47778, // RA (hours)
        35.8233, // Dec (degrees)
        6.4, // magnitude
        4.2, // distance (kly)
        21, // width (arcmin)
        21, // height (arcmin)
        "Contains a distinctive cruciform pattern of stars", // description
        "images/m38.jpg", // image URL
        1764, // discovery year
        "Winter", // best viewed
        400, // cropped width (px)
        259, // cropped height (px)
        2.0992, // scale factor
        150  // display size (px)
    },
    {
        40, // id
        "M40", // name
        "", // common name
        ObjectType::DoubleStar, // object type
        "Ursa Major", // constellation
        12.37, // RA (hours)
        58.0833, // Dec (degrees)
        20, // magnitude
        0.5, // distance (kly)
        0.8, // width (arcmin)
        0.8, // height (arcmin)
        "Actually a double star system, not a deep sky object", // description
        "images/m40.jpg", // image URL
        1764, // discovery year
        "Spring", // best viewed
        400, // cropped width (px)
        260, // cropped height (px)
        0.07995, // scale factor
        40  // display size (px)
    },
    {
        41, // id
        "M41", // name
        "", // common name
        ObjectType::OpenCluster, // object type
        "Canis Major", // constellation
        6.76667, // RA (hours)
        -20.7167, // Dec (degrees)
        4.5, // magnitude
        2.3, // distance (kly)
        38, // width (arcmin)
        38, // height (arcmin)
        "A bright open cluster easily visible with binoculars", // description
        "images/m41.jpg", // image URL
        1749, // discovery year
        "Winter", // best viewed
        400, // cropped width (px)
        254, // cropped height (px)
        3.79865, // scale factor
        150  // display size (px)
    },
    {
        42, // id
        "M42", // name
        "Orion Nebula", // common name
        ObjectType::Nebula, // object type
        "Orion", // constellation
        5.58814, // RA (hours)
        -5.39111, // Dec (degrees)
        20, // magnitude
        1.3, // distance (kly)
        85, // width (arcmin)
        60, // height (arcmin)
        "One of the brightest nebulae visible to the naked eye", // description
        "images/m42.jpg", // image URL
        1610, // discovery year
        "Winter", // best viewed
        147, // cropped width (px)
        400, // cropped height (px)
        7.14012, // scale factor
        150  // display size (px)
    },
    {
        43, // id
        "M43", // name
        "", // common name
        ObjectType::Nebula, // object type
        "Orion", // constellation
        5.59194, // RA (hours)
        -5.27, // Dec (degrees)
        20, // magnitude
        1.6, // distance (kly)
        20, // width (arcmin)
        15, // height (arcmin)
        "Part of the Orion Nebula complex", // description
        "images/m43.jpg", // image URL
        1769, // discovery year
        "Winter", // best viewed
        400, // cropped width (px)
        270, // cropped height (px)
        1.73067, // scale factor
        150  // display size (px)
    },
    {
        44, // id
        "M44", // name
        "Beehive Cluster", // common name
        ObjectType::OpenCluster, // object type
        "Cancer", // constellation
        8.67028, // RA (hours)
        19.6217, // Dec (degrees)
        20, // magnitude
        0.6, // distance (kly)
        95, // width (arcmin)
        95, // height (arcmin)
        "Also known as Praesepe, visible to naked eye", // description
        "images/m44.jpg", // image URL
        -260, // discovery year
        "Winter", // best viewed
        400, // cropped width (px)
        270, // cropped height (px)
        9.4997, // scale factor
        150  // display size (px)
    },
    {
        45, // id
        "M45", // name
        "Pleiades", // common name
        ObjectType::OpenCluster, // object type
        "Taurus", // constellation
        3.77333, // RA (hours)
        24.1133, // Dec (degrees)
        20, // magnitude
        0.4, // distance (kly)
        110, // width (arcmin)
        110, // height (arcmin)
        "The Seven Sisters, visible to naked eye", // description
        "images/m45.jpg", // image URL
        -1000, // discovery year
        "Winter", // best viewed
        400, // cropped width (px)
        270, // cropped height (px)
        10.9983, // scale factor
        150  // display size (px)
    },
    {
        46, // id
        "M46", // name
        "", // common name
        ObjectType::OpenCluster, // object type
        "Puppis", // constellation
        7.69639, // RA (hours)
        -14.8433, // Dec (degrees)
        20, // magnitude
        5.4, // distance (kly)
        27, // width (arcmin)
        27, // height (arcmin)
        "Contains a planetary nebula within the cluster", // description
        "images/m46.jpg", // image URL
        1771, // discovery year
        "Winter", // best viewed
        400, // cropped width (px)
        251, // cropped height (px)
        2.69985, // scale factor
        150  // display size (px)
    },
    {
        47, // id
        "M47", // name
        "", // common name
        ObjectType::OpenCluster, // object type
        "Puppis", // constellation
        7.60972, // RA (hours)
        -14.4883, // Dec (degrees)
        20, // magnitude
        1.6, // distance (kly)
        30, // width (arcmin)
        30, // height (arcmin)
        "A bright, large open cluster in Puppis", // description
        "images/m47.jpg", // image URL
        1771, // discovery year
        "Winter", // best viewed
        400, // cropped width (px)
        246, // cropped height (px)
        2.99915, // scale factor
        150  // display size (px)
    },
    {
        48, // id
        "M48", // name
        "", // common name
        ObjectType::OpenCluster, // object type
        "Hydra", // constellation
        8.2275, // RA (hours)
        -5.72667, // Dec (degrees)
        20, // magnitude
        1.5, // distance (kly)
        54, // width (arcmin)
        54, // height (arcmin)
        "A large open cluster visible with binoculars", // description
        "images/m48.jpg", // image URL
        1771, // discovery year
        "Winter", // best viewed
        400, // cropped width (px)
        246, // cropped height (px)
        5.3997, // scale factor
        150  // display size (px)
    },
    {
        50, // id
        "M50", // name
        "", // common name
        ObjectType::OpenCluster, // object type
        "Monoceros", // constellation
        7.04653, // RA (hours)
        -8.33778, // Dec (degrees)
        20, // magnitude
        3, // distance (kly)
        16, // width (arcmin)
        16, // height (arcmin)
        "Contains about 200 stars in a heart-shaped pattern", // description
        "images/m50.jpg", // image URL
        1772, // discovery year
        "Winter", // best viewed
        400, // cropped width (px)
        250, // cropped height (px)
        1.599, // scale factor
        150  // display size (px)
    },
    {
        51, // id
        "M51", // name
        "Whirlpool Galaxy", // common name
        ObjectType::Galaxy, // object type
        "Canes Venatici", // constellation
        13.498, // RA (hours)
        47.1953, // Dec (degrees)
        8.4, // magnitude
        23000, // distance (kly)
        11.2, // width (arcmin)
        6.9, // height (arcmin)
        "A classic example of a spiral galaxy", // description
        "images/m51.jpg", // image URL
        1773, // discovery year
        "Spring", // best viewed
        400, // cropped width (px)
        268, // cropped height (px)
        0.878051, // scale factor
        85  // display size (px)
    },
    {
        52, // id
        "M52", // name
        "", // common name
        ObjectType::OpenCluster, // object type
        "Cassiopeia", // constellation
        23.4131, // RA (hours)
        61.59, // Dec (degrees)
        20, // magnitude
        5, // distance (kly)
        13, // width (arcmin)
        13, // height (arcmin)
        "A rich open cluster in Cassiopeia", // description
        "images/m52.jpg", // image URL
        1774, // discovery year
        "Autumn", // best viewed
        400, // cropped width (px)
        261, // cropped height (px)
        1.2997, // scale factor
        126  // display size (px)
    },
    {
        61, // id
        "M61", // name
        "", // common name
        ObjectType::Galaxy, // object type
        "Virgo", // constellation
        12.3653, // RA (hours)
        4.47378, // Dec (degrees)
        9.7, // magnitude
        52.5, // distance (kly)
        6.5, // width (arcmin)
        5.9, // height (arcmin)
        "A spiral galaxy in the Virgo Cluster", // description
        "images/m61.jpg", // image URL
        1779, // discovery year
        "Spring", // best viewed
        400, // cropped width (px)
        251, // cropped height (px)
        0.618336, // scale factor
        60  // display size (px)
    },
    {
        63, // id
        "M63", // name
        "Sunflower Galaxy", // common name
        ObjectType::Galaxy, // object type
        "Canes Venatici", // constellation
        13.2637, // RA (hours)
        42.0294, // Dec (degrees)
        8.6, // magnitude
        37, // distance (kly)
        12.6, // width (arcmin)
        7.2, // height (arcmin)
        "A spiral galaxy with well-defined arms", // description
        "images/m63.jpg", // image URL
        1779, // discovery year
        "Spring", // best viewed
        400, // cropped width (px)
        270, // cropped height (px)
        0.951681, // scale factor
        92  // display size (px)
    },
    {
        65, // id
        "M65", // name
        "", // common name
        ObjectType::Galaxy, // object type
        "Leo", // constellation
        11.3155, // RA (hours)
        13.0923, // Dec (degrees)
        20, // magnitude
        35, // distance (kly)
        9.8, // width (arcmin)
        2.9, // height (arcmin)
        "Member of the Leo Triplet group of galaxies", // description
        "images/m65.jpg", // image URL
        1780, // discovery year
        "Spring", // best viewed
        400, // cropped width (px)
        252, // cropped height (px)
        0.532203, // scale factor
        51  // display size (px)
    },
    {
        66, // id
        "M66", // name
        "", // common name
        ObjectType::Galaxy, // object type
        "Leo", // constellation
        11.3375, // RA (hours)
        12.9913, // Dec (degrees)
        8.9, // magnitude
        35, // distance (kly)
        9.1, // width (arcmin)
        4.2, // height (arcmin)
        "Member of the Leo Triplet group of galaxies", // description
        "images/m66.jpg", // image URL
        1780, // discovery year
        "Spring", // best viewed
        400, // cropped width (px)
        253, // cropped height (px)
        0.61627, // scale factor
        60  // display size (px)
    },
    {
        67, // id
        "M67", // name
        "", // common name
        ObjectType::OpenCluster, // object type
        "Cancer", // constellation
        8.85639, // RA (hours)
        11.8133, // Dec (degrees)
        20, // magnitude
        2.7, // distance (kly)
        30, // width (arcmin)
        30, // height (arcmin)
        "One of the oldest known open clusters", // description
        "images/m67.jpg", // image URL
        1779, // discovery year
        "Winter", // best viewed
        400, // cropped width (px)
        250, // cropped height (px)
        2.99915, // scale factor
        150  // display size (px)
    },
    {
        74, // id
        "M74", // name
        "", // common name
        ObjectType::Galaxy, // object type
        "Pisces", // constellation
        1.6116, // RA (hours)
        15.7836, // Dec (degrees)
        9.5, // magnitude
        32, // distance (kly)
        10.2, // width (arcmin)
        9.5, // height (arcmin)
        "A face-on spiral galaxy with well-defined arms", // description
        "images/m74.jpg", // image URL
        1780, // discovery year
        "Autumn", // best viewed
        400, // cropped width (px)
        263, // cropped height (px)
        0.983383, // scale factor
        95  // display size (px)
    },
    {
        76, // id
        "M76", // name
        "Little Dumbbell Nebula", // common name
        ObjectType::PlanetaryNebula, // object type
        "Perseus", // constellation
        1.70546, // RA (hours)
        51.5754, // Dec (degrees)
        17.5, // magnitude
        3.4, // distance (kly)
        2.7, // width (arcmin)
        1.8, // height (arcmin)
        "A small, faint planetary nebula", // description
        "images/m76.jpg", // image URL
        1780, // discovery year
        "Autumn", // best viewed
        400, // cropped width (px)
        258, // cropped height (px)
        0.218851, // scale factor
        40  // display size (px)
    },
    {
        77, // id
        "M77", // name
        "", // common name
        ObjectType::Galaxy, // object type
        "Cetus", // constellation
        2.71131, // RA (hours)
        -0.013294, // Dec (degrees)
        8.9, // magnitude
        47, // distance (kly)
        7.1, // width (arcmin)
        6, // height (arcmin)
        "A barred spiral galaxy and Seyfert galaxy", // description
        "images/m77.jpg", // image URL
        1780, // discovery year
        "Autumn", // best viewed
        400, // cropped width (px)
        270, // cropped height (px)
        0.651603, // scale factor
        63  // display size (px)
    },
    {
        78, // id
        "M78", // name
        "", // common name
        ObjectType::Nebula, // object type
        "Orion", // constellation
        5.77939, // RA (hours)
        0.079167, // Dec (degrees)
        20, // magnitude
        1.6, // distance (kly)
        8, // width (arcmin)
        6, // height (arcmin)
        "A reflection nebula in the constellation Orion", // description
        "images/m78.jpg", // image URL
        1780, // discovery year
        "Winter", // best viewed
        400, // cropped width (px)
        262, // cropped height (px)
        0.691795, // scale factor
        67  // display size (px)
    },
    {
        81, // id
        "M81", // name
        "Bode's Galaxy", // common name
        ObjectType::Galaxy, // object type
        "Ursa Major", // constellation
        9.92588, // RA (hours)
        69.0653, // Dec (degrees)
        6.9, // magnitude
        11.8, // distance (kly)
        26.9, // width (arcmin)
        14.1, // height (arcmin)
        "A grand design spiral galaxy", // description
        "images/m81.jpg", // image URL
        1774, // discovery year
        "Spring", // best viewed
        374, // cropped width (px)
        400, // cropped height (px)
        1.94625, // scale factor
        150  // display size (px)
    },
    {
        82, // id
        "M82", // name
        "Cigar Galaxy", // common name
        ObjectType::Galaxy, // object type
        "Ursa Major", // constellation
        9.93123, // RA (hours)
        69.6797, // Dec (degrees)
        8.4, // magnitude
        12, // distance (kly)
        11.2, // width (arcmin)
        4.3, // height (arcmin)
        "A starburst galaxy with intense star formation", // description
        "images/m82.jpg", // image URL
        1774, // discovery year
        "Spring", // best viewed
        232, // cropped width (px)
        400, // cropped height (px)
        0.692506, // scale factor
        67  // display size (px)
    },
    {
        95, // id
        "M95", // name
        "", // common name
        ObjectType::Galaxy, // object type
        "Leo", // constellation
        10.7327, // RA (hours)
        11.7037, // Dec (degrees)
        9.7, // magnitude
        38, // distance (kly)
        7.4, // width (arcmin)
        5, // height (arcmin)
        "A barred spiral galaxy in the Leo I group", // description
        "images/m95.jpg", // image URL
        1781, // discovery year
        "Spring", // best viewed
        400, // cropped width (px)
        253, // cropped height (px)
        0.606329, // scale factor
        59  // display size (px)
    },
    {
        97, // id
        "M97", // name
        "Owl Nebula", // common name
        ObjectType::PlanetaryNebula, // object type
        "Ursa Major", // constellation
        11.2466, // RA (hours)
        55.019, // Dec (degrees)
        15.8, // magnitude
        2, // distance (kly)
        3.4, // width (arcmin)
        3.3, // height (arcmin)
        "A planetary nebula that resembles an owl's face", // description
        "images/m97.jpg", // image URL
        1781, // discovery year
        "Spring", // best viewed
        400, // cropped width (px)
        267, // cropped height (px)
        0.333086, // scale factor
        40  // display size (px)
    },
    {
        100, // id
        "M100", // name
        "", // common name
        ObjectType::Galaxy, // object type
        "Coma Berenices", // constellation
        12.3819, // RA (hours)
        15.8223, // Dec (degrees)
        9.3, // magnitude
        55, // distance (kly)
        7.4, // width (arcmin)
        6.3, // height (arcmin)
        "A grand design spiral galaxy in the Virgo Cluster", // description
        "images/m100.jpg", // image URL
        1781, // discovery year
        "Spring", // best viewed
        400, // cropped width (px)
        270, // cropped height (px)
        0.681513, // scale factor
        66  // display size (px)
    },
    {
        101, // id
        "M101", // name
        "Pinwheel Galaxy", // common name
        ObjectType::Galaxy, // object type
        "Ursa Major", // constellation
        14.0535, // RA (hours)
        54.3488, // Dec (degrees)
        7.9, // magnitude
        27, // distance (kly)
        28.8, // width (arcmin)
        26.9, // height (arcmin)
        "A face-on spiral galaxy with prominent arms", // description
        "images/m101.jpg", // image URL
        1781, // discovery year
        "Spring", // best viewed
        400, // cropped width (px)
        258, // cropped height (px)
        2.7823, // scale factor
        150  // display size (px)
    },
    {
        102, // id
        "M102", // name
        "", // common name
        ObjectType::Galaxy, // object type
        "Draco", // constellation
        15.1082, // RA (hours)
        55.7633, // Dec (degrees)
        9.9, // magnitude
        30, // distance (kly)
        5.2, // width (arcmin)
        2.3, // height (arcmin)
        "A lenticular or spiral galaxy in Draco", // description
        "images/m102.jpg", // image URL
        1781, // discovery year
        "Summer", // best viewed
        400, // cropped width (px)
        256, // cropped height (px)
        0.345083, // scale factor
        40  // display size (px)
    },
    {
        103, // id
        "M103", // name
        "", // common name
        ObjectType::OpenCluster, // object type
        "Cassiopeia", // constellation
        1.55583, // RA (hours)
        60.6583, // Dec (degrees)
        7.4, // magnitude
        8.5, // distance (kly)
        6, // width (arcmin)
        6, // height (arcmin)
        "A relatively young open cluster in Cassiopeia", // description
        "images/m103.jpg", // image URL
        1781, // discovery year
        "Autumn", // best viewed
        400, // cropped width (px)
        260, // cropped height (px)
        0.5986, // scale factor
        58  // display size (px)
    },
    {
        105, // id
        "M105", // name
        "", // common name
        ObjectType::Galaxy, // object type
        "Leo", // constellation
        10.7971, // RA (hours)
        12.5816, // Dec (degrees)
        9.8, // magnitude
        32, // distance (kly)
        5.4, // width (arcmin)
        4.8, // height (arcmin)
        "An elliptical galaxy in the Leo I group", // description
        "images/m105.jpg", // image URL
        1781, // discovery year
        "Spring", // best viewed
        400, // cropped width (px)
        264, // cropped height (px)
        0.508557, // scale factor
        49  // display size (px)
    },
    {
        106, // id
        "M106", // name
        "", // common name
        ObjectType::Galaxy, // object type
        "Canes Venatici", // constellation
        12.316, // RA (hours)
        47.3037, // Dec (degrees)
        8.4, // magnitude
        22.8, // distance (kly)
        18.6, // width (arcmin)
        7.6, // height (arcmin)
        "A spiral galaxy with an active galactic nucleus", // description
        "images/m106.jpg", // image URL
        1781, // discovery year
        "Spring", // best viewed
        400, // cropped width (px)
        270, // cropped height (px)
        1.18757, // scale factor
        115  // display size (px)
    },
    {
        108, // id
        "M108", // name
        "", // common name
        ObjectType::Galaxy, // object type
        "Ursa Major", // constellation
        11.1919, // RA (hours)
        55.6741, // Dec (degrees)
        20, // magnitude
        45, // distance (kly)
        8.7, // width (arcmin)
        2.2, // height (arcmin)
        "An edge-on barred spiral galaxy near the Big Dipper", // description
        "images/m108.jpg", // image URL
        1781, // discovery year
        "Spring", // best viewed
        400, // cropped width (px)
        276, // cropped height (px)
        0.436645, // scale factor
        42  // display size (px)
    },
    {
        109, // id
        "M109", // name
        "", // common name
        ObjectType::Galaxy, // object type
        "Ursa Major", // constellation
        11.96, // RA (hours)
        53.3747, // Dec (degrees)
        20, // magnitude
        55, // distance (kly)
        7.6, // width (arcmin)
        4.7, // height (arcmin)
        "A barred spiral galaxy in Ursa Major", // description
        "images/m109.jpg", // image URL
        1781, // discovery year
        "Spring", // best viewed
        400, // cropped width (px)
        269, // cropped height (px)
        0.596723, // scale factor
        58  // display size (px)
    },
    {
        110, // id
        "M110", // name
        "", // common name
        ObjectType::Galaxy, // object type
        "Andromeda", // constellation
        0.672794, // RA (hours)
        41.6854, // Dec (degrees)
        8.1, // magnitude
        2.2, // distance (kly)
        21.9, // width (arcmin)
        11, // height (arcmin)
        "A satellite galaxy of the Andromeda Galaxy", // description
        "images/m110.jpg", // image URL
        1773, // discovery year
        "Autumn", // best viewed
        400, // cropped width (px)
        270, // cropped height (px)
        1.55104, // scale factor
        150  // display size (px)
    },
};

// Helper functions
inline const MessierObject* findById(int id) {
    for (const auto& obj : MessierCatalog) {
        if (obj.id == id) return &obj;
    }
    return nullptr;
}

inline const MessierObject* findByName(const std::string& name) {
    for (const auto& obj : MessierCatalog) {
        if (obj.name == name) return &obj;
    }
    return nullptr;
}

#endif // MESSIER_CATALOG_H
