#include "image.h"

#include <sstream>
#include <fstream>
#include <iostream>

#include "ppm.h"

using namespace imaging;

Image::Image() : Array() {}

Image::Image(unsigned int width, unsigned int height) : Array(width, height) {}

Image::Image(unsigned int width, unsigned int height, const std::vector<Color> data_ptr) : Array(width, height, data_ptr) {}

Image::Image(const Image &src) : Array(src) {}

Image::~Image()
{
	buffer.clear();
	buffer.shrink_to_fit();
}

bool Image::load(const std::string & filename, const std::string & format) {
	std::istringstream iss(filename);
	std::string extension, token;

	char* s0;
	// Converts: std::string to char*
	s0 = new char[filename.size() + 1];
	memcpy(s0, filename.c_str(), filename.size() + 1);

	// Extracting the extension from the given filename.
	while (std::getline(iss, token, '.'))
		if (!token.empty()) extension = token;

	// Case-insensitive comparison of extension, format.
	bool compare = std::equal(extension.begin(), extension.end(),
		format.begin(), format.end(),
		[](char extension, char format)
	{
		return tolower(extension) == tolower(format);
	});

	if (compare)
	{
		// If the current Image object is initialized.
		if (this != nullptr)
		{
			this->~Image();
		}
		int w = width;
		int h = height;

		

		float *data = ReadPPM(s0, &w, &h);

		width = w;
		height = h;

		int p = 0;
		Color c;
		for (int i = 0; i < w*h; i++) {
			c.r = data[p];
			c.g = data[p + 1];
			c.b = data[p + 2];
			p = p + 3;

			buffer.push_back(c);

		}

		return true;
	}
	return false;
}

bool Image::save(const std::string & filename, const std::string & format) {
	std::istringstream iss(filename);
	std::string extension, token;

	char* s0;
	// Converts: std::string to char*
	s0 = new char[filename.size() + 1];
	memcpy(s0, filename.c_str(), filename.size() + 1);

	// Extracting the extension from the given filename.
	while (std::getline(iss, token, '.'))
		if (!token.empty()) extension = token;

	// Case-insensitive comparison of extension and format.
	bool compare = std::equal(extension.begin(), extension.end(),
		format.begin(), format.end(),
		[](char extension, char format)
	{
		return tolower(extension) == tolower(format);
	});

	if (compare)
	{
		// Checking if the current Image object is initialized.
		if (this != nullptr)
		{
			int w = width;
			int h = height;

			float* array = new float[3 * w*h];

			int p = 0;
			for (int i = 0; i < w*h; i++)
			{
				array[p] = buffer[i].r;
				array[p + 1] = buffer[i].g;
				array[p + 2] = buffer[i].b;

				p += 3;
			}

			// Converts: Image01.ppm to Image01_neg.ppm
			std::string leftPart = filename, newFileName;
			newFileName = leftPart.substr(0, leftPart.find(".")) + "_filtered.ppm";

			char* s2;
			// Converts: std::string to char*
			s2 = new char[newFileName.size() + 1];
			memcpy(s2, newFileName.c_str(), newFileName.size() + 1);

			if (WritePPM((float *)array, w, h, s2)) {
				//std::cout << "Negative image created successfully" << std::endl;
			}

			return true;
		}


	}

	return false;
}