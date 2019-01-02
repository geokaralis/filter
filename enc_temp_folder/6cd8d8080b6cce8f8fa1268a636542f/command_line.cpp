#include "command_line.h"

#include "../../imaging/image.h"
#include "../../imaging/filter/filter_gamma.h"
#include "../../imaging/filter/filter_linear.h"

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

bool CommandLine::FilePresent(int argc) 
{
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
	for (int i = 0; i < args.size(); i++) {
		if (args[i] == "-f") {
			int j = i + 1;

			if (args[j] == "gamma") {
				// args[j] == "gamma"
				// args[j + 1] == value of gamma --> e.g. 2.0f
				filter.insert(filter.end(), { args[j], args[j + 1] });
				Allfilters.push_back(filter);
				filter.clear();
			}else if (args[j] == "linear") {
				// args[j] == "linear"
				// args[j + 1] == value of aR --> e.g. -1
				// args[j + 2] == value of aG --> e.g. -1
				// ...
				// args[j + 6] == value of cB --> e.g. 1
				filter.insert(filter.end(), { args[j], args[j + 1], args[j + 2], args[j + 3], args[j + 4], args[j + 5], args[j + 6] });
				Allfilters.push_back(filter);
				filter.clear();
			} // !endif gamma || linear
		} // !endif -f
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
	if (FilePresent(argc)) {
		image_file = args[1];
	}else {
		
		std::cout << "Specify filter(s): "; // -f gamma 2.0 -f linear 1 1 1

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

void CommandLine::A(std::string filename, std::vector<std::vector<std::string>> filters) {
	Image *image = new Image();

	//for (auto f : filters) {
	//	for (auto x : f) {
	//		std::cout << x << std::endl;
	//	}
	//}

	if (image->load(filename, "ppm")) {
		for (int i = 0; i < filters.size(); ++i) {
			if (filters[i][0] == "gamma") {
				float gamma = std::stof(filters[i][1]);
				std::cout << "BHKE GAMMA" << std::endl;
				FilterGamma *filter_gamma = new FilterGamma(gamma);
				*image = *filter_gamma << *image;
			}else if (filters[i][0] == "linear") {
				float aR = std::stof(filters[i][1]);
				float aG = std::stof(filters[i][2]);
				float aB = std::stof(filters[i][3]);
				float cR = std::stof(filters[i][4]);
				float cG = std::stof(filters[i][5]);
				float cB = std::stof(filters[i][6]);

				Color* a = new Color(aR, aG, aB);
				Color* c = new Color(cR, cG, cB);
				std::cout << "BHKE LINEAR" << std::endl;
				FilterLinear *filter_linear = new FilterLinear(*a, *c);
				*image = *filter_linear << *image;
			}
		}
		
		
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