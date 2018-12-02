#include "command_line.h"

bool CommandLine::FilePresent(int argc) {
	if (argc != 2) {
		return false;
	}
	return true;
}

void CommandLine::PromptUser(std::string &input) {
	std::cout << "File name of the image to load: ";
	std::cin >> input;
}

void CommandLine::PrintLogo()
{
	std::cout << "(c) 2018, George Kavalieros, George Karalis" << std::endl;
	std::cout << std::endl;
}

int CommandLine::Init(int argc, char** argv) {
	PrintLogo();

	std::string image_file;

	// Checking for user input.
	if (CommandLine::FilePresent(argc))
	{
		image_file = argv[1];
	}
	else
	{
		CommandLine::PromptUser(image_file);
	}

	negative::CreateNegativeImage(image_file);

	std::cout << "Press any key to close..." << std::endl;
	std::cin.ignore();
	std::cin.get();
	return 0;
}