#include "ppm.h"

#include <iostream>
#include <sstream>
#include <fstream>

float * imaging::ReadPPM(const char * filename, int * w, int * h) {
	int width;
	int height;

	unsigned int color_intensity;

	std::ifstream file_stream;
	std::string format;

	file_stream.open(filename, std::ios::binary);

	if (!file_stream.is_open()) throw("Cannot open file");

	file_stream >> format 
		>> width 
		>> height 
		>> color_intensity;

	int size = 3 * width * height; // Size of float array 3 X w X h 3 rgb values

	unsigned char* buffer = new unsigned char[size];

	if (format.compare("P6") != 0) throw("Cannot read file. Must be P6");
	if (color_intensity > 255) throw("Cannot read file. Color intensity must be up to 255");
	
	file_stream.read((char*)buffer, size);

	for (int i = 0; i < 10; i++)
	{
		std::cout << (float)buffer[i] << std::endl;
	}


	file_stream.close();

	std::cout << "the entire file content is in memory \n";

	float* floatArray = new float[size];
	for (int i = 0; i < 10; ++i) {
		floatArray[i] = (double)buffer[i];

		std::cout << "Float: " << floatArray[i] << std::endl;
	}

	return floatArray;
	//return nullptr;

}

bool imaging::WritePPM(const float * data, int w, int h, const char * filename)
{
	return false;
}