#include <iostream>
#include <memory>

#include <allheaders.h> // leptonica main header for image io
#include <baseapi.h> // tesseract main header



#include "../include/jpeg_file.h"
#include "../include/rgb_file.h"

#define VERSION "0.1"





int main(int argc, char *argv[])
{
    std::cout << "begin" << std::endl;

    tesseract::TessBaseAPI tess;

    char* jpeg_file_path = argv[1];

    jpeg_file* jpeg_file = load_jpeg_file(jpeg_file_path);
    rgb_file* rgb_file = decode_jpeg_to_rgb(jpeg_file);
    uint8_t* rgbImageBuffer = rgb_file->rgb_buffer;
    size_t rgbImageBufferSize = rgb_file->rgb_buffer_size;
    int width = rgb_file->header.width;
    int height = rgb_file->header.height;
    int bytesPerPixel = rgb_file->header.bpp;
    int bytesPerLine = width*bytesPerPixel;

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
    tess.SetImage(rgbImageBuffer, width, height, bytesPerPixel, bytesPerLine);
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
