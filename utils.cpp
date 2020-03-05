#include <fstream>
#include <iostream>
#include <string>
#include "string.h"

using namespace std;
unsigned char* readBMP2(const char* filename, int* width, int* height)
{
    int i;
    FILE* f = fopen(filename, "rb");
    unsigned char info[54];
    fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header

    // extract image height and width from header
    //int width, height;
    memcpy(width, info + 18, sizeof(int));
    memcpy(height, info + 22, sizeof(int));

    int heightSign = 1;
    if (height < 0){
        heightSign = -1;
    }

    int size = 3 * (*width) * abs(*height);
    unsigned char* data = new unsigned char[size]; // allocate 3 bytes per pixel
    fread(data, sizeof(unsigned char), size, f); // read the rest of the data at once
    fclose(f);

    if(heightSign == 1){
        for(i = 0; i < size; i += 3)
        {
            //code to flip the image data here....
        }
    }
    return data;
}