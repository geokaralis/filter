#include "image.h"
#include <sstream>
#include<fstream>
#include<iostream>

using namespace imaging;

Color * imaging::Image::getRawDataPtr()
{
	return buffer;
}

Color imaging::Image::getPixel(unsigned int x, unsigned int y) const
{
	return Color();
}

void imaging::Image::setPixel(unsigned int x, unsigned int y, Color & value)
{
}

void imaging::Image::setData(const Color *& data_ptr)
{
	buffer = const_cast<Color*>(data_ptr);
}

imaging::Image::Image() : width(0), height(0), buffer(nullptr)
{
}

imaging::Image::Image(unsigned int width, unsigned int height) : width(width), height(height), buffer(nullptr)
{
}

imaging::Image::Image(unsigned int width, unsigned int height, const Color * data_ptr) : width(width), height(height)
{
	setData(data_ptr);
}

imaging::Image::Image(const Image & src) : width(src.width), height(src.height), buffer(src.buffer)
{
}

imaging::Image::~Image()
{
	delete buffer;
}

Image & imaging::Image::operator=(const Image & right)
{
	Image img = Image(right);
	return img;
}

bool imaging::Image::load(const std::string & filename, const std::string & format)
{
	std::istringstream iss(filename);
	std::string extension, token;

	while (std::getline(iss, extension, '.'))
		//if (!token.empty()) extension = token;

		if (extension.compare(format) == 0)
		{

			std::ifstream is;
			std::string header;
			int width, height, rgb;

			is.open(filename, std::ios::binary);
			if (!is.is_open()) throw("Cannot open file");
			is >> header >> width >> height >> rgb;

			this->width = width;
			this->height = height;

			if (header.compare("P6") != 0) throw("Cannot read file. Must be P6");
			if (rgb > 255) throw("Cannot read file. Color intensity must be up to 255");


			return true;
		}

	return false;
}

bool imaging::Image::save(const std::string & filename, const std::string & format)
{
	return false;
}