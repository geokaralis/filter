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

	std::ifstream ifs;

	/*!
	 * @TODO: Use argv instead of filename;
	 */
	std::string filename = "Image01.ppm";
	/*ifs.open(filename, std::ios::binary);*/

	imaging::Image img; // = new imaging::Image(45, 50, new imaging::Color(50, 60, 50));

	if (img.load(filename, "ppm"))
	{
		//float *array = imaging::ReadPPM("Image01.ppm", img.getWidth, img.getHeight);
		std::cout << img.getPixel(0, 5).r;
	};
	

	/*std::cout << "----------------\n";
	imaging::Color c = img.getPixel(0,1);
	std::cout << c.r << " " << c.g << " " << c.b;*/

	/*std::string input;
	PromptUser(argc, input);*/

	std::cin.get();
	return 0;
}

