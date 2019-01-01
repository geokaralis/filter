#include "negative.h"

#include "Array.h"

using namespace negative;

Color * negative::FillColorFromRawData(Color * color, float * data, int width, int height)
{
	int p = 0; // Holds the position of the current 
			   // color value within the raw data array.

	// Iterate through the image data and fill r, g, b
	// respectively with data from the 1-dimensional 
	// float array.
	//
	// For each color value move the position by 1
	// i.e. r -> pos(0), g -> pos(1), b -> pos(2)...
	//
	// Then increase the position pointer by 3, since a pixel 
	// consists of three r, g, b values.
	//
	//                             (p = p + 3)
	//                             |
	// Raw data   : [134, 58, 109, 90, 204, 20, ...]
	//               |     |   |
	//               |     |   (p + 2)
	//               (p) (p + 1)
	//
	// Color data : [{134, 58, 109}, {90, 204, 20}, ...]
	for (int i = 0; i < IMAGE_SIZE; i++) {
		color[i].r = data[p];
		color[i].g = data[p + 1];
		color[i].b = data[p + 2];

		p = p + 3;
	}

	return color;
}

std::vector<Color> negative::ApplyNegativeFilter(std::vector<Color> color, int width, int height)
{
	Color* white = new Color(1, 1, 1); // (1, 1, 1) is white since each color channel 
									   // goes from 0.0f (darkness) to 1.0f (full color brightness).

	// Calculate negative using the type:
	// p(x, y) = (1, 1, 1) - p(x, y)
	for (int i = 0; i < IMAGE_SIZE; i++) {
		color[i] = *white - color[i];
	}

	return color;
}

void negative::CreateNegativeImage(std::string filename)
{
	Image *image = new Image();

	Color* a = new Color(1, 1, 1);
	Color* c = new Color(-1, -1, -1);

	if (image->load(filename, "ppm")) {
		
		/*imageData = ApplyNegativeFilter(imageData, image->getWidth(), image->getHeight());*/


		FilterLinear* linear_filter = new FilterLinear(*a, *c);

		*image = *linear_filter << *image;

		std::vector<Color> imageData = image->getRawDataPtr();

		/*math::Array<Color> arr1;
		math::Array<Color> arr2;

		arr1 = arr2;

		arr1(2, 3);*/

		image->setData(imageData);
	}
	else {
		std::cout << "File isn't recognized as a valid ppm image." << std::endl;
		std::cout << "Only .ppm files are accepted." << std::endl;
	}

	if (image->save(filename, "ppm")) {
		LOG("Image dimensions are: " << image->getWidth() << " X " << image->getHeight());
	} else {
		LOG("Could not save image.");
	}
}
