#include "lodepng.h"
#include <iostream>

int decodeOneStep(const char* filename, std::vector<unsigned char> *image, unsigned *width, unsigned *height);

void encodeOneStep(const char* filename, std::vector<unsigned char>& image, unsigned width, unsigned height);

void sepiaFilter(std::vector<unsigned char> *image, unsigned width, unsigned height);

void grayFilter(std::vector<unsigned char> *image, unsigned width, unsigned height);

// int main(int argc, char *argv[])
// {
// 	const char* filename = argc > 1 ? argv[1] : "test.png";
// 	std::vector<unsigned char> image; //the raw pixels
// 	unsigned width, height;
// 	decodeOneStep(filename, &image, &width, &height);
// 	grayFilter(&image, width, height);
// 	encodeOneStep(filename, image, width, height);

// }