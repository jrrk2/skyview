// SolarSystemSkyView.qml
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: root
    anchors.fill: parent
    
    // Properties to bind to the controller
    property real azimuth: skyViewController.azimuth
    property real altitude: skyViewController.altitude
    property var visibleDSOs: skyViewController.visibleDSOs
    property var visiblePlanets: []  // Will hold solar system objects
    
    // Background gradient representing the sky
    Rectangle {
        id: skyBackground
        anchors.fill: parent
        z: 1
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#000020" }  // Deep space blue at top
            GradientStop { position: 0.9; color: "#000040" }  // Slightly lighter blue near horizon
        }
    }
    
    // Stars (small white dots representing background stars)
    Item {
        id: starField
        anchors.fill: parent
        z: 2
        
        Repeater {
            model: 300  // Number of stars
            
            Rectangle {
                x: Math.random() * parent.width
                y: Math.random() * parent.height
                width: Math.random() * 2 + 1
                height: width
                radius: width / 2
                color: "#FFFFFF"
                opacity: Math.random() * 0.8 + 0.2
            }
        }
    }
    
    // Fixed horizon line at bottom of screen
    Rectangle {
        id: horizonLine
        anchors.bottom: parent.bottom
        width: parent.width
        height: 1
        color: "#404030"  // Subtle horizon line color
        z: 10  // Above everything
    }
    
    // Optional ground area below horizon (small strip for visual effect)
    Rectangle {
        id: ground
        anchors.top: horizonLine.bottom
        width: parent.width
        height: 5  // Just a small strip
        color: "#151510"  // Dark earth color
        z: 10
    }
    
    // Solar System Objects
    Item {
        id: planetContainer
        anchors.fill: parent
        z: 4  // In front of DSOs
        
        Repeater {
            id: planetRepeater
            model: root.visiblePlanets
            
            delegate: Item {
                id: planetItem
                
                // Position based on view coordinates (-1 to 1 range)
                x: (modelData.viewX + 1) * parent.width / 2
                y: (modelData.viewY + 1) * parent.height / 2
                
                // Size based on apparent size but with minimum display size
                width: Math.max(20, modelData.displaySize)
                height: width
                
                // Center the object
                transform: Translate {
                    x: -width / 2
                    y: -height / 2
                }
                
                // Create a clipping container for the image
                Item {
                    id: planetImageClip
                    anchors.fill: parent
                    clip: true  // This will crop the image to the container
                    
                    // Fallback circle if image isn't ready
                    Rectangle {
                        id: planetBackground
                        anchors.fill: parent
                        color: "#E0E0FF"  // Light blue for planets
                        radius: width / 2
                        border.width: 1
                        border.color: "#C0C0FF"
                        opacity: 0.7
                        visible: !planetImage.visible || planetImage.status !== Image.Ready
                    }
                    
                    Image {
                        id: planetImage
                        anchors.fill: parent
                        source: modelData.imageUrl || ""
                        fillMode: Image.PreserveAspectFit
                        opacity: 1.0
                        visible: status === Image.Ready || status === Image.Loading
                        
                        // Phases for inner planets (Mercury and Venus)
                        Rectangle {
                            visible: modelData.phase !== undefined && modelData.phase < 0.99
                            anchors.right: parent.right
                            anchors.top: parent.top
                            anchors.bottom: parent.bottom
                            width: parent.width * (1.0 - modelData.phase)
                            color: "#000000"
                            opacity: 0.8
                        }
                        
                        // Smooth scaling
                        smooth: true
                        mipmap: true
                    }
                }
                
                // Planet name label - placed below the image
                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.bottom
                    anchors.topMargin: 2
                    text: {
                        // Show magnitude if available
                        if (modelData.magnitude !== undefined) {
                            return modelData.name + " (mag " + modelData.magnitude.toFixed(1) + ")";
                        } else {
                            return modelData.name;
                        }
                    }
                    color: "#FFFFFF"
                    font.pixelSize: 12
                    style: Text.Outline
                    styleColor: "#000000"
                    width: parent.width * 1.5
                    elide: Text.ElideRight
                    horizontalAlignment: Text.AlignHCenter
                }
                
                // Optional click area for more detailed information
                MouseArea {
                    anchors.fill: parent
                    anchors.margins: -10  // Extend click area
                    onClicked: {
                        planetInfo.visible = !planetInfo.visible;
                    }
                }
                
                // Detailed information popup
                Rectangle {
                    id: planetInfo
                    visible: false
                    width: infoColumn.width + 20
                    height: infoColumn.height + 20
                    color: "#80000020"
                    border.color: "#C0C0FF"
                    border.width: 1
                    radius: 5
                    
                    anchors.left: parent.right
                    anchors.leftMargin: 10
                    
                    Column {
                        id: infoColumn
                        anchors.centerIn: parent
                        spacing: 5
                        
                        Text {
                            text: modelData.name
                            color: "#FFFFFF"
                            font.pixelSize: 14
                            font.bold: true
                        }
                        
                        Text {
                            visible: modelData.distance !== undefined
                            text: "Distance: " + (modelData.distance * 149.6).toFixed(1) + " million km"
                            color: "#FFFFFF"
                            font.pixelSize: 12
                        }
                        
                        Text {
                            visible: modelData.phase !== undefined
                            text: "Phase: " + (modelData.phase * 100).toFixed(0) + "%"
                            color: "#FFFFFF"
                            font.pixelSize: 12
                        }
                        
                        Text {
                            visible: modelData.angularSize !== undefined
                            text: "Angular size: " + modelData.angularSize.toFixed(1) + " arcsec"
                            color: "#FFFFFF"
                            font.pixelSize: 12
                        }
                    }
                }
            }
        }
    }
    
    // Deep sky objects
    Item {
        id: dsoContainer
        anchors.fill: parent
        z: 3
        
        Repeater {
            id: dsoRepeater
            model: visibleDSOs
            
            delegate: Item {
                id: dsoItem
                
                // Position based on view coordinates (-1 to 1 range)
                x: (modelData.viewX + 1) * parent.width / 2
                y: (modelData.viewY + 1) * parent.height / 2
                
                // Size based on the calculated display size
                width: modelData.displaySize || 60
                height: modelData.displaySize || 60
                
                // Center the object
                transform: Translate {
                    x: -width / 2
                    y: -height / 2
                }
                
                // Visibility check for debugging - always show objects for now
                visible: true
                
                // Create a clipping container for the image
                Item {
                    id: imageClip
                    anchors.fill: parent
                    clip: true  // This will crop the image to the container
                    
                    // Fallback rectangle if image isn't ready
                    Rectangle {
                        id: dsoBackground
                        anchors.fill: parent
                        color: "transparent"
                        radius: width / 2
                        border.width: 1
                        border.color: "#8080FF"
                        opacity: 0.5
                        visible: !dsoImage.visible || dsoImage.status !== Image.Ready
                    }
                    
                    Image {
                        id: dsoImage
                        // If we have cropped dimensions, use them for aspect ratio
                        width: {
                            if (modelData.croppedWidth && modelData.croppedHeight) {
                                var aspectRatio = modelData.croppedWidth / modelData.croppedHeight;
                                return (aspectRatio >= 1.0) ? parent.width : parent.height * aspectRatio;
                            } else {
                                return parent.width;
                            }
                        }
                        
                        height: {
                            if (modelData.croppedWidth && modelData.croppedHeight) {
                                var aspectRatio = modelData.croppedWidth / modelData.croppedHeight;
                                return (aspectRatio >= 1.0) ? parent.width / aspectRatio : parent.height;
                            } else {
                                return parent.height;
                            }
                        }
                        
                        // Center in parent
                        anchors.centerIn: parent
                        
                        source: modelData.imageUrl
                        fillMode: Image.PreserveAspectFit
                        opacity: 0.9
                        visible: status === Image.Ready || status === Image.Loading
                        
                        // Smooth scaling
                        smooth: true
                        mipmap: true
                        
                        // Rotation to match celestial coordinates
                        rotation: -root.azimuth
                    }
                }
                                
                // DSO name label - placed below the image
                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.bottom
                    anchors.topMargin: 2
                    text: modelData.name
                    color: "#FFFFFF"
                    font.pixelSize: 10
                    style: Text.Outline
                    styleColor: "#000000"
                    width: parent.width * 1.5
                    elide: Text.ElideRight
                    horizontalAlignment: Text.AlignHCenter
                }
            }
        }
    }
    
    // UI elements (compass, etc.)
    Item {
        id: uiContainer
        anchors.fill: parent
        z: 5
        
        // Compass direction indicator
        Item {
            id: compassIndicator
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            width: 200
            height: 30
            
            Text {
                anchors.centerIn: parent
                text: {
                    var dir = "";
                    var az = root.azimuth;
                    
                    if (az >= 337.5 || az < 22.5) dir = "N";
                    else if (az >= 22.5 && az < 67.5) dir = "NE";
                    else if (az >= 67.5 && az < 112.5) dir = "E";
                    else if (az >= 112.5 && az < 157.5) dir = "SE";
                    else if (az >= 157.5 && az < 202.5) dir = "S";
                    else if (az >= 202.5 && az < 247.5) dir = "SW";
                    else if (az >= 247.5 && az < 292.5) dir = "W";
                    else if (az >= 292.5 && az < 337.5) dir = "NW";
                    
                    return dir;
                }
                color: "#FFFFFF"
                font.pixelSize: 20
                font.bold: true
                style: Text.Outline
                styleColor: "#000000"
            }
        }
        
        // Direction markers around the edge
        Repeater {
            model: ["N", "E", "S", "W"]
            
            Text {
                property int direction: index
                property var positions: [
                    { x: 0.5, y: 0.05 },  // North
                    { x: 0.95, y: 0.5 },  // East
                    { x: 0.5, y: 0.95 },  // South
                    { x: 0.05, y: 0.5 }   // West
                ]
                
                x: positions[direction].x * parent.width - width/2
                y: positions[direction].y * parent.height - height/2
                text: modelData
                color: "#FFFFFF"
                font.pixelSize: 16
                style: Text.Outline
                styleColor: "#000000"
                
                // Highlight the current direction
                Rectangle {
                    visible: {
                        var az = root.azimuth;
                        return (direction === 0 && (az >= 337.5 || az < 22.5)) ||
                               (direction === 1 && az >= 67.5 && az < 112.5) ||
                               (direction === 2 && az >= 157.5 && az < 202.5) ||
                               (direction === 3 && az >= 247.5 && az < 292.5);
                    }
                    anchors.centerIn: parent
                    width: parent.width + 10
                    height: parent.height + 10
                    color: "transparent"
                    border.color: "#FFFF00"
                    border.width: 2
                    radius: 5
                }
            }
        }
        
        // Altitude indicator
        Rectangle {
            id: altitudeIndicator
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            width: 20
            height: parent.height * 0.7
            color: "transparent"
            border.color: "#808080"
            border.width: 1
            
            Rectangle {
                id: altitudeMarker
                width: parent.width
                height: 5
                color: "#FFFF00"
                y: parent.height * (1 - (root.altitude + 90) / 180)
                
                // Keep marker in bounds
                onYChanged: {
                    if (y < 0) y = 0;
                    if (y > parent.height - height) y = parent.height - height;
                }
            }
            
            // Altitude labels
            Repeater {
                model: ["90°", "60°", "30°", "0°", "-30°", "-60°", "-90°"]
                
                Text {
                    x: altitudeIndicator.width + 2
                    y: altitudeIndicator.height * index / 6 - height / 2
                    text: modelData
                    color: "#FFFFFF"
                    font.pixelSize: 10
                }
            }
        }
    }
    
    // Function to update planet positions from controller
    function updatePlanets() {
        // Get the latest planet positions from the controller
        // This would be implemented in your C++ code
        var planets = skyViewController.getVisibleSolarSystemObjects();
        root.visiblePlanets = planets;
    }
    
    // Timer to update planet positions every second
    Timer {
        interval: 1000
        running: true
        repeat: true
        onTriggered: {
            updatePlanets();
        }
    }
    
    // Initialize when component completes
    Component.onCompleted: {
        updatePlanets();
    }
}
