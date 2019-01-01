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
	virtual Image operator << (const Image & image)
	{
		for (unsigned int i = 0; i < image.getWidth(); ++i) {
			for (unsigned int j = 0; j < image.getHeight(); ++j) {
				Image img = image;
				img(i,j) = (a * img(i, j)) + c;
				return img;
			}
		}
	}

	FilterLinear(const Color& a, const Color& c) 
		: a(a),
		  c(c) { }

	FilterLinear(const Filter &src) : Filter(src) { }
};

} //namespace imaging

#endif