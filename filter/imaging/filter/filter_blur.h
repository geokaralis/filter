#ifndef FILTER_BLUR_H
#define FILTER_BLUR_H


#include "filter.h"
#include <cmath>
#include "../../data/array.h"

namespace imaging
{
	class FilterBlur : public Filter, public data::Array<Color>
	{
	protected:
		int N;
		int m, n;
	public:
		FilterBlur(int N) : N(N) { }
		FilterBlur() : Filter() { }
		~FilterBlur() {}

		Image operator << (const Image & image) {
			Image filtered_image = image;

			for (int x = N/2; x < image.getWidth() - N/2; ++x)
			{
				for (int y = N/2; y < image.getHeight() - N/2; ++y)
				{
					Color sum;
					for (int i = -N/2; i < N/2; ++i)
					{
						for (int j = -N/2; j <  N/2; ++j)
						{
							Color c = image.getElement(x + i, y + j);
							Color f = image.getElement(i + N / 2, j + N / 2);
							sum += (c * f);
						}
					}
					//sum /= (1 / std::pow(N, 2));
					filtered_image.setElement(x, y, sum);
				} // Iterate through height
			} // Iterate through width
			return filtered_image;
		}
	};

}

#endif // !FILTER_BLUR_H