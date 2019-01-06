#ifndef FILTER_LINEAR_H
#define FILTER_LINEAR_H

#include "filter.h"

namespace imaging
{
	class FilterLinear : public Filter
	{
	protected:
		Color a;
		Color c;
	public:
		Image operator<< (const Image & image);

		FilterLinear();
		FilterLinear(const Color& a, const Color& c);
		FilterLinear(const Filter &src);
	};

} //namespace imaging

#endif // !FILTER_LINEAR_H