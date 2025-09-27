#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "appcontroller.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<AppController>("com.barcodescanner", 1, 0, "AppController");

    QQmlApplicationEngine engine;

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("barcodeDecoder", "Main");

    return app.exec();
}
