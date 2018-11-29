// The application main

#include <iostream>
#include <fstream>
#include <string>

#include "ppm.h"
#include "image.h"

#define LOG(x) std::cout << x << std::endl;

bool FilePresent(int argc) {
	if (argc != 2) {
		std::cout << "You didn't provide a file" << std::endl;
		return false;
	}

	std::cout << "File is good" << std::endl;
	return true;
}

void PromptUser(int argc, std::string input) {
	if (FilePresent(argc)) {
		LOG("File is present");

		return;
	}

	std::cout << "Write the file: ";
	std::cin >> input;
}

int main(int argc, char** argv) {

	imaging::Image *image = new imaging::Image();
	if (true /*img.load("Image01.ppm", "ppm")*/)
	{
		// img.getWidth() and img.getHeight() are ZERO.
		int w = 0;
		int h = 0;

		float *array = imaging::ReadPPM("Image01.ppm", &w, &h);

		image = new imaging::Image(w, h);

		imaging::Color *buffer = image->getRawDataPtr();

		for (int i = 0, j = 0; i < w*h && j < w*h * 3; i++, j += 3)
		{
			buffer[i][0] = array[j];
			buffer[i][1] = array[j + 1];
			buffer[i][2] = array[j + 2];
		}

		imaging::Color *white = new imaging::Color(1,1,1);

		for (int i = 0; i < w*h; i++)
		{
			buffer[i] = *white - buffer[i];
		}

		array = (float*)buffer;

		LOG("Begin to write negative image");

		/*int width = w;
		int height = h;*/

		imaging::WritePPM(array, w, h, "Image01_neg.ppm");
		//image->save("Image01_neg.ppm", "ppm");
		std::cout << "\n\ndone";
	};

	/*std::cout << "----------------\n";
	imaging::Color c = img.getPixel(0,1);
	std::cout << c.r << " " << c.g << " " << c.b;*/

	/*std::string input;
	PromptUser(argc, input);*/

	std::cin.get();
	return 0;
}

