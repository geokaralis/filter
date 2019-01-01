#pragma once
#ifndef _FILTERLINEAR
#define _FILTERLINEAR

#include "filter.h"

namespace imaging
{
	class FilterLinear: public Filter
	{
	protected:
		Color a, c;
	public:
		virtual Image operator << (const Image & image)
		{
			for (int x = 0; x < image.getWidth(); x++)
			{
				for (int y = 0; y < image.getHeight(); y++)
				{
					image(x, y);
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