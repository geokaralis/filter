#include "cli.h"

bool FilePresent(int argc) {
	if (argc != 2) {
		return false;
	}
	return true;
}

char* PromptUser(std::string &input) {
	char* s0;
	std::cout << "File name of the image to load: ";
	std::cin >> input;
	
	// Converts: std::string to char*
	s0 = new char[input.size() + 1];
	memcpy(s0, input.c_str(), input.size() + 1);

	return s0;
}