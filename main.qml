// main.qml with Solar System integration
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    id: window
    visible: true
    width: 390
    height: 844
    title: "Solar System SkyView"
    
    // Start sensors when app is active
    Component.onCompleted: {
        skyViewController.startSensors();
    }
    
    // Stop sensors when app is inactive
    Component.onDestruction: {
        skyViewController.stopSensors();
    }
    
    // Main solar system view (use our new component)
    SolarSystemSkyView {
        id: skyView
        anchors.fill: parent
    }
    
    // Info overlay to display coordinates and location status
    Rectangle {
        id: infoOverlay
        color: "#80000000"
        width: parent.width
        height: 210
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
                color: skyViewController.isGPSEnabled ? "#90EE90" : "#FFA07A"
                font.pixelSize: 14
            }

            Text {
                Layout.fillWidth: true
                text: "DSOs: " + skyViewController.visibleDSOs.length + " | Planets: " + skyViewController.visibleSolarSystemObjects.length
                color: "#FFFFFF"
                font.pixelSize: 14
            }
        }
    }
    
    // Debug matrix overlay (can be toggled by tapping)
    Rectangle {
        id: matrixDebug
        width: parent.width
        height: matrixVisible ? 180 : 30
        color: "#80000020"
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
                text: "Sky View Settings"
                font.pixelSize: 24
                font.bold: true
            }
            
            // Display options
            GroupBox {
                title: "Display Options"
                Layout.fillWidth: true
                
                ColumnLayout {
                    anchors.fill: parent
                    spacing: 10
                    
                    CheckBox {
                        id: showDSOsCheck
                        text: "Show Deep Sky Objects"
                        checked: true
                        onCheckedChanged: {
                            skyView.dsoContainer.visible = checked
                        }
                    }
                    
                    CheckBox {
                        id: showPlanetsCheck
                        text: "Show Solar System Objects"
                        checked: true
                        onCheckedChanged: {
                            skyView.planetContainer.visible = checked
                        }
                    }
                    
                    CheckBox {
                        id: showStarsCheck
                        text: "Show Background Stars"
                        checked: true
                        onCheckedChanged: {
                            skyView.starField.visible = checked
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
                            let location = Qt.createQmlObject(
                                'import QtPositioning; QtPositioning.coordinate(' + 
                                parseFloat(latField.text) + ', ' + 
                                parseFloat(longField.text) + ')',
                                this);
                            skyViewController.setLocation(location);
                        }
                    }
                }
            }
            
            // Spacer
            Item {
                Layout.fillHeight: true
            }
            
            // Reset button
            Button {
                text: "Reset to Default View"
                Layout.fillWidth: true
                onClicked: {
                    skyViewController.loadDefaultDSOs();
                    skyViewController.updateSolarSystemObjects();
                }
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
}
