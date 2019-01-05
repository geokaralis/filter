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
		Image operator<< (const Image & image)
		{
			Image img = image;

			for (unsigned int i = 0; i < image.getWidth(); ++i) {
				for (unsigned int j = 0; j < image.getHeight(); ++j) {
					Color color = img(i, j) * a;
					color = color + c;
					color = color.clampToLowerBound(0.0f);
					color = color.clampToUpperBound(1.0f);
					img.setElement(i, j, color);

				}
			}

			return img;
		}

		FilterLinear() : Filter() { }

		FilterLinear(const Color& a, const Color& c)
			: a(a),
			c(c) { }

		FilterLinear(const Filter &src) : Filter(src) { }
	};

} //namespace imaging

#endif // !FILTER_LINEAR_H