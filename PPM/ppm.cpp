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

	file_stream.open(filename, std::ios_base::binary);

	if (!file_stream.is_open()) throw("Cannot open file");

	file_stream >> format 
		>> width 
		>> height 
		>> color_intensity;

	*w = width;
	*h = height;

	int size = 3 * width * height; // Size of float array 3 X w X h 3 rgb values

	//unsigned char* buffer = new unsigned char[size];

	float* floatArray = new float[size/sizeof(float)];


	if (format.compare("P6") != 0) throw("Cannot read file. Must be P6");
	if (color_intensity > 255) throw("Cannot read file. Color intensity must be up to 255");
	
	file_stream.read(reinterpret_cast<char *>(floatArray), size);

	/*for (int i = 0; i < 10; i++)
	{
		std::cout << (float)buffer[i] << std::endl;
	}*/


	file_stream.close();

	std::cout << "the entire file content is in memory \n";

	/*float* floatArray = new float[size];
	for (int i = 0; i < size; i++) {
		floatArray[i] = (char)buffer[i];
	}*/

	return floatArray;
}

bool imaging::WritePPM(const float * data, int w, int h, const char * filename)
{
	try
	{
		// Setting up the header of PPM file. 
		std::ofstream file_stream(filename, std::ios_base::binary);
		file_stream << "P6\n";
		file_stream << w << "\n";
		file_stream << h << "\n";
		file_stream << "255\n";

		// Write buffer data to the given file.
		file_stream.write((char*)(data), w * h * 3);
		file_stream.close();

		return true;
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	return false;
}