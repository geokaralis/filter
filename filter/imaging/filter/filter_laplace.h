#ifndef FILTER_LAPLACE_H
#define FILTER_LAPLACE_H


#include "filter_blur.h"
#include <cmath>
#include "../../data/array.h"

namespace imaging
{
	class FilterLaplace : public FilterBlur
	{
	protected:
		int kernel[3][3] = {
			{0, 1, 0},
			{1, -4 , 1},
			{0, 1, 0}
		};
	public:
		Image operator << (const Image & image);
	};


	Image FilterLaplace::operator<< (const Image & image) {
		Image filtered_image = image;

		for (unsigned int x = 0; x < (image.getWidth()); ++x)
		{
			for (unsigned int y = 0; y < (image.getHeight()); ++y)
			{
				Color sum, result;
				for (int i = -1; i <= 1; ++i)
				{
					for (int j = -1; j <= 1; ++j)
					{
						Color c = image.getElement(x + i, y + j);
						int f = kernel[i + 1][j + 1];
						sum += (c * f);
					}
					// max{result, 1}
					result = sum.clampToUpperBound(1.0f);
				}
				// min{result, 0}
				result = result.clampToLowerBound(0.0f);
				filtered_image.setElement(x, y, sum);
			} // Iterate through height
		} // Iterate through width
		return filtered_image;
	}

} // namespace imaging

#endif // !FILTER_LAPLACE_H
