// SkyView.qml
import QtQuick

Item {
    id: root
    
    // Properties to bind to the controller
    property real azimuth: 0
    property real altitude: 0
    property var visibleDSOs: []
    
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
                // This is a simplified implementation, in a real app
                // you would adjust the SkyViewController's azimuth/altitude
                // based on the drag distance and direction
                
                // Calculate change in mouse position
                var deltaX = mouse.x - lastX
                var deltaY = mouse.y - lastY
                
                // Update last position
                lastX = mouse.x
                lastY = mouse.y
                
                // In a complete implementation, we would update the view here
                // For now, we'll just provide visual feedback
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
