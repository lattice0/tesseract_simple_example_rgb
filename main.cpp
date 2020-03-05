#include <iostream>
#include <memory>

#include <allheaders.h> // leptonica main header for image io
#include <baseapi.h>    // tesseract main header
#include "utils.h"


int main(int argc, char *argv[])
{
    std::cout << "begin" << std::endl;
    int rgbBufferWidth;
    int rgbBufferHeight;
    std::string imageName = "phototest_flipped.bmp"; 
    unsigned char *rgbBuffer = readBMP2(imageName.c_str(), &rgbBufferWidth, &rgbBufferHeight);
    int bytesPerPixel = 3;
    int bytesPerLine = bytesPerPixel * rgbBufferWidth;
    int rgbBufferSize = rgbBufferWidth * rgbBufferHeight * 3;
    std::cout << "readed " << imageName << ", width: " << rgbBufferWidth << " height: " << rgbBufferHeight << " bytesPerLine: " << bytesPerLine << std::endl;
    tesseract::TessBaseAPI tess;

    if (tess.Init("./languages/", "eng"))
    {
        std::cout << "OCRTesseract: Could not initialize tesseract." << std::endl;
        return 1;
    }

    // setup
    tess.SetPageSegMode(tesseract::PageSegMode::PSM_AUTO);
    tess.SetVariable("save_best_choices", "T");


    // recognize
    tess.SetImage((const unsigned char*)rgbBuffer, rgbBufferWidth, rgbBufferHeight, bytesPerPixel, bytesPerLine);
    std::cout << "gonna recognize" << std::endl;
    tess.Recognize(0);
    // get result and delete[] returned char* string
    std::cout << std::unique_ptr<char[]>(tess.GetUTF8Text()).get() << std::endl;

    std::cout << "did recognition" << std::endl;

    // cleanup
    tess.Clear();
    std::cout << "end" << std::endl;

    return 0;
}