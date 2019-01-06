#ifndef FILTER_GAMMA_H
#define FILTER_GAMMA_H

#include <cmath>
#include "filter.h"

namespace imaging
{
	class FilterGamma : public Filter
	{
	public:
		FilterGamma(float gamma);
		FilterGamma();
		~FilterGamma();

		Image operator << (const Image & image);
	protected:
		float gamma;

	};
}
#endif // !FILTER_GAMMA_H

