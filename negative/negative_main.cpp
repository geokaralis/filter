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
	if (img.load("Image01.ppm", "ppm")) std::cout << img.getWidth();

	std::string input;
	PromptUser(argc, input);

	std::cin.get();
	return 0;
}

