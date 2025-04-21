TEMPLATE = app
TARGET = DSO_SkyView

# Only require QtQuick, not positioning or sensors
QT += quick

CONFIG += c++17

# Required for iOS
ios {
    QMAKE_INFO_PLIST = ios/Info.plist
    ios_icon.files = $$files(ios/AppIcon*.png)
    QMAKE_BUNDLE_DATA += ios_icon
}

SOURCES += \
    main.cpp \
    skyviewcontroller.cpp \
    AstronomyCalculator.cpp \
    GeoCoordinate.cpp

HEADERS += \
    skyviewcontroller.h \
    IOSSensorBridge.h \
    AstronomyCalculator.h \
    GeoCoordinate.h

# Add Objective-C++ file for iOS platform
ios {
    OBJECTIVE_SOURCES += \
        IOSSensorBridge.mm
        
    # Link required iOS frameworks
    LIBS += -framework CoreMotion -framework CoreLocation
}

RESOURCES += \
    qml.qrc \
    images.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
