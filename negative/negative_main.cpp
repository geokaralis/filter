// The application main

#include "negative.h"

#define LOG(x) std::cout << x << std::endl;

int main(int argc, char** argv) {

	std::string image_file = argv[1];

	Image *image = new Image();

	if (image->load(image_file, "ppm")) {

		// img.getWidth() and img.getHeight() are ZERO.
		int w = image->getWidth();
		int h = image->getHeight();

		float *data = ReadPPM(argv[1], &w, &h);

		image = new Image(w,h);
		Color *color = image->getRawDataPtr();

		FillColorFromRawData(color, data, w, h);
		ApplyNegativeFilter(color, w, h);

		if (image->save(image_file, "ppm")) {
			LOG("Image dimensions are: "<< image->getWidth() << " X " << image->getHeight())
						
			WritePPM((float*)color, w, h, argv[1]);
		}
		
	};

	std::cin.get();
	return 0;
}

