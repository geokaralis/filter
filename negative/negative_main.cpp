// The application main

#include <iostream>
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

	imaging::Image img;
	int w = img.getWidth();
	int h = img.getHeight();

	float *array = imaging::ReadPPM("Image01.ppm", &w, &h);

	for (int i = 0; i < 10; i++) {
		std::cout << "from negative " << array[i] << std::endl;
	}
	/*if (img.load("Image01.ppm", "ppm"))
	{
		float *array = imaging::ReadPPM("Image01.ppm", &w, &h); 

	};*/

	/*std::cout << "----------------\n";
	imaging::Color c = img.getPixel(0,1);
	std::cout << c.r << " " << c.g << " " << c.b;*/

	/*std::string input;
	PromptUser(argc, input);*/

	std::cin.get();
	return 0;
}

