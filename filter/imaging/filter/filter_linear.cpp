#include "filter_linear.h"

namespace imaging {
	Image FilterLinear::operator<< (const Image & image)
	{
		Image img = image;

		for (unsigned int i = 0; i < image.getWidth(); ++i) {
			for (unsigned int j = 0; j < image.getHeight(); ++j) {
				Color color = img(i, j) * a;
				color = color + c;
				color = color.clampToLowerBound(0.0f);
				color = color.clampToUpperBound(1.0f);
				img.setElement(i, j, color);
			}
		}

		return img;
	}

	FilterLinear::FilterLinear(const Color& a, const Color& c)
		: a(a),
		c(c) { }

	FilterLinear::FilterLinear(const Filter &src) : Filter(src) { }

	FilterLinear::FilterLinear() : Filter() { }
}