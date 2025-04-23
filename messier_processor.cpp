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
#include "MessierCatalog.h"

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
bool processImage(const MessierObject& obj, const std::string& imageDir, const std::string& outputDir) {
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
    
    int displaySize = obj.displaySize;
    double scaleFactor = obj.scaleFactor;    
    int croppedWidth = obj.croppedWidth;
    int croppedHeight = obj.croppedHeight;
    
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

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <image_dir> [output_image_dir]" << std::endl;
        return 1;
    }
    
    std::string imageDir = argv[1];
    
    // Output image directory (default to image_dir/cropped if not specified)
    std::string outputImageDir = (argc > 2) ? argv[2] : imageDir + "/cropped";
        
    // Parse objects
    std::vector<MessierObject> objects;
    for (const auto& obj : MessierCatalog) {
        try {
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
    
    std::cout << "Successfully processed " << objects.size() << " Messier objects with images" << std::endl;
    
    return 0;
}
