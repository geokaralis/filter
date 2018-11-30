// The application main

#include "negative.h"

#define LOG(x) std::cout << x << std::endl;

int main(int argc, char** argv) {

	std::string image_file = "../data/img_01.ppm";

	Image *image = new Image();

	if (image->load(image_file, "ppm")) {
		// img.getWidth() and img.getHeight() are ZERO.
		int w = image->getWidth();
		int h = image->getHeight();

		float *data = ReadPPM("../data/img_01.ppm", &w, &h);

		image = new Image(w,h);
		Color *color = image->getRawDataPtr();

		FillColorFromRawData(color, data, w, h);
		ApplyNegativeFilter(color, w, h);

		if (image->save(image_file, "ppm")) {
			WritePPM((float*)color, w, h, "../data/_neg_img_01.ppm");
		}
		
	};

	/*std::string input;
	PromptUser(argc, input);*/

	LOG("Press any button to exit...");
	std::cin.get();
	return 0;
}

