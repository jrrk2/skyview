// main.qml
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
// import QtPositioning

ApplicationWindow {
    id: window
    visible: true
    width: 390
    height: 844
    title: "DSO SkyView"
    
    // Start sensors when app is active
    Component.onCompleted: {
        skyViewController.startSensors();
    }
    
    // Stop sensors when app is inactive
    Component.onDestruction: {
        skyViewController.stopSensors();
    }
    
    // Main sky view
    SkyView {
        id: skyView
        anchors.fill: parent
        
        // Bind to controller properties
        azimuth: skyViewController.azimuth
        altitude: skyViewController.altitude
        visibleDSOs: skyViewController.visibleDSOs
        
        // Background gradient representing the sky
        Rectangle {
            id: skyBackground
            anchors.fill: parent
            gradient: Gradient {
                GradientStop { position: 0.0; color: "#000020" }  // Deep space blue at top
                GradientStop { position: 1.0; color: "#000000" }  // Black at bottom
            }
        }
        
        // Stars (could be replaced with a more sophisticated star field)
        Item {
            id: starField
            anchors.fill: parent
            
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
        
        // Deep sky objects
        Repeater {
            id: dsoRepeater
            model: skyViewController.visibleDSOs
            
            delegate: Item {
                id: dsoItem
                
                // Position based on view coordinates (-1 to 1 range)
                x: (modelData.viewX + 1) * parent.width / 2
                y: (modelData.viewY + 1) * parent.height / 2
                
                // Scale based on object's apparent size (simplified)
                width: 200  // Fixed size for now
                height: 200
                
                // Center the object
                transform: Translate {
                    x: -width / 2
                    y: -height / 2
                }
                
                Image {
                    id: dsoImage
                    anchors.fill: parent
                    source: modelData.imageUrl
                    fillMode: Image.PreserveAspectFit
                    opacity: 0.9
                    
                    // Smooth scaling
                    smooth: true
                    mipmap: true
                    
                    // Rotation to match celestial coordinates (simplified)
                    rotation: -skyViewController.azimuth
                }
                
                // DSO name label
                Text {
                    anchors.bottom: dsoImage.bottom
                    anchors.horizontalCenter: dsoImage.horizontalCenter
                    text: modelData.name
                    color: "#FFFFFF"
                    font.pixelSize: 14
                    style: Text.Outline
                    styleColor: "#000000"
                }
            }
        }
    }
    
    // Update the infoOverlay section in main.qml for simplified J2000 coordinates display

    // Replace the existing infoOverlay Rectangle with this streamlined version:

// Modify the infoOverlay section in main.qml to add quaternion display

Rectangle {
    id: infoOverlay
    color: "#80000000"
    width: parent.width
    height: 210  // Increased height to accommodate the quaternion info
    anchors.bottom: parent.bottom

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 5

        // Horizontal coordinates
        GridLayout {
            Layout.fillWidth: true
            columns: 2
            columnSpacing: 10

            Text {
                Layout.fillWidth: true
                text: "Az: " + skyViewController.azimuth.toFixed(1) + "°"
                color: "#FFFFFF"
                font.pixelSize: 16
            }

            Text {
                Layout.fillWidth: true
                text: "Alt: " + skyViewController.altitude.toFixed(1) + "°"
                color: "#FFFFFF"
                font.pixelSize: 16
            }
        }

        Text {
            Layout.fillWidth: true
            text: "J2000 Coordinates:"
            color: "#AAAAFF"
            font.pixelSize: 14
            font.bold: true
        }

        // J2000 equatorial coordinates
        GridLayout {
            Layout.fillWidth: true
            columns: 2
            columnSpacing: 10

            Text {
                Layout.fillWidth: true
                text: "RA: " + skyViewController.formattedRA
                color: "#FFFFFF"
                font.pixelSize: 16
            }

            Text {
                Layout.fillWidth: true
                text: "DEC: " + skyViewController.formattedDEC
                color: "#FFFFFF"
                font.pixelSize: 16
            }
        }

        Text {
            Layout.fillWidth: true
            text: "Location: " + 
                skyViewController.location.latitude.toFixed(4) + ", " + 
                skyViewController.location.longitude.toFixed(4)
            color: "#FFFFFF"
            font.pixelSize: 14
        }

        Text {
            Layout.fillWidth: true
            text: skyViewController.locationStatus
            color: skyViewController.isGPSEnabled ? "#90EE90" : "#FFA07A"  // Light green if GPS enabled, light salmon if not
            font.pixelSize: 14
        }

        Text {
            Layout.fillWidth: true
            text: "DSOs in view: " + skyViewController.visibleDSOs.length
            color: "#FFFFFF"
            font.pixelSize: 14
        }
    }

// Add after the infoOverlay component
Rectangle {
    id: matrixDebug
    width: parent.width
    height: matrixVisible ? 180 : 30
    color: "#80000020"  // Slightly lighter background
    anchors.top: infoOverlay.bottom
    
    property bool matrixVisible: false
    
    MouseArea {
        anchors.fill: parent
        onClicked: {
            matrixDebug.matrixVisible = !matrixDebug.matrixVisible
        }
    }
    
    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 5
        spacing: 2
        
        // Header with toggle button
        RowLayout {
            Layout.fillWidth: true
            
            Text {
                text: "Rotation Matrix"
                color: "#AAAAFF"
                font.pixelSize: 14
                font.bold: true
            }
            
            Item { Layout.fillWidth: true }
            
            Text {
                text: matrixDebug.matrixVisible ? "▲" : "▼"
                color: "#FFFFFF"
                font.pixelSize: 14
            }
        }
        
        // Matrix content - only visible when expanded
        GridLayout {
            visible: matrixDebug.matrixVisible
            Layout.fillWidth: true
            columns: 3
            rowSpacing: 2
            columnSpacing: 10
            
            // First row
            Text {
                text: skyViewController.m11.toFixed(3)
                color: "#FFFFFF"
                font.pixelSize: 12
                font.family: "Monospace"
                Layout.preferredWidth: 60
                horizontalAlignment: Text.AlignRight
            }
            Text {
                text: skyViewController.m12.toFixed(3)
                color: "#FFFFFF"
                font.pixelSize: 12
                font.family: "Monospace"
                Layout.preferredWidth: 60
                horizontalAlignment: Text.AlignRight
            }
            Text {
                text: skyViewController.m13.toFixed(3)
                color: "#FFFFFF"
                font.pixelSize: 12
                font.family: "Monospace"
                Layout.preferredWidth: 60
                horizontalAlignment: Text.AlignRight
            }
            
            // Second row
            Text {
                text: skyViewController.m21.toFixed(3)
                color: "#FFFFFF"
                font.pixelSize: 12
                font.family: "Monospace"
                Layout.preferredWidth: 60
                horizontalAlignment: Text.AlignRight
            }
            Text {
                text: skyViewController.m22.toFixed(3)
                color: "#FFFFFF"
                font.pixelSize: 12
                font.family: "Monospace"
                Layout.preferredWidth: 60
                horizontalAlignment: Text.AlignRight
            }
            Text {
                text: skyViewController.m23.toFixed(3)
                color: "#FFFFFF"
                font.pixelSize: 12
                font.family: "Monospace"
                Layout.preferredWidth: 60
                horizontalAlignment: Text.AlignRight
            }
            
            // Third row
            Text {
                text: skyViewController.m31.toFixed(3)
                color: "#FFFFFF"
                font.pixelSize: 12
                font.family: "Monospace"
                Layout.preferredWidth: 60
                horizontalAlignment: Text.AlignRight
            }
            Text {
                text: skyViewController.m32.toFixed(3)
                color: "#FFFFFF"
                font.pixelSize: 12
                font.family: "Monospace"
                Layout.preferredWidth: 60
                horizontalAlignment: Text.AlignRight
            }
            Text {
                text: skyViewController.m33.toFixed(3)
                color: "#FFFFFF"
                font.pixelSize: 12
                font.family: "Monospace"
                Layout.preferredWidth: 60
                horizontalAlignment: Text.AlignRight
            }
            
            // Direction vector header
            Text {
                Layout.columnSpan: 3
                Layout.topMargin: 5
                text: "View Direction (normalized):"
                color: "#AAAAFF"
                font.pixelSize: 12
            }
            
            // X component
            Text {
                text: "X:"
                color: "#AAAAFF"
                font.pixelSize: 12
                Layout.preferredWidth: 20
            }
/*            Text {
                text: skyViewController.debugDirX.toFixed(3)
                color: "#FFFFFF"
                font.pixelSize: 12
                font.family: "Monospace"
                Layout.fillWidth: true
            }
            Item { Layout.fillWidth: true }
            
            // Y component
            Text {
                text: "Y:"
                color: "#AAAAFF"
                font.pixelSize: 12
                Layout.preferredWidth: 20
            }
            Text {
                text: skyViewController.debugDirY.toFixed(3)
                color: "#FFFFFF"
                font.pixelSize: 12
                font.family: "Monospace"
                Layout.fillWidth: true
            }
            Item { Layout.fillWidth: true }
            
            // Z component
            Text {
                text: "Z:"
                color: "#AAAAFF"
                font.pixelSize: 12
                Layout.preferredWidth: 20
            }
            Text {
                text: skyViewController.debugDirZ.toFixed(3)
                color: "#FFFFFF"
                font.pixelSize: 12
                font.family: "Monospace"
                Layout.fillWidth: true
            }
Item { Layout.fillWidth: true }
*/
        }
    }
}
}

    // Settings drawer
    Drawer {
        id: settingsDrawer
        width: 0.8 * window.width
        height: window.height
        edge: Qt.RightEdge
        
        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 20
            spacing: 15
            
            Text {
                text: "Settings"
                font.pixelSize: 24
                font.bold: true
            }
            
            // Add custom DSO section
            GroupBox {
                title: "Add Custom DSO"
                Layout.fillWidth: true
                
                ColumnLayout {
                    anchors.fill: parent
                    spacing: 10
                    
                    TextField {
                        id: dsoNameField
                        Layout.fillWidth: true
                        placeholderText: "Name (e.g., M31 Andromeda)"
                    }
                    
                    RowLayout {
                        Layout.fillWidth: true
                        spacing: 10
                        
                        TextField {
                            id: raField
                            Layout.fillWidth: true
                            placeholderText: "RA (hours)"
                            inputMethodHints: Qt.ImhFormattedNumbersOnly
                        }
                        
                        TextField {
                            id: decField
                            Layout.fillWidth: true
                            placeholderText: "Dec (degrees)"
                            inputMethodHints: Qt.ImhFormattedNumbersOnly
                        }
                    }
                    
                    Button {
                        text: "Select Image"
                        Layout.fillWidth: true
                        onClicked: fileDialog.open()
                    }
                    
                    Text {
                        id: selectedImageText
                        text: "No image selected"
                        Layout.fillWidth: true
                        elide: Text.ElideMiddle
                    }
                    
                    Button {
                        text: "Add DSO"
                        Layout.fillWidth: true
                        onClicked: {
                            if (dsoNameField.text.length > 0 && 
                                raField.text.length > 0 && 
                                decField.text.length > 0 &&
                                selectedImageUrl.length > 0) {
                                    
                                skyViewController.addCustomDSO(
                                    dsoNameField.text,
                                    parseFloat(raField.text),
                                    parseFloat(decField.text),
                                    selectedImageUrl
                                );
                                
                                // Clear fields
                                dsoNameField.text = "";
                                raField.text = "";
                                decField.text = "";
                                selectedImageText.text = "No image selected";
                                selectedImageUrl = "";
                            }
                        }
                    }
                }
            }
            
            // Location settings
            GroupBox {
                title: "Location"
                Layout.fillWidth: true
                
                GridLayout {
                    columns: 2
                    anchors.fill: parent
                    
                    Text { text: "Latitude:" }
                    TextField {
                        id: latField
                        Layout.fillWidth: true
                        text: skyViewController.location.latitude.toFixed(4)
                        inputMethodHints: Qt.ImhFormattedNumbersOnly
                        enabled: !gpsSwitch.checked
                    }
                    
                    Text { text: "Longitude:" }
                    TextField {
                        id: longField
                        Layout.fillWidth: true
                        text: skyViewController.location.longitude.toFixed(4)
                        inputMethodHints: Qt.ImhFormattedNumbersOnly
                        enabled: !gpsSwitch.checked
                    }
                    
                    Text { text: "Use GPS:" }
                    Switch {
                        id: gpsSwitch
                        checked: skyViewController.isGPSEnabled
                        onCheckedChanged: {
                            skyViewController.useManualLocation(!checked);
                        }
                    }
                    
                    Text { text: "GPS Accuracy:" }
                    ComboBox {
                        id: accuracyCombo
                        Layout.fillWidth: true
                        model: ["Best", "Navigation", "Balanced", "Low Power"]
                        currentIndex: 0
                        enabled: gpsSwitch.checked
                        onCurrentIndexChanged: {
                            skyViewController.setGPSAccuracy(currentIndex);
                        }
                    }
                    
                    Button {
                        text: "Set Location"
                        Layout.columnSpan: 2
                        Layout.fillWidth: true
                        enabled: !gpsSwitch.checked
                        onClicked: {
                            let location = QtPositioning.coordinate(
                                parseFloat(latField.text), 
                                parseFloat(longField.text));
                            skyViewController.setLocation(location);
                        }
                    }
                    
                    // Status text
                    Text {
                        Layout.columnSpan: 2
                        Layout.fillWidth: true
                        text: skyViewController.locationStatus
                        color: skyViewController.isGPSEnabled ? "#008000" : "#A0A0A0"
                        elide: Text.ElideRight
                    }
                }
            }
            
            // Spacer
            Item {
                Layout.fillHeight: true
            }
            
            // Reset button
            Button {
                text: "Reset to Default DSOs"
                Layout.fillWidth: true
                onClicked: skyViewController.loadDefaultDSOs()
            }
        }
    }
    
    // Button to open settings
    RoundButton {
        id: settingsButton
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.margins: 20
        text: "⚙️"
        onClicked: settingsDrawer.open()
    }
    
    // Store selected image URL
    property string selectedImageUrl: ""
    
    // File dialog for selecting custom DSO images
    // (This would be implemented differently on iOS with native pickers)
    // For simplicity, we're using a placeholder here
    Item {
        id: fileDialog
        function open() {
            // On a real app, this would use a native file picker
            // For now, we'll just simulate selecting a file
            selectedImageUrl = "file:///path/to/selected/image.jpg";
            selectedImageText.text = "image.jpg";
        }
    }
}
