#include "command_line.h"

bool CommandLine::FilePresent(int argc) {
	if (argc != 2) {
		return false;
	}
	return true;
}

char* CommandLine::PromptUser(std::string &input) {
	char* s0;
	std::cout << "File name of the image to load: ";
	std::cin >> input;
	
	// Converts: std::string to char*
	s0 = new char[input.size() + 1];
	memcpy(s0, input.c_str(), input.size() + 1);

	return s0;
}

void CommandLine::PrintLogo()
{
	std::cout << "(c) 2018, George Kavalieros, George Karalis" << std::endl;
	std::cout << std::endl;
}

int CommandLine::Init(int argc, char** argv) {
	PrintLogo();

	std::string image_file;
	char* input;

	// Checking for user input.
	if (CommandLine::FilePresent(argc))
	{
		input = argv[1];
		image_file = argv[1];
	}
	else
	{
		input = CommandLine::PromptUser(image_file);
	}

	Image *image = new Image();

	if (image->load(image_file, "ppm")) {

		// img.getWidth() and img.getHeight() are ZERO.
		int w = image->getWidth();
		int h = image->getHeight();

		// Checking for input from user.
		float *data = ReadPPM(input, &w, &h);

		image = new Image(w, h);
		Color *color = image->getRawDataPtr();

		negative::FillColorFromRawData(color, data, w, h);
		negative::ApplyNegativeFilter(color, w, h);

		if (image->save(image_file, "ppm")) {
			LOG("Image dimensions are: " << image->getWidth() << " X " << image->getHeight());
			if (WritePPM((float*)color, w, h, input)) {
				LOG("Negative image created successfully");
			}
		}
	}
	else {
		std::cout << "File isn't recognized as a valid ppm image." << std::endl;
		std::cout << "Only .ppm files are accepted." << std::endl;
	}

	std::cout << "Press any key to close..." << std::endl;

	std::cin.ignore();
	std::cin.get();
	return 0;
}