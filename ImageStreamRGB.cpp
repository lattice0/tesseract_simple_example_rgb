#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <windows.h>
#include <time.h>
//#include <process.h>
#include <sys/timeb.h>
#include <iostream>
#include <thread>
#include <vector>
#include <memory>
#include "include/WPMainCore.h"
#include "include/CTMedia.h"
#include "include/CTStream.h"
#include "ImageStream.h"
#include "SimpleBuffer.h"
#include "YuvUtils.h"
#include "utils.h"

static unsigned ThreadMainLoop(void *pParam);

void imageStreamRGBThread(std::function<void(std::unique_ptr<SimpleRoseekBuffer>, int, int)> rgbUpdateCallback)
{
    //int rgbBufferSize = nWidth * nHeight * 3 * sizeof(unsigned char);
    int rgbBufferWidth;
    int rgbBufferHeight;
    std::string imageName = "phototest_flipped.bmp";
    //unsigned char *rgbBuffer = readBMP1(imageName.c_str(), &rgbBufferWidth, &rgbBufferHeight);
    std::vector<char> rgbBufferVector = readBMP1(imageName.c_str(), &rgbBufferWidth, &rgbBufferHeight);
    unsigned char* rgbBuffer = (unsigned char *) rgbBufferVector.data();
    int bytesPerPixel = 3;
    int bytesPerLine = bytesPerPixel * rgbBufferWidth;
    int rgbBufferSize = rgbBufferWidth * rgbBufferHeight * 3;
    while (true)
    {
        std::unique_ptr<SimpleRoseekBuffer> simpleRoseekBuffer = std::make_unique<SimpleRoseekBuffer>(rgbBufferSize);
        unsigned char *d = simpleRoseekBuffer->data();
        for (int i = 0; i < rgbBufferSize; i++)
        {
            //std::cout << i << std::endl;
            //d[i];
            //std::cout << "a"<< std::endl;
            d[i] = *(rgbBuffer + i);
        }
        rgbUpdateCallback(std::move(simpleRoseekBuffer), rgbBufferWidth, rgbBufferHeight);
        std::chrono::milliseconds timespan(100);
        std::this_thread::sleep_for(timespan);
    }

    std::cout << "finished decoder thread" << std::endl;
}
