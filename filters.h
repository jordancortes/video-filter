#include "lodepng.h"
#include <iostream>

int decodeOneStep(const char* filename, std::vector<unsigned char> *image, unsigned *width, unsigned *height);

void encodeOneStep(const char* filename, std::vector<unsigned char>& image, unsigned width, unsigned height);

void sepiaFilter(std::vector<unsigned char> *image, unsigned width, unsigned height);

void grayFilter(std::vector<unsigned char> *image, unsigned width, unsigned height);

void invertedFilter(std::vector<unsigned char> *image, unsigned width, unsigned height);