// SkyView.qml with fixed layering
import QtQuick

Item {
    id: root
    
    // Properties to bind to the controller
    property real azimuth: 0
    property real altitude: 0
    property var visibleDSOs: []
    
    // Background gradient representing the sky
    Rectangle {
        id: skyBackground
        anchors.fill: parent
        z: 1 // Set explicit z-order
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#000020" }  // Deep space blue at top
            GradientStop { position: 1.0; color: "#000000" }  // Black at bottom
        }
    }
    
    // Stars (could be replaced with a more sophisticated star field)
    Item {
        id: starField
        anchors.fill: parent
        z: 2 // Set explicit z-order
        
        Repeater {
            model: 200  // Number of stars
            
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
    
    // Deep sky objects - place in front of the stars
    Item {
        id: dsoContainer
        anchors.fill: parent
        z: 3 // Make sure DSOs appear above the star field
        
        Repeater {
            id: dsoRepeater
            model: visibleDSOs
            
            delegate: Item {
                id: dsoItem
                
                // Position based on view coordinates (-1 to 1 range)
                x: (modelData.viewX + 1) * parent.width / 2
                y: (modelData.viewY + 1) * parent.height / 2
                
                width: 100  // Fixed size for now
                height: 100
                
                // Center the object
                transform: Translate {
                    x: -width / 2
                    y: -height / 2
                }
                
                // Use a Rectangle as a background for the DSO
                Rectangle {
                    id: dsoBackground
                    anchors.fill: parent
                    color: "transparent"
                    radius: width / 2
                    border.width: 1
                    border.color: "#8080FF"
                    opacity: 0.5
                    visible: true // Always visible as a fallback
                }
                
                Image {
                    id: dsoImage
                    anchors.fill: parent
                    source: modelData.imageUrl
                    fillMode: Image.PreserveAspectFit
                    opacity: 0.9
                    visible: status === Image.Ready || status === Image.Loading
                    
                    // Smooth scaling
                    smooth: true
                    mipmap: true
                    
                    // Rotation to match celestial coordinates (simplified)
                    rotation: -root.azimuth
                    
                    // Debug information
                    onStatusChanged: {
                        if (status === Image.Error) {
                            console.log("Failed to load image: " + source);
                        } else if (status === Image.Ready) {
                            console.log("Image loaded successfully: " + source);
                        }
                    }
                }
                
                // DSO name label
                Text {
                    anchors.horizontalCenter: dsoImage.horizontalCenter
                    anchors.top: dsoImage.bottom
                    anchors.topMargin: 2
                    text: modelData.name
                    color: "#FFFFFF"
                    font.pixelSize: 12
                    style: Text.Outline
                    styleColor: "#000000"
                }
            }
        }
    }
    
    // Place UI elements above both stars and DSOs
    Item {
        id: uiContainer
        anchors.fill: parent
        z: 4
        
        // Allow mouse and touch interaction for manual exploration
        MouseArea {
            anchors.fill: parent
            
            property real lastX: 0
            property real lastY: 0
            property bool dragging: false
            
            onPressed: {
                lastX = mouse.x
                lastY = mouse.y
                dragging = true
            }
            
            onReleased: {
                dragging = false
            }
            
            onPositionChanged: {
                if (dragging) {
                    // Manual adjustment of view
                    // Calculate change in mouse position
                    var deltaX = mouse.x - lastX
                    var deltaY = mouse.y - lastY
                    
                    // Update last position
                    lastX = mouse.x
                    lastY = mouse.y
                    
                    // Visual feedback
                    overlaySkyView.opacity = 0.5
                    overlaySkyView.x += deltaX * 0.1
                    overlaySkyView.y += deltaY * 0.1
                    
                    // Reset overlay after a short delay
                    resetTimer.restart()
                }
            }
        }
        
        // Overlay to provide visual feedback during manual exploration
        Rectangle {
            id: overlaySkyView
            anchors.fill: parent
            color: "transparent"
            opacity: 0
            
            // Timing for resetting overlay
            Timer {
                id: resetTimer
                interval: 300
                onTriggered: {
                    overlaySkyView.opacity = 0
                    overlaySkyView.x = 0
                    overlaySkyView.y = 0
                }
            }
        }
        
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
                    // Convert azimuth to cardinal direction
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
}
