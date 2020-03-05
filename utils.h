#ifndef UTILS_H
#define UTILS_H
#include <iostream>
#include <vector>
std::vector<char> readBMP1(const char* filename, int* width, int* height);
unsigned char* readBMP2(const char* filename, int* width, int* height);

#endif //UTILS_H