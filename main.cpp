#include <iostream>
#include <memory>

#include <allheaders.h> // leptonica main header for image io
#include <baseapi.h> // tesseract main header

int main(int argc, char *argv[])
{
    std::cout << "begin" << std::endl;

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
    tess.SetImage(pixs);
    tess.Recognize(0);

    // get result and delete[] returned char* string
    std::cout << std::unique_ptr<char[]>(tess.GetUTF8Text()).get() << std::endl;

    // cleanup
    tess.Clear();
    pixDestroy(&pixs);
    std::cout << "end" << std::endl;

    return 0;
}
