#include "application.h"

#include "../imaging/image.h"
#include "../imaging/filter/filter_gamma.h"
#include "../imaging/filter/filter_linear.h"
#include "../imaging/filter/filter_blur.h"
#include "../imaging/filter/filter_laplace.h"

#include <sstream>
#include <fstream>
#include <iostream>

using namespace imaging;

bool app::ArgumentsExist(int argc)
{
	if (argc > 2) {
		return true;
	}

	return false;
}

bool app::FilePresent(int argc)
{
	if (argc < 2) {
		return false;
	}
	return true;
}

void app::LoadFile(std::string& input)
{
	std::cout << "File name of the image to load: ";
	std::cin >> input;
}


// Removes all filters from args.
// Adds these filters to Allfilters.
std::vector<std::vector<std::string>> app::ParseFiltersFromArguments(std::vector<std::string> &args) {
	std::vector<std::string> filter;                        // contains a filter and its values            --> e.g. {"gamma", "2.0"}
	std::vector<std::vector<std::string>> Allfilters;        // contains all filters and their values.    --> e.g. {{"gamma", "2.0"}, ... }


	//while (args = parse("-f", args)) // -f gamma 2.0 -
	//{
		// insert
	//}

	// [gamma, 2.0][linear, 1, 1, ...]
	
	/*std::vector<Node> filters;
	Node n = new Node("gamma", args)*/
	

	// Range-based for loop with argv.
	for (int i = 0; i < args.size(); i++) {
		if (args[i] == "-f") {
			int j = i + 1;

			if (args[j] == "gamma" || args[j] == "blur") {
				// args[j] == "gamma"
				// args[j + 1] == value of gamma --> e.g. 2.0
				filter.insert(filter.end(), { args[j], args[j + 1] });
				Allfilters.push_back(filter);
				filter.clear();
			}
			else if (args[j] == "linear") {
				// args[j] == "linear"
				// args[j + 1] == value of aR --> e.g. -1
				// args[j + 2] == value of aG --> e.g. -1
				// ...
				// args[j + 6] == value of cB --> e.g. 1
				filter.insert(filter.end(), { args[j], args[j + 1], args[j + 2], args[j + 3], args[j + 4], args[j + 5], args[j + 6] });
				Allfilters.push_back(filter);
				filter.clear();
			}
			else if (args[j] == "laplace") {
				// args[j] == "linear"				
				filter.insert(filter.end(), { args[j] });
				Allfilters.push_back(filter);
				filter.clear();
			}// !endif (gamma || blur || linear || laplace)
		} // !endif -f
	}
	return Allfilters;
}

void app::Init(int argc, char ** argv)
{
	base::CommandLine::Init(argc, argv);

	std::string image_file;

	std::string input_filter_args;

	// Store argv in a vector of strings (args). 
	// NOTE: System cant tell how long argv is at compile time
	std::vector<std::string> args(argv, argv + argc);

	std::vector<std::string> input_args;

	std::vector<std::vector<std::string>> Allfilters;

	if (ArgumentsExist(argc)) {
		Allfilters = ParseFiltersFromArguments(args);
	}

	// Checking for user input.
	if (FilePresent(argc)) {
		image_file = args[args.size() - 1];
	}
	else {

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

		Allfilters = ParseFiltersFromArguments(args);

		LoadFile(image_file);


		Image *image = new Image();

		if (image->load(image_file, "ppm")) {
			for (int i = 0; i < Allfilters.size(); ++i) {
				//Node
				//FilterNode
				// filters[i].getFilter()
				// *image = filters[i] << *image;
				if (Allfilters[i][0] == "gamma") {
					float gamma = std::stof(Allfilters[i][1]);

					FilterGamma *filter_gamma = new FilterGamma(gamma);
					*image = *filter_gamma << *image;
				}
				else if (Allfilters[i][0] == "linear") {
					float aR = std::stof(Allfilters[i][1]);
					float aG = std::stof(Allfilters[i][2]);
					float aB = std::stof(Allfilters[i][3]);
					float cR = std::stof(Allfilters[i][4]);
					float cG = std::stof(Allfilters[i][5]);
					float cB = std::stof(Allfilters[i][6]);

					Color* a = new Color(aR, aG, aB);
					Color* c = new Color(cR, cG, cB);

					FilterLinear *filter_linear = new FilterLinear(*a, *c);
					*image = *filter_linear << *image;
				}
				else if (Allfilters[i][0] == "blur") {
					unsigned int blur = std::stoi(Allfilters[i][1]);

					FilterBlur *filter_blur = new FilterBlur(blur);
					*image = *filter_blur << *image;
				}
				else if (Allfilters[i][0] == "laplace") {
					FilterLaplace *filter_laplace = new FilterLaplace();
					*image = *filter_laplace << *image;
				}
			}


		}
		else {
			std::cout << "File isn't recognized as a valid ppm image." << std::endl;
			std::cout << "Only .ppm files are accepted." << std::endl;
		}

		if (image->save(image_file, "ppm")) {

			std::cout << "Image dimensions are: " << image->getWidth() << " X " << image->getHeight() << std::endl;
			std::cout << "Image filtering applied..." << std::endl;
		}
		else {
			std::cout << "Cannot save image" << std::endl;
		}

		base::CommandLine::Terminate();
	}
}
