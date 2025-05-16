#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QFontDatabase>
#include <QStyleHints>
#include <QQmlContext>
#include <QSharedPointer>
#include "CanBus.hpp"
#include "Misc.hpp"
#include "Vehicle.hpp"
#include "ColorPalette.hpp"
#include "Application.hpp"
#include "MaterialIcons.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("MRS Electronic, Inc.");
    QCoreApplication::setOrganizationDomain("mrs-electronics.com");
    QCoreApplication::setApplicationName("neuralplex-demo");
    QCoreApplication::setApplicationVersion(VERSION);

    QGuiApplication app(argc, argv);
    ColorPalette* appColors = new ColorPalette();

    qmlRegisterUncreatableMetaObject(MiscEnums::staticMetaObject, "com.mrs.MiscEnums", 1, 0,
                                     "MiscEnums",
                                     "Cannot create C++ class \"MiscEnums::staticMetaObject\" in QML");

    // Set the default drag distance
    QGuiApplication::styleHints()->setStartDragDistance(24);

    // Setup the application fonts
    QString fontFamily;
    int id = QFontDatabase::addApplicationFont(":/TypeFace/Montserrat-Regular.ttf");
    QFontDatabase::addApplicationFont(":/TypeFace/DejaVuSans.ttf");
    QFontDatabase::addApplicationFont(":/TypeFace/DSEG7Modern-BoldItalic.ttf");
    QFontDatabase::addApplicationFont(":/TypeFace/materialdesignicons-webfont.ttf");
    QFontDatabase::addApplicationFont(":/TypeFace/HelveticaNeue-Light.ttf");
    fontFamily = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont font(fontFamily);
    QGuiApplication::setFont(font);

    // Create instance of main classes
    QSharedPointer<CanBus> canBusPointer = QSharedPointer<CanBus>::create(appSettings.value("canbus0", "CAN0"));
    Application* application = new Application();
    Vehicle* vehicle = new Vehicle(canBusPointer);

    // Setup the context properties so the front end can access the back end
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("MaterialIcons", new MaterialIcons());
    engine.rootContext()->setContextObject(application);
    engine.rootContext()->setContextProperty("colors", appColors);
    engine.rootContext()->setContextProperty("vehicle", vehicle);

    const QUrl url(QStringLiteral("qrc:/qml/Main.qml"));

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated, &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}
