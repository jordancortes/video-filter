#include "filters.h"

int decodeOneStep(const char* filename,
                   std::vector<unsigned char> *image,
                   unsigned *width,
                   unsigned *height)
{
	// decode
    unsigned error = lodepng::decode(*image, *width, *height, filename);

    // if there's an error, display it
    if(error)
    {
        return 1;
    }

    return 0;
}

void encodeOneStep(const char* filename,
                   std::vector<unsigned char>& image,
                   unsigned width,
                   unsigned height)
{
	// Encode the image
	unsigned error = lodepng::encode(filename, image, width, height);

	// if there's an error, display it
	if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
}

void sepiaFilter(std::vector<unsigned char> *image,
                 unsigned width,
                 unsigned height)
{
	float inRed, inGreen, inBlue;
	for(unsigned y = 0; y < height; y++)
		#pragma simd
		for(unsigned x = 0; x < width; x++)
		{
			int pos = ( width * y + x ) * 4;
			float newColor;
			inRed = image->at(pos);
			inGreen = image->at(pos+1);
			inBlue = image->at(pos+2);
		//RED
			newColor = (inRed * .393) + (inGreen * .769) + (inBlue * .189) - 30;
			if (newColor > 255) {
				image->at(pos) = 255;
			}
			else if (newColor < 0) {
				image->at(pos) = 0;
			}
			else {
				image->at(pos) = newColor;
			}

		//GREEN
			newColor = (inRed * .349) + (inGreen * .686) + (inBlue * .168) - 30;
			if (newColor > 255) {
				image->at(pos + 1) = 255;
			}
			else if (newColor < 0) {
				image->at(pos + 1) = 0;
			}
			else {
				image->at(pos + 1) = newColor;
			}
		//BLUE
			newColor = (inRed * .272) + (inGreen * .534) + (inBlue * .131) - 30;
			if (newColor > 255) {
				image->at(pos + 2) = 255;
			}
			else if (newColor < 0) {
				image->at(pos + 2) = 0;
			}
			else {
				image->at(pos + 2) = newColor;
			}
		}
}

void grayFilter(std::vector<unsigned char> *image,
                unsigned width,
                unsigned height)
{
	float inRed, inGreen, inBlue;
	for(unsigned y = 0; y < height; y++)
		#pragma simd
		for(unsigned x = 0; x < width; x++)
		{
			int pos = ( width * y + x ) * 4 ;
			float newColor;
			inRed = image->at(pos);
			inGreen = image->at(pos+1);
			inBlue = image->at(pos+2);
			newColor = ( inRed + inGreen + inBlue ) / 3;
			image->at(pos) = newColor;
			image->at(pos + 1) = newColor;
			image->at(pos + 2) = newColor;
		}
}

void invertedFilter(std::vector<unsigned char> *image,
                unsigned width,
                unsigned height)
{
    float inRed, inGreen, inBlue;
    for(unsigned y = 0; y < height; y++)
        #pragma simd
        for(unsigned x = 0; x < width; x++)
        {
            int pos = ( width * y + x ) * 4 ;
            float newColor;
            inRed = image->at(pos);
            inGreen = image->at(pos+1);
            inBlue = image->at(pos+2);
            image->at(pos) = 255 - inRed;
            image->at(pos + 1) = 255 - inGreen;
            image->at(pos + 2) = 255 - inBlue;
        }
}