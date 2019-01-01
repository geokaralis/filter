#pragma once
#ifndef _FILTERLINEAR
#define _FILTERLINEAR

#include "filter.h"

#include "Array.h"

namespace imaging
{
	class FilterLinear: public Filter
	{
	protected:
		Color a, c;
	public:
		virtual Image operator << (const Image & image)
		{
			for (unsigned int i = 0; i < image.getWidth(); ++i)
			{
				for (unsigned int j = 0; j < image.getHeight(); ++j)
				{
					Image img;
					

					img = image;

					img(i,j);
				}
			}
		}

		FilterLinear(Color &a, Color &c) 
		{ 
			this->a = a;
			this->c = c;
		}

		FilterLinear(const Filter &src) : Filter(src) {}
	};

} //namespace imaging

#endif