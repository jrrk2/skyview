#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include <algorithm>
#include <cmath>

// For image processing
#include <QImage>
#include <QFileInfo>
#include <QDir>

// Object type enum matching the OCaml version
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

// Convert string to ObjectType
ObjectType stringToObjectType(const std::string& type) {
    if (type == "Globular_Cluster") return ObjectType::GlobularCluster;
    if (type == "Open_Cluster") return ObjectType::OpenCluster;
    if (type == "Nebula") return ObjectType::Nebula;
    if (type == "Planetary_Nebula") return ObjectType::PlanetaryNebula;
    if (type == "Supernova_Remnant") return ObjectType::SupernovaRemnant;
    if (type == "Galaxy") return ObjectType::Galaxy;
    if (type == "Galaxy_Cluster") return ObjectType::GalaxyCluster;
    if (type == "Double_Star") return ObjectType::DoubleStar;
    if (type == "Asterism") return ObjectType::Asterism;
    if (type == "Star_Cloud") return ObjectType::StarCloud;
    return ObjectType::Other;
}

// String representation of ObjectType for C++ output
std::string objectTypeToString(ObjectType type) {
    switch (type) {
        case ObjectType::GlobularCluster: return "ObjectType::GlobularCluster";
        case ObjectType::OpenCluster: return "ObjectType::OpenCluster";
        case ObjectType::Nebula: return "ObjectType::Nebula";
        case ObjectType::PlanetaryNebula: return "ObjectType::PlanetaryNebula";
        case ObjectType::SupernovaRemnant: return "ObjectType::SupernovaRemnant";
        case ObjectType::Galaxy: return "ObjectType::Galaxy";
        case ObjectType::GalaxyCluster: return "ObjectType::GalaxyCluster";
        case ObjectType::DoubleStar: return "ObjectType::DoubleStar";
        case ObjectType::Asterism: return "ObjectType::Asterism";
        case ObjectType::StarCloud: return "ObjectType::StarCloud";
        case ObjectType::Other: return "ObjectType::Other";
    }
    return "ObjectType::Other";
}

// Updated MessierObject structure with displaySize field

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
    
    // Extended properties for image processing
    int croppedWidth;    // Width after cropping
    int croppedHeight;   // Height after cropping
    double scaleFactor;  // Scale factor for display
    int displaySize;     // Recommended display size in pixels
};

// Updated image processing functions using a fixed pixel scale

// Define the fixed pixel scale as a constant
const double PIXEL_SCALE_ARCSEC = 1.23;  // arcseconds per pixel
const double PIXEL_SCALE_ARCMIN = PIXEL_SCALE_ARCSEC / 60.0;  // arcminutes per pixel

// Calculate the natural size in pixels based on angular size and fixed pixel scale
int calculateNaturalSizeInPixels(double angularSizeArcmin) {
    // Convert angular size from arcminutes to pixels
    return static_cast<int>(angularSizeArcmin / PIXEL_SCALE_ARCMIN);
}

// Process an image with the fixed pixel scale
bool processImage(MessierObject& obj, const std::string& imageDir, const std::string& outputDir) {
    // Extract the filename from the image URL (assumes format "images/mXX.jpg")
    std::string filename = obj.imageUrl;
    size_t lastSlash = filename.find_last_of('/');
    if (lastSlash != std::string::npos) {
        filename = filename.substr(lastSlash + 1);
    }
    
    // Full path to the image
    std::string imagePath = imageDir + "/" + filename;
    
    // Load the image
    QImage image(QString::fromStdString(imagePath));
    if (image.isNull()) {
        std::cerr << "Failed to load image: " << imagePath << std::endl;
        return false;
    }
    
    // Get image dimensions
    int originalWidth = image.width();
    int originalHeight = image.height();
    
    // Calculate the "natural" size based on angular dimensions and pixel scale
    int naturalWidth = calculateNaturalSizeInPixels(obj.sizeArcminWidth);
    int naturalHeight = calculateNaturalSizeInPixels(obj.sizeArcminHeight);
    
    std::cout << "Processing " << obj.name << " (" << filename << ") - " 
              << originalWidth << "x" << originalHeight << " pixels, "
              << obj.sizeArcminWidth << "x" << obj.sizeArcminHeight << " arcmin" << std::endl;
    std::cout << "  Natural size at " << PIXEL_SCALE_ARCSEC << " arcsec/pixel: "
              << naturalWidth << "x" << naturalHeight << " pixels" << std::endl;
    
    // Calculate target display size for UI based on the natural size
    // We'll still cap this to avoid extremely large UI elements
    const int maxDisplaySize = 150;  // Maximum display size in the UI
    const int minDisplaySize = 40;   // Minimum display size in the UI
    
    // Calculate base size from natural dimensions (use geometric mean for area-based sizing)
    double naturalGeometricMean = std::sqrt(naturalWidth * naturalHeight);
    int baseDisplaySize = static_cast<int>(naturalGeometricMean * 0.2);  // Scale factor for UI
    
    // Ensure size is within reasonable bounds
    int displaySize = std::min(maxDisplaySize, std::max(minDisplaySize, baseDisplaySize));
    
    // Calculate scaling factor relative to "standard" object
    // Using a DSO with 10 arcmin diameter as the standard (scale factor = 1.0)
    double standardSizeArcmin = 10.0;
    double standardSizePixels = standardSizeArcmin / PIXEL_SCALE_ARCMIN;
    double scaleFactor = naturalGeometricMean / standardSizePixels;
    
    // Store the scale factor
    obj.scaleFactor = scaleFactor;
    
    // Determine if image cropping is needed based on a size threshold
    const int maxImageSize = 400; // Maximum allowed image dimension for efficiency
    bool needsCropping = (originalWidth > maxImageSize || originalHeight > maxImageSize);
    
    int croppedWidth, croppedHeight;
    
    if (needsCropping) {
        // Calculate the crop size to maintain aspect ratio
        double aspectRatio = static_cast<double>(originalWidth) / originalHeight;
        
        if (aspectRatio > 1.0) {
            // Landscape image
            croppedWidth = std::min(originalWidth, maxImageSize);
            croppedHeight = static_cast<int>(croppedWidth / aspectRatio);
        } else {
            // Portrait or square image
            croppedHeight = std::min(originalHeight, maxImageSize);
            croppedWidth = static_cast<int>(croppedHeight * aspectRatio);
        }
        
        // Create output directory if it doesn't exist
        QDir dir(QString::fromStdString(outputDir));
        if (!dir.exists()) {
            dir.mkpath(".");
        }
        
        // Calculate the center of the image
        int centerX = originalWidth / 2;
        int centerY = originalHeight / 2;
        
        // Calculate the top-left corner of the crop rectangle
        int cropX = centerX - croppedWidth / 2;
        int cropY = centerY - croppedHeight / 2;
        
        // Ensure the crop rectangle stays within the image bounds
        cropX = std::max(0, std::min(cropX, originalWidth - croppedWidth));
        cropY = std::max(0, std::min(cropY, originalHeight - croppedHeight));
        
        // Perform the crop
        QImage croppedImage = image.copy(cropX, cropY, croppedWidth, croppedHeight);
        
        // Save the cropped image
        std::string outputPath = outputDir + "/" + filename;
        if (!croppedImage.save(QString::fromStdString(outputPath))) {
            std::cerr << "Failed to save cropped image: " << outputPath << std::endl;
            return false;
        }
        
        std::cout << "  Cropped to " << croppedWidth << "x" << croppedHeight 
                  << " pixels, scale factor: " << scaleFactor 
                  << ", display size: " << displaySize << "px" << std::endl;
    } else {
        croppedWidth = originalWidth;
        croppedHeight = originalHeight;
        
        std::cout << "  No cropping needed, scale factor: " << scaleFactor 
                  << ", display size: " << displaySize << "px" << std::endl;
        
        // Just copy the image to the output directory
        QFile::copy(QString::fromStdString(imagePath), 
                    QString::fromStdString(outputDir + "/" + filename));
    }
    
    // Store the cropping and display information
    obj.croppedWidth = croppedWidth;
    obj.croppedHeight = croppedHeight;
    obj.displaySize = displaySize;
    
    return true;
}

// Function to parse an OCaml Messier object block and extract data
MessierObject parseMessierObject(const std::string& block) {
    MessierObject obj;
    
    // Set defaults
    obj.commonName = "";
    obj.discoveryYear = -1;
    obj.croppedWidth = 0;
    obj.croppedHeight = 0;
    obj.scaleFactor = 1.0;
    
    // Regular expressions to extract data
    std::regex idRegex("id = (\\d+);");
    std::regex nameRegex("name = \"(M\\d+)\";");
    std::regex commonNameRegex("common_name = Some \"([^\"]+)\";");
    std::regex objectTypeRegex("object_type = ([A-Za-z_]+);");
    std::regex constellationRegex("constellation = \"([^\"]+)\";");
    std::regex raRegex("ra_hours = ([\\d\\.]+);");
    std::regex decRegex("dec_degrees = ([\\-\\d\\.]+);");
    std::regex magnitudeRegex("magnitude = ([\\d\\.]+);");
    std::regex distanceRegex("distance_kly = ([\\d\\.]+);");
    std::regex sizeRegex("size_arcmin = \\(([\\d\\.]+), ([\\d\\.]+)\\);");
    std::regex descriptionRegex("description = \"([^\"]+)\";");
    std::regex imageUrlRegex("image_url = \"([^\"]+)\";");
    std::regex discoveryYearRegex("discovery_year = Some \\(([-\\d]+)\\);");
    std::regex bestViewedRegex("best_viewed = \"([^\"]+)\";");
    
    // Extract matches
    std::smatch match;
    
    if (std::regex_search(block, match, idRegex))
        obj.id = std::stoi(match[1]);
    
    if (std::regex_search(block, match, nameRegex))
        obj.name = match[1];
    
    if (std::regex_search(block, match, commonNameRegex))
        obj.commonName = match[1];
    
    if (std::regex_search(block, match, objectTypeRegex))
        obj.objectType = stringToObjectType(match[1]);
    
    if (std::regex_search(block, match, constellationRegex))
        obj.constellation = match[1];
    
    if (std::regex_search(block, match, raRegex))
        obj.raHours = std::stod(match[1]);
    
    if (std::regex_search(block, match, decRegex))
        obj.decDegrees = std::stod(match[1]);
    
    if (std::regex_search(block, match, magnitudeRegex))
        obj.magnitude = std::stod(match[1]);
    
    if (std::regex_search(block, match, distanceRegex))
        obj.distanceKly = std::stod(match[1]);
    
    if (std::regex_search(block, match, sizeRegex)) {
        obj.sizeArcminWidth = std::stod(match[1]);
        obj.sizeArcminHeight = std::stod(match[2]);
    }
    
    if (std::regex_search(block, match, descriptionRegex))
        obj.description = match[1];
    
    if (std::regex_search(block, match, imageUrlRegex))
        obj.imageUrl = match[1];
    
    if (std::regex_search(block, match, discoveryYearRegex))
        obj.discoveryYear = std::stoi(match[1]);
    
    if (std::regex_search(block, match, bestViewedRegex))
        obj.bestViewed = match[1];
    
    return obj;
}

/*
// Process an image and calculate cropping parameters
bool processImage(MessierObject& obj, const std::string& imageDir, const std::string& outputDir) {
    // Extract the filename from the image URL (assumes format "images/mXX.jpg")
    std::string filename = obj.imageUrl;
    size_t lastSlash = filename.find_last_of('/');
    if (lastSlash != std::string::npos) {
        filename = filename.substr(lastSlash + 1);
    }
    
    // Full path to the image
    std::string imagePath = imageDir + "/" + filename;
    
    // Load the image
    QImage image(QString::fromStdString(imagePath));
    if (image.isNull()) {
        std::cerr << "Failed to load image: " << imagePath << std::endl;
        return false;
    }
    
    // Get image dimensions
    int originalWidth = image.width();
    int originalHeight = image.height();
    
    std::cout << "Processing " << obj.name << " (" << filename << ") - " 
              << originalWidth << "x" << originalHeight << " pixels, "
              << obj.sizeArcminWidth << "x" << obj.sizeArcminHeight << " arcmin" << std::endl;
    
    // Calculate scaling based on angular size
    // Use the square root of the area for scaling to account for both dimensions
    double angularArea = obj.sizeArcminWidth * obj.sizeArcminHeight;
    double angularSize = std::sqrt(angularArea);
    
    // Base display size for a "standard" DSO (e.g., 10 arcmin)
    const double standardArcmin = 10.0;
    const int standardDisplaySize = 100; // pixels
    
    // Calculate scale factor (capped to avoid extremely large/small images)
    double scaleFactor = std::min(3.0, std::max(0.5, angularSize / standardArcmin));
    obj.scaleFactor = scaleFactor;
    
    // Determine target display size
    int targetDisplaySize = static_cast<int>(standardDisplaySize * scaleFactor);
    
    // Determine if the image should be cropped
    const int maxImageSize = 400; // Maximum allowed image dimension
    bool needsCropping = (originalWidth > maxImageSize || originalHeight > maxImageSize);
    
    int croppedWidth, croppedHeight;
    
    if (needsCropping) {
        // Calculate the crop size to maintain aspect ratio
        double aspectRatio = static_cast<double>(originalWidth) / originalHeight;
        
        if (aspectRatio > 1.0) {
            // Landscape image
            croppedWidth = std::min(originalWidth, maxImageSize);
            croppedHeight = static_cast<int>(croppedWidth / aspectRatio);
        } else {
            // Portrait or square image
            croppedHeight = std::min(originalHeight, maxImageSize);
            croppedWidth = static_cast<int>(croppedHeight * aspectRatio);
        }
        
        // Create output directory if it doesn't exist
        QDir dir(QString::fromStdString(outputDir));
        if (!dir.exists()) {
            dir.mkpath(".");
        }
        
        // Calculate the center of the image
        int centerX = originalWidth / 2;
        int centerY = originalHeight / 2;
        
        // Calculate the top-left corner of the crop rectangle
        int cropX = centerX - croppedWidth / 2;
        int cropY = centerY - croppedHeight / 2;
        
        // Ensure the crop rectangle stays within the image bounds
        cropX = std::max(0, std::min(cropX, originalWidth - croppedWidth));
        cropY = std::max(0, std::min(cropY, originalHeight - croppedHeight));
        
        // Perform the crop
        QImage croppedImage = image.copy(cropX, cropY, croppedWidth, croppedHeight);
        
        // Save the cropped image
        std::string outputPath = outputDir + "/" + filename;
        if (!croppedImage.save(QString::fromStdString(outputPath))) {
            std::cerr << "Failed to save cropped image: " << outputPath << std::endl;
            return false;
        }
        
        std::cout << "  Cropped to " << croppedWidth << "x" << croppedHeight 
                  << " pixels, scale factor: " << scaleFactor 
                  << ", display size: " << targetDisplaySize << "px" << std::endl;
    } else {
        croppedWidth = originalWidth;
        croppedHeight = originalHeight;
        
        std::cout << "  No cropping needed, scale factor: " << scaleFactor 
                  << ", display size: " << targetDisplaySize << "px" << std::endl;
        
        // Just copy the image to the output directory
        QFile::copy(QString::fromStdString(imagePath), 
                    QString::fromStdString(outputDir + "/" + filename));
    }
    
    // Store the cropping information
    obj.croppedWidth = croppedWidth;
    obj.croppedHeight = croppedHeight;
    
    return true;
}

// Generate C++ header file from Messier objects
void generateCppHeader(const std::vector<MessierObject>& objects, const std::string& outputFile) {
    std::ofstream out(outputFile);
    
    // Header guards and includes
    out << "#ifndef MESSIER_CATALOG_H\n";
    out << "#define MESSIER_CATALOG_H\n\n";
    out << "#include <vector>\n";
    out << "#include <string>\n\n";
    
    // Object type enum
    out << "// Messier object types\n";
    out << "enum class ObjectType {\n";
    out << "    GlobularCluster,\n";
    out << "    OpenCluster,\n";
    out << "    Nebula,\n";
    out << "    PlanetaryNebula,\n";
    out << "    SupernovaRemnant,\n";
    out << "    Galaxy,\n";
    out << "    GalaxyCluster,\n";
    out << "    DoubleStar,\n";
    out << "    Asterism,\n";
    out << "    StarCloud,\n";
    out << "    Other\n";
    out << "};\n\n";
    
    // Helper function to convert enum to string
    out << "// Convert object type to string\n";
    out << "inline const char* objectTypeToString(ObjectType type) {\n";
    out << "    switch (type) {\n";
    out << "        case ObjectType::GlobularCluster: return \"Globular Cluster\";\n";
    out << "        case ObjectType::OpenCluster: return \"Open Cluster\";\n";
    out << "        case ObjectType::Nebula: return \"Nebula\";\n";
    out << "        case ObjectType::PlanetaryNebula: return \"Planetary Nebula\";\n";
    out << "        case ObjectType::SupernovaRemnant: return \"Supernova Remnant\";\n";
    out << "        case ObjectType::Galaxy: return \"Galaxy\";\n";
    out << "        case ObjectType::GalaxyCluster: return \"Galaxy Cluster\";\n";
    out << "        case ObjectType::DoubleStar: return \"Double Star\";\n";
    out << "        case ObjectType::Asterism: return \"Asterism\";\n";
    out << "        case ObjectType::StarCloud: return \"Star Cloud\";\n";
    out << "        case ObjectType::Other: return \"Other\";\n";
    out << "    }\n";
    out << "    return \"Unknown\";\n";
    out << "}\n\n";
    
    // Messier object structure
    out << "// Messier object structure\n";
    out << "struct MessierObject {\n";
    out << "    int id;\n";
    out << "    std::string name;\n";
    out << "    std::string commonName;  // Empty if none\n";
    out << "    ObjectType objectType;\n";
    out << "    std::string constellation;\n";
    out << "    double raHours;\n";
    out << "    double decDegrees;\n";
    out << "    double magnitude;\n";
    out << "    double distanceKly;\n";
    out << "    double sizeArcminWidth;\n";
    out << "    double sizeArcminHeight;\n";
    out << "    std::string description;\n";
    out << "    std::string imageUrl;\n";
    out << "    int discoveryYear;  // -1 if unknown\n";
    out << "    std::string bestViewed;\n";
    out << "    int croppedWidth;      // Width of cropped image in pixels\n";
    out << "    int croppedHeight;     // Height of cropped image in pixels\n";
    out << "    double scaleFactor;    // Recommended UI scale factor\n";
    out << "};\n\n";
    
    // Catalog data
    out << "// Complete Messier catalog\n";
    out << "const std::vector<MessierObject> MessierCatalog = {\n";
    
    // Add each object
    for (const auto& obj : objects) {
        out << "    {\n";
        out << "        " << obj.id << ", // id\n";
        out << "        \"" << obj.name << "\", // name\n";
        out << "        \"" << obj.commonName << "\", // common name\n";
        out << "        " << objectTypeToString(obj.objectType) << ", // object type\n";
        out << "        \"" << obj.constellation << "\", // constellation\n";
        out << "        " << obj.raHours << ", // RA (hours)\n";
        out << "        " << obj.decDegrees << ", // Dec (degrees)\n";
        out << "        " << obj.magnitude << ", // magnitude\n";
        out << "        " << obj.distanceKly << ", // distance (kly)\n";
        out << "        " << obj.sizeArcminWidth << ", // width (arcmin)\n";
        out << "        " << obj.sizeArcminHeight << ", // height (arcmin)\n";
        out << "        \"" << obj.description << "\", // description\n";
        out << "        \"" << obj.imageUrl << "\", // image URL\n";
        out << "        " << obj.discoveryYear << ", // discovery year\n";
        out << "        \"" << obj.bestViewed << "\", // best viewed\n";
        out << "        " << obj.croppedWidth << ", // cropped width (px)\n";
        out << "        " << obj.croppedHeight << ", // cropped height (px)\n";
        out << "        " << obj.scaleFactor << "  // scale factor\n";
        out << "    },\n";
    }
    
    out << "};\n\n";
    
    // Helper functions
    out << "// Helper functions\n";
    
    // Find by ID
    out << "inline const MessierObject* findById(int id) {\n";
    out << "    for (const auto& obj : MessierCatalog) {\n";
    out << "        if (obj.id == id) return &obj;\n";
    out << "    }\n";
    out << "    return nullptr;\n";
    out << "}\n\n";
    
    // Find by name
    out << "inline const MessierObject* findByName(const std::string& name) {\n";
    out << "    for (const auto& obj : MessierCatalog) {\n";
    out << "        if (obj.name == name) return &obj;\n";
    out << "    }\n";
    out << "    return nullptr;\n";
    out << "}\n\n";
    
    // End of header
    out << "#endif // MESSIER_CATALOG_H\n";
    
    out.close();
    
    std::cout << "Generated C++ header file: " << outputFile << std::endl;
    std::cout << "Contains " << objects.size() << " Messier objects." << std::endl;
}
*/

// Update the generateCppHeader function to include the displaySize field

void generateCppHeader(const std::vector<MessierObject>& objects, const std::string& outputFile) {
    std::ofstream out(outputFile);
    
    // Header guards and includes
    out << "#ifndef MESSIER_CATALOG_H\n";
    out << "#define MESSIER_CATALOG_H\n\n";
    out << "#include <vector>\n";
    out << "#include <string>\n\n";
    
    // Object type enum
    out << "// Messier object types\n";
    out << "enum class ObjectType {\n";
    out << "    GlobularCluster,\n";
    out << "    OpenCluster,\n";
    out << "    Nebula,\n";
    out << "    PlanetaryNebula,\n";
    out << "    SupernovaRemnant,\n";
    out << "    Galaxy,\n";
    out << "    GalaxyCluster,\n";
    out << "    DoubleStar,\n";
    out << "    Asterism,\n";
    out << "    StarCloud,\n";
    out << "    Other\n";
    out << "};\n\n";
    
    // Helper function to convert enum to string
    out << "// Convert object type to string\n";
    out << "inline const char* objectTypeToString(ObjectType type) {\n";
    out << "    switch (type) {\n";
    out << "        case ObjectType::GlobularCluster: return \"Globular Cluster\";\n";
    out << "        case ObjectType::OpenCluster: return \"Open Cluster\";\n";
    out << "        case ObjectType::Nebula: return \"Nebula\";\n";
    out << "        case ObjectType::PlanetaryNebula: return \"Planetary Nebula\";\n";
    out << "        case ObjectType::SupernovaRemnant: return \"Supernova Remnant\";\n";
    out << "        case ObjectType::Galaxy: return \"Galaxy\";\n";
    out << "        case ObjectType::GalaxyCluster: return \"Galaxy Cluster\";\n";
    out << "        case ObjectType::DoubleStar: return \"Double Star\";\n";
    out << "        case ObjectType::Asterism: return \"Asterism\";\n";
    out << "        case ObjectType::StarCloud: return \"Star Cloud\";\n";
    out << "        case ObjectType::Other: return \"Other\";\n";
    out << "    }\n";
    out << "    return \"Unknown\";\n";
    out << "}\n\n";
    
    // Messier object structure
    out << "// Messier object structure\n";
    out << "struct MessierObject {\n";
    out << "    int id;\n";
    out << "    std::string name;\n";
    out << "    std::string commonName;  // Empty if none\n";
    out << "    ObjectType objectType;\n";
    out << "    std::string constellation;\n";
    out << "    double raHours;\n";
    out << "    double decDegrees;\n";
    out << "    double magnitude;\n";
    out << "    double distanceKly;\n";
    out << "    double sizeArcminWidth;\n";
    out << "    double sizeArcminHeight;\n";
    out << "    std::string description;\n";
    out << "    std::string imageUrl;\n";
    out << "    int discoveryYear;  // -1 if unknown\n";
    out << "    std::string bestViewed;\n";
    out << "    int croppedWidth;      // Width of cropped image in pixels\n";
    out << "    int croppedHeight;     // Height of cropped image in pixels\n";
    out << "    double scaleFactor;    // Recommended UI scale factor\n";
    out << "    int displaySize;       // Recommended display size in pixels\n";
    out << "};\n\n";
    
    // Catalog data
    out << "// Complete Messier catalog\n";
    out << "const std::vector<MessierObject> MessierCatalog = {\n";
    
    // Add each object
    for (const auto& obj : objects) {
        out << "    {\n";
        out << "        " << obj.id << ", // id\n";
        out << "        \"" << obj.name << "\", // name\n";
        out << "        \"" << obj.commonName << "\", // common name\n";
        out << "        " << objectTypeToString(obj.objectType) << ", // object type\n";
        out << "        \"" << obj.constellation << "\", // constellation\n";
        out << "        " << obj.raHours << ", // RA (hours)\n";
        out << "        " << obj.decDegrees << ", // Dec (degrees)\n";
        out << "        " << obj.magnitude << ", // magnitude\n";
        out << "        " << obj.distanceKly << ", // distance (kly)\n";
        out << "        " << obj.sizeArcminWidth << ", // width (arcmin)\n";
        out << "        " << obj.sizeArcminHeight << ", // height (arcmin)\n";
        out << "        \"" << obj.description << "\", // description\n";
        out << "        \"" << obj.imageUrl << "\", // image URL\n";
        out << "        " << obj.discoveryYear << ", // discovery year\n";
        out << "        \"" << obj.bestViewed << "\", // best viewed\n";
        out << "        " << obj.croppedWidth << ", // cropped width (px)\n";
        out << "        " << obj.croppedHeight << ", // cropped height (px)\n";
        out << "        " << obj.scaleFactor << ", // scale factor\n";
        out << "        " << obj.displaySize << "  // display size (px)\n";
        out << "    },\n";
    }
    
    out << "};\n\n";
    
    // Helper functions
    out << "// Helper functions\n";
    
    // Find by ID
    out << "inline const MessierObject* findById(int id) {\n";
    out << "    for (const auto& obj : MessierCatalog) {\n";
    out << "        if (obj.id == id) return &obj;\n";
    out << "    }\n";
    out << "    return nullptr;\n";
    out << "}\n\n";
    
    // Find by name
    out << "inline const MessierObject* findByName(const std::string& name) {\n";
    out << "    for (const auto& obj : MessierCatalog) {\n";
    out << "        if (obj.name == name) return &obj;\n";
    out << "    }\n";
    out << "    return nullptr;\n";
    out << "}\n\n";
    
    // End of header
    out << "#endif // MESSIER_CATALOG_H\n";
    
    out.close();
    
    std::cout << "Generated C++ header file: " << outputFile << std::endl;
    std::cout << "Contains " << objects.size() << " Messier objects." << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cerr << "Usage: " << argv[0] << " <input_ocaml_file> <output_cpp_header> <image_dir> [output_image_dir]" << std::endl;
        return 1;
    }
    
    std::string inputFile = argv[1];
    std::string outputFile = argv[2];
    std::string imageDir = argv[3];
    
    // Output image directory (default to image_dir/cropped if not specified)
    std::string outputImageDir = (argc > 4) ? argv[4] : imageDir + "/cropped";
    
    // Read the OCaml file
    std::ifstream file(inputFile);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open input file " << inputFile << std::endl;
        return 1;
    }
    
    std::string content((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());
    file.close();
    
    // Split into object blocks
    std::vector<std::string> blocks;
    size_t pos = 0;
    while ((pos = content.find("{ ", pos)) != std::string::npos) {
        size_t endPos = content.find("};", pos);
        if (endPos == std::string::npos) break;
        
        blocks.push_back(content.substr(pos, endPos - pos + 2));
        pos = endPos + 2;
    }
    
    // Parse objects
    std::vector<MessierObject> objects;
    for (const auto& block : blocks) {
        try {
            MessierObject obj = parseMessierObject(block);
            if (!obj.name.empty()) {
                // Process the image if it exists
                if (processImage(obj, imageDir, outputImageDir)) {
                    objects.push_back(obj);
                } else {
                    std::cerr << "Warning: Skipping " << obj.name << " due to image processing failure" << std::endl;
                }
            }
        } catch (const std::exception& e) {
            std::cerr << "Error parsing block: " << e.what() << std::endl;
        }
    }
    
    // Generate C++ header
    generateCppHeader(objects, outputFile);
    
    std::cout << "Successfully processed " << objects.size() << " Messier objects with images" << std::endl;
    
    return 0;
}
