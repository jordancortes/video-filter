//#include "lodepng.h"
#include "filters.h"
//#include <iostream>

void decodeOneStep(const char* filename, std::vector<unsigned char> *image, unsigned *width, unsigned *height)
{
  //decode
  unsigned error = lodepng::decode(*image, *width, *height, filename);

  //if there's an error, display it
  if(error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;

  //the pixels are now in the vector "image", 4 bytes per pixel, ordered RGBARGBA..., use it as texture, draw it, ...
}

void encodeOneStep(const char* filename, std::vector<unsigned char>& image, unsigned width, unsigned height)
{
  //Encode the image
  unsigned error = lodepng::encode(filename, image, width, height);

  //if there's an error, display it
  if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
}

void sepiaFilter(std::vector<unsigned char> *image, unsigned width, unsigned height){
	float inRed, inGreen, inBlue;
	for(unsigned y = 0; y < height*4; y++)
		#pragma vector always
		for(unsigned x = 0; x < width*4; x++)
		{
			int pos = width * y + x;
			float newColor;
			try{
				switch (pos % 4) {
					//RED
					case 0:
						inRed = image->at(pos);
						inGreen = image->at(pos+1);
						inBlue = image->at(pos+2);
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
						
						break;
					//GREEN
					case 1:
						newColor = (inRed * .349) + (inGreen * .686) + (inBlue * .168) - 30;
						if (newColor > 255) {
							image->at(pos) = 255;
						}
						else if (newColor < 0) {
							image->at(pos) = 0;
						}
						else {
							image->at(pos) = newColor;
						}
						break;
					//BLUE
					case 2:
						newColor = (inRed * .272) + (inGreen * .534) + (inBlue * .131) - 30;
						if (newColor > 255) {
							image->at(pos) = 255;
						}
						else if (newColor < 0) {
							image->at(pos) = 0;
						}
						else {
							image->at(pos) = newColor;
						}
						break;
				}
			}
			catch(std::out_of_range e){
			}
		}
}

void grayFilter(std::vector<unsigned char> *image, unsigned width, unsigned height){
	float inRed, inGreen, inBlue;
	for(unsigned y = 0; y < height*4; y++)
		//#pragma vector always
		for(unsigned x = 0; x < width*4; x = x + 4)
		{
			int pos = width * y + x;
			float newColor;
			try{
				inRed = image->at(pos);
				inGreen = image->at(pos+1);
				inBlue = image->at(pos+2);
				newColor = ( inRed + inGreen + inBlue ) / 3;
				image->at(pos) = newColor;
				image->at(pos + 1) = newColor;
				image->at(pos + 2) = newColor;
			}
			catch(std::out_of_range e){
			}
		}
}

// int main(int argc, char *argv[])
// {
// 	const char* filename = argc > 1 ? argv[1] : "test.png";
// 	std::vector<unsigned char> image; //the raw pixels
// 	unsigned width, height;
// 	decodeOneStep(filename, &image, &width, &height);
// 	grayFilter(&image, width, height);
// 	encodeOneStep(filename, image, width, height);

// }