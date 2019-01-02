#include "command_line.h"

#include "../../imaging/image.h"
#include "../../imaging/filter/filter_gamma.h"

#include <sstream>
#include <fstream>
#include <iostream>

using namespace imaging;

namespace base {

const std::string header = "Filter [Build " + std::string(BUILD_VERSION) 
							+ "]\n" + "(c) 2019, George Kavalieros, George Karalis.\n";

bool CommandLine::ArgumentsExist(int argc)
{
	if (argc > 2) {
		return true;
	}

	return false;
}

bool CommandLine::FilePresent(int argc) {
	if (argc < 2) {
		return false;
	}
	return true;
}

void CommandLine::LoadFile(std::string& input)
{
	std::cout << "File name of the image to load: ";
	std::cin >> input;
}

void CommandLine::PrintHeader()
{
	std::cout << header;
	std::cout << std::endl;
}

// Removes all filters from args.
// Adds these filters to Allfilters.
std::vector<std::vector<std::string>> CommandLine::ReadFilters(std::vector<std::string> &args) {
	std::vector<std::string> filter;                        // contains a filter and its values            --> e.g. {"gamma", "2.0"}
	std::vector<std::vector<std::string>> Allfilters;        // contains all filters and their values.    --> e.g. {{"gamma", "2.0"}, ... }

	// Range-based for loop with argv.
	for (int i = 0; i < args.size(); i++)
	{
		
		if (args[i] == "-f")
		{
			int j = i + 1;
			if (args[j] == "gamma")
			{
				// args[j] == "gamma"
				// args[j + 1] == value of gamma --> e.g. 2.0f
				filter.insert(filter.end(), { args[j], args[j + 1] });

				// Remove the filter and its values from args
				args.erase(args.begin() + i, args.begin() + (j + 2));
			}
			else if (args[j] == "linear")
			{
				// args[j] == "linear"
				// args[j + 1] == value of aR --> e.g. -1
				// args[j + 2] == value of aG --> e.g. -1
				// ...
				// args[j + 6] == value of cB --> e.g. 1
				filter.insert(filter.end(), { args[j], args[j + 1], args[j + 2], args[j + 3], args[j + 4], args[j + 5], args[j + 6] });

				// Remove the filter and its values from args
				args.erase(args.begin() + i, args.begin() + (j + 7));
			}

			Allfilters.push_back(filter);
		}
	}
	return Allfilters;
}



// static
int CommandLine::Init(int argc, char** argv) {
	PrintHeader();

	std::string image_file;

	std::string input_filter_args;

	// Store argv in a vector of strings (args). 
	// NOTE: System cant tell how long argv is at compile time
	std::vector<std::string> args(argv, argv + argc);

	std::vector<std::string> input_args;

	std::vector<std::vector<std::string>> Allfilters;

	if (ArgumentsExist(argc)) {
		Allfilters = ReadFilters(args);
	}

	// Checking for user input.
	if (FilePresent(argc))
	{
		image_file = args[1];
	}
	else
	{
		
		std::cout << "Specify filter(s): "; // -f gamma 2.0 -f linear 1 1 1
		//std::cin >> input_filter_args;

		std::getline(std::cin, input_filter_args);

		std::istringstream iss(input_filter_args);
		std::string token;

		// Split input filters into args.
		int i = 1;
		while (std::getline(iss, token, ' ')) {
			args.insert(args.begin() + i, token);
			++i;
		}

		Allfilters = ReadFilters(args);

		std::cout << Allfilters[0][0] << std::endl;

		CommandLine::LoadFile(image_file);
	}

	A(image_file, Allfilters);

	std::cout << "Press any key to close..." << std::endl;
	std::cin.ignore();
	std::cin.get();
	return 0;
}

CommandLine::CommandLine() { }

CommandLine::CommandLine(int argc, char** argv) 
	: argc(argc), 
	  argv(argv) { }

CommandLine::~CommandLine() = default;

void CommandLine::A(std::string filename, std::vector<std::vector<std::string>> filters)
{
	Image *image = new Image();

	Color* a = new Color(-1, -1, -1);
	Color* c = new Color(1, 1, 1);

	std::cout << filters[0][1] << std::endl;

	float gamma = std::stof(filters[0][1]);

	if (image->load(filename, "ppm")) {
		//FilterLinear* linear_filter = new FilterLinear(*a, *c);
		FilterGamma* gamma_filter = new FilterGamma(gamma);

		*image = *gamma_filter << *image;

		//*image = *linear_filter << *image;
	}
	else {
		std::cout << "File isn't recognized as a valid ppm image." << std::endl;
		std::cout << "Only .ppm files are accepted." << std::endl;
	}

	if (image->save(filename, "ppm")) {
		std::cout << "Image dimensions are: " << image->getWidth() << " X " << image->getHeight() << std::endl;
		std::cout << "Image filtering applied..." << std::endl;
	}
	else {
		std::cout << "Cannot save image" << std::endl;
	}
}

} // namespace base