import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item {
    id: root
    
    // Expose properties to allow external control
    property bool useNativeCompass: skyViewController.useNativeCompass
    property double heading: skyViewController.azimuth
    property double headingAccuracy: skyViewController.headingAccuracy
    
    signal settingsChanged(bool useNativeCompass)
    
    width: parent.width
    height: contentColumn.height
    
    function formatHeading(deg) {
        var directions = ["N", "NE", "E", "SE", "S", "SW", "W", "NW", "N"];
        var index = Math.round(deg / 45) % 8;
        return deg.toFixed(1) + "° " + directions[index];
    }
    
    Column {
        id: contentColumn
        width: parent.width
        spacing: 10
        
        Rectangle {
            width: parent.width
            height: 50
            color: "#f0f0f0"
            border.color: "#d0d0d0"
            
            RowLayout {
                anchors.fill: parent
                anchors.margins: 10
                
                Label {
                    text: "Use Native Compass"
                    font.pixelSize: 16
                    Layout.fillWidth: true
                }
                
                Switch {
                    checked: root.useNativeCompass
                    onCheckedChanged: {
                        skyViewController.useNativeCompass = checked;
                        root.settingsChanged(checked);
                    }
                }
            }
        }
        
        Rectangle {
            width: parent.width
            height: 50
            color: "#f0f0f0"
            border.color: "#d0d0d0"
            visible: root.useNativeCompass
            
            RowLayout {
                anchors.fill: parent
                anchors.margins: 10
                
                Label {
                    text: "Current Heading: " + formatHeading(root.heading)
                    font.pixelSize: 16
                    Layout.fillWidth: true
                }
                
                Label {
                    text: "±" + root.headingAccuracy.toFixed(1) + "°"
                    font.pixelSize: 14
                    color: root.headingAccuracy < 15 ? "#006600" : 
                           root.headingAccuracy < 45 ? "#996600" : "#990000"
                }
            }
        }
        
        Button {
            width: parent.width
            height: 50
            text: "Recalibrate Compass"
            visible: root.useNativeCompass
            
            onClicked: {
                skyViewController.resetCompassCalibration();
            }
        }
        
        Label {
            width: parent.width
            text: "When calibration is needed, move your device in a figure-8 pattern."
            font.pixelSize: 14
            wrapMode: Text.WordWrap
            visible: root.useNativeCompass
        }
    }
}
