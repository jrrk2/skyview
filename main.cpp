#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "skyviewcontroller.h"
#include "GeoCoordinate.h"
#include "GeoCoordinate.h"
#include "jpl.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QString datapath = QCoreApplication::applicationDirPath() + "/data/";
    QString srcpath = QCoreApplication::applicationDirPath() + "/src/";
    std::string cdataPath = datapath.toStdString();
    std::string csrcPath = srcpath.toStdString();
    ephem_main(cdataPath.c_str(), csrcPath.c_str());
    
    // Register GeoCoordinate as a type that can be used in QML
    qRegisterMetaType<GeoCoordinate>("GeoCoordinate");
    
    QQmlApplicationEngine engine;
    
    // Create the controller and expose it to QML
    SkyViewController skyViewController;
    engine.rootContext()->setContextProperty("skyViewController", &skyViewController);
    
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    
    return app.exec();
}
