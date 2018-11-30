#include "cli.h"

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
		std::cout << "File is present" << std::endl;

		return;
	}

	std::cout << "Write the file: ";
	std::cin >> input;
}