#ifndef FILTER_GAMMA_H
#define FILTER_GAMMA_H

#include <cmath>
#include <iostream>
#include "filter.h"

namespace imaging
{
	class FilterGamma : public Filter
	{
	public:
		FilterGamma(float gamma) : gamma(gamma) { }
		FilterGamma() : Filter() { }
		~FilterGamma() {}
		Image operator << (const Image & image) {
			Image filtered_image = image;

			for (unsigned int i = 0; i < image.getWidth(); ++i) {
				for (unsigned int j = 0; j < image.getHeight(); ++j) {

					float r = std::pow(filtered_image(i, j).r, gamma);
					float g = std::pow(filtered_image(i, j).g, gamma);
					float b = std::pow(filtered_image(i, j).b, gamma);

					Color color;
					color.r = r;
					color.g = g;
					color.b = b;

					filtered_image.setElement(i, j, color);
				}
			}
			return filtered_image;
		}
	protected:
		float gamma;

	};

	//FilterGamma::FilterGamma()
	//{
	//}

	//FilterGamma::~FilterGamma()
	//{
	//}

	/*inline Image FilterGamma::operator<<(const Image & image)
	{
		Image filtered_image = image;
		for (unsigned int i = 0; i < image.getWidth(); ++i) {
			for (unsigned int j = 0; j < image.getHeight(); ++j) {
				std::pow(filtered_image(i, j).r, 0.2);
				std::pow(filtered_image(i, j).g, 0.2);
				std::pow(filtered_image(i, j).b, 0.2);

				Color col = filtered_image(i, j);
				filtered_image.setElement(i, j, col);
			}
		}
		return filtered_image;
	}*/
}
#endif // !FILTER_GAMMA_H

