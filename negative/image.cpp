#include "image.h"

#include <sstream>
#include <fstream>
#include <iostream>

#include "ppm.h"

using namespace imaging;

Color * Image::getRawDataPtr() {
	return buffer;
}

Color Image::getPixel(unsigned int x, unsigned int y) const {
	Color c = Color();
	// Checking the bounds of Image.
	if (x < width && y < height && x >= 0 && y >= 0)
	{
		c.r = buffer[x + (y * width)].r;
		c.g = buffer[x + (y * width)].g;
		c.b = buffer[x + (y * width)].b;
	}
	return c;
}

void Image::setPixel(unsigned int x, unsigned int y, Color & value) {
	// Checking the bounds of Image.
	if (x < width && y < height && x >= 0 && y >= 0)
	{
		buffer[x + (y * width)].r = value.r;
		buffer[x + (y * width)].g = value.g;
		buffer[x + (y * width)].b = value.b;
	}
}

void Image::setData(const Color *& data_ptr) {
	buffer = new Color[width*height];
	memcpy(buffer, data_ptr, width*height);
}

Image::Image() {
	this->width = 0;
	this->height = 0;
	this->buffer = nullptr;
}

Image::Image(unsigned int width, unsigned int height) {
	this->width = width;
	this->height = height;
	buffer = new Color[width*height];
}

Image::Image(unsigned int width, unsigned int height, const Color * data_ptr) {
	this->width = width;
	this->height = height;
	setData(data_ptr);
}

Image::Image(const Image & src) {
	this->width = src.width;
	this->height = src.height;
	buffer = new Color[src.width*src.height];
	memcpy(buffer, src.buffer, src.width*src.height);
}

Image::~Image() {
	delete[] buffer;
}

Image & Image::operator=(const Image & right) {
	Image *img = new Image(right);
	return *img;
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

		buffer = new Color[w*h];

		int p = 0;


		for (int i = 0; i < w*h; i++) {
			this->buffer[i].r = data[p];
			this->buffer[i].g = data[p + 1];
			this->buffer[i].b = data[p + 2];

			p = p + 3;
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

			if (WritePPM((float*)buffer, w, h, s0)) {
				std::cout << "Negative image created successfully" << std::endl;
			}

			return true;
		}

		
	}

	return false;
}