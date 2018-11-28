#include "image.h"
#include <sstream>
#include <fstream>
#include <iostream>

using namespace imaging;

Color * imaging::Image::getRawDataPtr()
{
	return buffer;
}

Color imaging::Image::getPixel(unsigned int x, unsigned int y) const
{
	Color c = Color();
	// Checking the bounds of Image.
	if (x < width && y < height && x >= 0 && y >= 0)
	{
		c.r = buffer[x*width + y].r;
		c.g = buffer[x*width + y].g;
		c.b = buffer[x*width + y].b;
	}
	return c;
}

void imaging::Image::setPixel(unsigned int x, unsigned int y, Color & value)
{
	// Checking the bounds of Image.
	if (x < width && y < height && x >= 0 && y >= 0)
	{
		buffer[x*width + y].r = value.r;
		buffer[x*width + y].g = value.g;
		buffer[x*width + y].b = value.b;
	}
}

void imaging::Image::setData(const Color *& data_ptr)
{
	buffer = new Color[width*height];
	memcpy(buffer, data_ptr, width*height);
}

imaging::Image::Image() : width(0), height(0), buffer(nullptr)
{
}

imaging::Image::Image(unsigned int width, unsigned int height) : width(width), height(height)
{
	buffer = new Color[width*height];
}

imaging::Image::Image(unsigned int width, unsigned int height, const Color * data_ptr) : width(width), height(height)
{
	setData(data_ptr);
}

imaging::Image::Image(const Image & src) : width(src.width), height(src.height)
{
	buffer = new Color[src.width*src.height];
	memcpy(buffer, src.buffer, src.width*src.height);
}

imaging::Image::~Image()
{
	delete[] buffer;
}

Image & imaging::Image::operator=(const Image & right)
{
	Image *img = new Image(right);
	return *img;
}

bool imaging::Image::load(const std::string & filename, const std::string & format)
{
	std::istringstream iss(filename);
	std::string extension, token;

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

		return true;
	}
	return false;
}

bool imaging::Image::save(const std::string & filename, const std::string & format)
{
	std::istringstream iss(filename);
	std::string extension, token;

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
			return true;
		}
	}
	return false;
}