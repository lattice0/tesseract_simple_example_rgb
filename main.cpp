#include <thread>
#include <iostream>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include <process.h>
#include <sys/timeb.h>
#include <QImage>
#include "ImageStream.h"
#include "CameraView.h"
#include <chrono>
#include <memory>
#include "SimpleBuffer.h"
#include "include/WPMainCore.h"
#include "include/CTMedia.h"
#include "include/CTStream.h"

typedef struct _MainContext
{
    int m_ThreadWatch;
    void *pEncoder;
    void *pStreamer;
}MainContext_t;

int main(int argc, char **argv)
{
    std::cout << "Roseek" << std::endl;
    int ret;
    MainContext_t MainCT;
    UINT32 nWidth, nHeight;
    float FrameRate;
    MediaEncoderParamsV1 EncoderParams;

    memset(&MainCT, 0, sizeof(MainCT));

    ret = Roseek_MainCore_Init(0);
    if (ret != 0)
    {
        std::cout << "Roseek_MainCore_Init problem" << std::endl;
    }

    ret = Roseek_ImageAcquisition_Start();
    if (ret != 0)
    {
        std::cout << "Roseek_ImageAcquisition_Start problem" << std::endl;
    }

    Roseek_ImageAcquisition_GetResolution(NULL, NULL, NULL, &nWidth, &nHeight);
    Roseek_ImageAcquisition_GetFrameRate(&FrameRate);

    Roseek_MediaEncoder_InitParamsV1(&EncoderParams);
    EncoderParams.HWOrSW = CT_USE_AUTO;
    EncoderParams.SourceFormat = CT_FOURCC_NV12;
    EncoderParams.SourceWidth = nWidth;
    EncoderParams.SourceHeight = nHeight;
    EncoderParams.SourceFrameRate = FrameRate;
    EncoderParams.DestCodecID = CT_CODEC_H264;
    EncoderParams.DestWidth = nWidth;
    EncoderParams.DestHeight = nHeight;
    EncoderParams.DestFrameRate = 25.0f;
    EncoderParams.BitRate = 8000;
    ret = Roseek_MediaEncoder_CreateV1(&MainCT.pEncoder, &EncoderParams);

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


    auto updateCameraView = [&cameraView](std::unique_ptr<SimpleRoseekBuffer> simpleRoseekBuffer, int width, int height) {
        //std::cout << "gonna update image" << std::endl;
        //std::shared_ptr<QImage> qImage = std::make_shared<QImage>(simpleRoseekBuffer.data(), width, height, QImage::Format_RGB24);
        cameraView->updateImage(std::move(simpleRoseekBuffer), width, height, QImage::Format_RGB888);
        QMetaObject::invokeMethod(cameraView, "update", Qt::QueuedConnection);
        std::cout << "updated image" << std::endl;
    };
    std::thread decoder(imageStreamThread, (void*)&MainCT, updateCameraView);

    return app.exec();
    
    std::chrono::milliseconds timespan(111605); // or whatever

    std::this_thread::sleep_for(timespan);
}
