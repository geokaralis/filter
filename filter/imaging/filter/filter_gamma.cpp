#include "filter_gamma.h"

namespace imaging {
	FilterGamma::FilterGamma(float gamma) : gamma(gamma) { }
	FilterGamma::FilterGamma() : Filter() { }
	FilterGamma::~FilterGamma() {}

	Image FilterGamma::operator << (const Image & image) {
		Image filtered_image = image;

		for (unsigned int i = 0; i < image.getWidth(); ++i) {
			for (unsigned int j = 0; j < image.getHeight(); ++j) {

				float r = std::pow(filtered_image(i, j).r, gamma);
				float g = std::pow(filtered_image(i, j).g, gamma);
				float b = std::pow(filtered_image(i, j).b, gamma);

				Color color;
				color.r = r;
				color.g = g;
				color.b = b;

				filtered_image.setElement(i, j, color);
			}
		}
		return filtered_image;
	}
}