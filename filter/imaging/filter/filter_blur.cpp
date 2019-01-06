#include "filter_blur.h"

namespace imaging {
	Image FilterBlur::operator<< (const Image & image) {
		Image filtered_image = image;

		for (unsigned int x = 0; x < (image.getWidth()); ++x)
		{
			for (unsigned int y = 0; y < (image.getHeight()); ++y)
			{
				Color sum;
				for (int i = -(N / 2); i < N / 2; ++i)
				{
					for (int j = -(N / 2); j < N / 2; ++j)
					{
						int i_inside_bounds = x + i;
						int j_inside_bounds = y + j;

						// Bounds Checking.
						if (i_inside_bounds < 0) i_inside_bounds = 0;
						if (i_inside_bounds > image.getWidth()) i_inside_bounds = image.getWidth();
						if (j_inside_bounds < 0) j_inside_bounds = 0;
						if (j_inside_bounds > image.getHeight()) j_inside_bounds = image.getHeight();

						Color c = image.getElement(i_inside_bounds, j_inside_bounds);
						float f = kernel[i + N / 2][j + N / 2];
						sum += (c * f);
					}
				}
				filtered_image.setElement(x, y, sum);
			} // Iterate through height
		} // Iterate through width
		return filtered_image;
	}
}

