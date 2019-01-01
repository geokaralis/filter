#pragma once
#ifndef _FILTER_LINEAR
#define _FILTER_LINEAR

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

		for (unsigned int i = 0; i < image.getWidth(); ++i) {
			for (unsigned int j = 0; j < image.getHeight(); ++j) {
				Color col = img(i, j) * a;
				col += c;
				col = col.clampToLowerBound(1.0f);
				img.setElement(i, j, col);
			}
		}
		return img;
	}

	FilterLinear(const Color& a, const Color& c) 
		: a(a),
		  c(c) { }

	FilterLinear(const Filter &src) : Filter(src) { }
};

} //namespace imaging

#endif //!_FILTER_LINEAR