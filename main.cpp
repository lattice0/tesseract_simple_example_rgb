#include <iostream>
#include <memory>

#include <allheaders.h> // leptonica main header for image io
#include <baseapi.h>    // tesseract main header
#include "libbmp/libbmp.h"
#include "utils.h"

//#include "../include/jpeg_file.h"
//#include "../include/rgb_file.h"

#define VERSION "0.1"

int main(int argc, char *argv[])
{
    std::cout << "begin" << std::endl;
    int rgbBufferWidth;
    int rgbBufferHeight;
    std::string imageName = "phototest.bmp"; 
    unsigned char *rgbBuffer = readBMP1(imageName.c_str(), &rgbBufferWidth, &rgbBufferHeight);
    int bytesPerPixel = 3;
    int bytesPerLine = bytesPerPixel * rgbBufferWidth;
    int rgbBufferSize = rgbBufferWidth * rgbBufferHeight * 3;
    std::cout << "readed " << imageName << ", width: " << rgbBufferWidth << " height: " << rgbBufferHeight << std::endl;
    tesseract::TessBaseAPI tess;
    
    if (tess.Init("./languages/", "eng"))
    {
        std::cout << "OCRTesseract: Could not initialize tesseract." << std::endl;
        return 1;
    }

    // setup
    tess.SetPageSegMode(tesseract::PageSegMode::PSM_AUTO);
    tess.SetVariable("save_best_choices", "T");

    // read image
    auto pixs = pixRead("phototest.tif");
    if (!pixs)
    {
        std::cout << "Cannot open input file: " << argv[1] << std::endl;
        return 1;
    }

    // recognize
    //tess.SetImage(pixs);
    tess.SetImage((const unsigned char*)rgbBuffer, rgbBufferWidth, rgbBufferHeight, bytesPerPixel, bytesPerLine);
    std::cout << "gonna recognize" << std::endl;
    tess.Recognize(0);

    // get result and delete[] returned char* string
    std::cout << std::unique_ptr<char[]>(tess.GetUTF8Text()).get() << std::endl;

    std::cout << "did recognition" << std::endl;

    // cleanup
    tess.Clear();
    pixDestroy(&pixs);
    std::cout << "end" << std::endl;

    return 0;
}
