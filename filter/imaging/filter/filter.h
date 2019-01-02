#pragma once

#ifndef FILTER_H
#define FILTER_H

#include "../image.h"

namespace imaging
{
	class Filter
	{
	protected:

	public:
		Image img;
		virtual Image operator << (const Image & image) = 0;

		Filter() {}

		Filter(const Filter &src)
		{
			img = src.img;
		}
	};

} //namespace imaging

#endif