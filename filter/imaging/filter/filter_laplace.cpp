#include "filter_laplace.h"

namespace imaging {
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
}