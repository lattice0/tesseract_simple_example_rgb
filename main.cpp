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
#include "ImageStream.h"
#include <chrono>

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

    std::thread decoder(imageStreamThread, (void*)&MainCT);
    /*
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
    */
    std::chrono::milliseconds timespan(111605); // or whatever

    std::this_thread::sleep_for(timespan);
}
