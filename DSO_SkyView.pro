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
    SolarSystemCalculator.cpp \
    GeoCoordinate.cpp \
    src/argparse/argparse.c \
    src/coreUtils/asciiDouble.c \
    src/coreUtils/errorReport.c \
    src/coreUtils/makeRasters.c \
    src/ephemCalc/constellations.c \
    src/ephemCalc/jpl.c \
    src/ephemCalc/magnitudeEstimate.c \
    src/ephemCalc/meeus.c \
    src/ephemCalc/orbitalElements.c \
    src/listTools/ltDict.c \
    src/listTools/ltList.c \
    src/listTools/ltMemory.c \
    src/listTools/ltStringProc.c \
    src/main.c \
    src/mathsTools/julianDate.c \
    src/mathsTools/precess_equinoxes.c \
    src/mathsTools/sphericalAst.c \
    src/settings/settings.c \
    
HEADERS += \
    skyviewcontroller.h \
    IOSSensorBridge.h \
    AstronomyCalculator.h \
    SolarSystemCalculator.h \
    GeoCoordinate.h \
    src/argparse/argparse.h \
    src/coreUtils/asciiDouble.h \
    src/coreUtils/errorReport.h \
    src/coreUtils/makeRasters.h \
    src/coreUtils/strConstants.h \
    src/ephemCalc/constellations.h \
    src/ephemCalc/jpl.h \
    src/ephemCalc/magnitudeEstimate.h \
    src/ephemCalc/meeus.h \
    src/ephemCalc/orbitalElements.h \
    src/listTools/ltDict.h \
    src/listTools/ltList.h \
    src/listTools/ltMemory.h \
    src/listTools/ltStringProc.h \
    src/mathsTools/julianDate.h \
    src/mathsTools/precess_equinoxes.h \
    src/mathsTools/sphericalAst.h \
    src/partial_file.h \
    src/settings/settings.h \

# Add Objective-C++ file for iOS platform
ios {
    # Data files to be copied to the bundle
    datafiles.files = $$files($$PWD/data/*)
    datafiles.path = data
    # Add all resource sets to the bundle
    QMAKE_BUNDLE_DATA += datafiles

    DEFINES += SRCDIR=srcdir DATADIR=datadir DEBUG=1 MEMDEBUG1=0 MEMDEBUG2=0 DCFVERSION=\\\"4.0\\\" DATE=\\\"23/09/2024\\\"
    INCLUDEPATH += src /opt/homebrew/Cellar/gsl/2.8/include
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
