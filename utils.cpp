#include "stdio.h"
#include "utils.h"
#include "iostream"
#include "math.h"
#include "string.h"
/*
unsigned char* readBMP(const char* filename, int* width, int* height)
{
    int i;
    FILE* f = fopen(filename, "rb");
    unsigned char info[54];
    fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header

    // xtract image height and width from header
    *width = *(int*)&info[18];
    *height = *(int*)&info[22];
    //printf("%d", *width);

    int size = 3 * (*width) * (*height);
    unsigned char* data = new unsigned char[size]; // allocate 3 bytes per pixel
    fread(data, sizeof(unsigned char), size, f); // read the rest of the data at once
    fclose(f);

    for(i = 0; i < size; i += 3)
    {
            unsigned char tmp = data[i];
            data[i] = data[i+2];
            data[i+2] = tmp;
    }

    return data;
}
*/

#include <fstream>
#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <iterator>

std::vector<char> readBMP1(const char* filename, int* width, int* height)
{
    static constexpr size_t HEADER_SIZE = 54;

    std::ifstream bmp(filename, std::ios::binary);

    std::array<char, HEADER_SIZE> header;
    bmp.read(header.data(), header.size());

    auto fileSize = *reinterpret_cast<uint32_t *>(&header[2]);
    auto dataOffset = *reinterpret_cast<uint32_t *>(&header[10]);
    *width = *reinterpret_cast<uint32_t *>(&header[18]);
    *height = *reinterpret_cast<uint32_t *>(&header[22]);
    auto depth = *reinterpret_cast<uint16_t *>(&header[28]);

    std::cout << "fileSize: " << fileSize << std::endl;
    std::cout << "dataOffset: " << dataOffset << std::endl;
    std::cout << "width: " << *width << std::endl;
    std::cout << "height: " << *height << std::endl;
    std::cout << "depth: " << depth << "-bit" << std::endl;

    std::vector<char> img(dataOffset - HEADER_SIZE);
    bmp.read(img.data(), img.size());

    auto dataSize = ((*width * 3 + 3) & (~3)) * *height;
    img.resize(dataSize);
    bmp.read(img.data(), img.size());

    char temp = 0;

    for (auto i = dataSize - 4; i >= 0; i -= 3)
    {
        temp = img[i];
        img[i] = img[i+2];
        img[i+2] = temp;

        //std::cout << "R: " << int(img[i] & 0xff) << " G: " << int(img[i+1] & 0xff) << " B: " << int(img[i+2] & 0xff) << std::endl;
    }

    //return (unsigned char* ) img.data();
    return img;
}

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