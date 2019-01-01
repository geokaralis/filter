#pragma once

#ifndef FILTER_GAMMA_H
#define FILTER_GAMMA_H

#include <cmath>
#include "filter.h"

namespace imaging 
{
	class FilterGamma : public Filter
	{
	protected:
		 float gamma;
	public:
		Image operator << (const Image & image) {
			Image filtered_image = image;

			for (unsigned int i = 0; i < image.getWidth(); ++i) {
				for (unsigned int j = 0; j < image.getHeight(); ++j) {

					float r = std::pow(filtered_image(i, j).r, gamma);
					float g = std::pow(filtered_image(i, j).g, gamma);
					float b = std::pow(filtered_image(i, j).b, gamma);

					

					Color col;
					col.r = r;
					col.g = g;
					col.b = b;

					filtered_image.setElement(i, j, col);
				}
			}
			return filtered_image;
		}

		FilterGamma(float &gamma) 
			: gamma(gamma) {}

		~FilterGamma() {}
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
} // namespace imaging
#endif // !FILTER_GAMMA_H
