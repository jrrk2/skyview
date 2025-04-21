#!/bin/bash
# build-image-processor.sh
# Script to compile the image processing tool

# Set compiler and flags
CXX="g++"
CXXFLAGS="-std=c++17 -Wall -O2"

# Get Qt include and lib paths from pkg-config
QT_INCLUDES=$(pkg-config --cflags Qt6Core Qt6Gui)
QT_LIBS=$(pkg-config --libs Qt6Core Qt6Gui)

# Source and output files
SOURCE="messier_processor.cpp"
OUTPUT="messier_processor"

# Compile the tool
echo "Compiling Messier catalog image processor..."
$CXX $CXXFLAGS $QT_INCLUDES -o $OUTPUT $SOURCE $QT_LIBS

if [ $? -eq 0 ]; then
    echo "Build successful. Usage:"
    echo "./$OUTPUT messier_data.ml MessierCatalog.h images_directory output_images_directory"
    echo ""
    echo "Example:"
    echo "./$OUTPUT ./data/messier_data.ml ./include/MessierCatalog.h ./images ./images/cropped"
else
    echo "Build failed."
fi
