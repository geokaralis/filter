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

} // namespace imaging

#endif // !FILTER_LAPLACE_H
