#include <thread>
#include <iostream>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/timeb.h>
#include <QImage>
#include "ImageStream.h"
#include "ImageStreamRGB.h"
#include "CameraView.h"
#include <chrono>
#include <memory>
#include "SimpleBuffer.h"
#include "include/WPMainCore.h"
#include "include/CTMedia.h"
#include "include/CTStream.h"
#include "YuvUtils.h"

int main(int argc, char **argv)
{
    
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    qmlRegisterType<CameraView>("com.lucaszanella.camera_view", 1, 0, "CameraView");
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject* obj, const QUrl& objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);
    QObject *rootObject = engine.rootObjects().first();
    QObject *mainWindow = rootObject->findChild<QObject*>("mainWindow");
    if (!mainWindow) {
        std::cout << "mainWindow not found" << std::endl;
        //std::exit(1);
    } 
    QObject *cameraViewQ = rootObject->findChild<QObject*>("cameraView");
    if (!cameraViewQ) {
        std::cout << "cameraViewQ not found" << std::endl;
        std::exit(1);
    } 
    CameraView* cameraView = static_cast<CameraView*>(cameraViewQ);

    yuv2rgb_init();
    auto updateCameraView = [&cameraView](std::unique_ptr<SimpleRoseekBuffer> simpleRoseekBuffer, int width, int height) {
        //std::cout << "gonna update image" << std::endl;
        //std::shared_ptr<QImage> qImage = std::make_shared<QImage>(simpleRoseekBuffer.data(), width, height, QImage::Format_RGB24);
        cameraView->updateImage(std::move(simpleRoseekBuffer), width, height, QImage::Format_RGB888);
        QMetaObject::invokeMethod(cameraView, "update", Qt::QueuedConnection);
        std::cout << "updated image" << std::endl;
    };
    std::thread decoder(imageStreamRGBThread, updateCameraView);

    return app.exec();
}
