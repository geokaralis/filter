#include "image.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>

#define BUFFERSIZE width*height

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
	memcpy(buffer, data_ptr, BUFFERSIZE);
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
		try
		{
			std::ifstream ifs;
			std::string header;
			unsigned int width, height, rgb;

			ifs.open(filename, std::ios::binary);


			if (!ifs.is_open()) throw("Cannot open file");
			ifs >> header >> width >> height >> rgb;

			this->width = width;
			this->height = height;

			if (header.compare("P6") != 0) throw("Cannot read file. Must be P6");
			if (rgb > 255) throw("Cannot read file. Color intensity must be up to 255");


			int tmpbufferSize = BUFFERSIZE * 3;
			unsigned char *tmp = new unsigned char[tmpbufferSize];

			buffer = new Color[BUFFERSIZE];

			ifs.read((char*)tmp, BUFFERSIZE);

			for (int i = 0, j = 0; i < BUFFERSIZE && j < tmpbufferSize; i++, j+=3)
			{
				buffer[i][0] = (float)tmp[j];
				buffer[i][1] = (float)tmp[j+1];
				buffer[i][2] = (float)tmp[j+2];
			}

			for (int i = 0; i < 5; i++)
			{
				std::cout << buffer[i][0] << " " << buffer[i][1] << " " << buffer[i][2] << std::endl;
			}

			/*const int bufferSize = width * height;
			buffer = new Color[bufferSize];

			std::cout << sizeof(buffer[0]);
			std::cout << sizeof(char);

			ifs.read((char *)buffer, bufferSize); rgb rgb rgb rgb rgb rgb rgb rgb 

			buffer[0]*/

			ifs.close();

			return true;
		}
		catch (std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
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
			try
			{
				// Setting up the header of PPM file. 
				std::ofstream ofs(filename, std::ios::binary);
				ofs << "P6\n";
				ofs << this->width << "\n";
				ofs << this->height << "\n";
				ofs << "255\n";

				// Write buffer data to the given file.
				ofs.write((char*)buffer, width * height * 3);
				ofs.close();

				return true;
			}
			catch (std::exception& e)
			{
				std::cout << e.what() << std::endl;
			}
		}
	}
	return false;
}