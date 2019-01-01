#pragma once
#ifndef _FILTERLINEAR
#define _FILTERLINEAR

#include "filter.h"

namespace imaging
{
class FilterLinear: public Filter
{
protected:
	Color a;
	Color c;
public:
	Image operator << (const Image & image)
	{
		Image img = image;

		std::cout << "[DEBUG][FilterLinear]: Red value copied from source image: " << img.getElement(0,0).r << std::endl;

		for (unsigned int i = 0; i < image.getWidth(); ++i) {
			for (unsigned int j = 0; j < image.getHeight(); ++j) {
				Color col = img(i, j) * a;
				col = col + c;
				img.setElement(i, j, col);
			}
		}

		std::cout << "[DEBUG][FilterLinear]: Red value: " << img.getElement(0, 0).r << std::endl;


		return img;
	}

	FilterLinear(const Color& a, const Color& c) 
		: a(a),
		  c(c) { }

	FilterLinear(const Filter &src) : Filter(src) { }
};

} //namespace imaging

#endif