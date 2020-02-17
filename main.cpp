#include <thread>
#include <iostream>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "DecodeH264AndStream.h"

//#pragma comment(lib, "win_bin/lib/x64/CTMedia.lib")
//#pragma comment(lib, "win_bin/lib/x64/CTStream.lib")
//#pragma comment(lib, "win_bin/lib/x64/CTMainCore.lib")

int main(int argc, char **argv)
{
    std::cout << "Roseek" << std::endl;
    std::thread decoder(decoder_thread);
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject* obj, const QUrl& objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
