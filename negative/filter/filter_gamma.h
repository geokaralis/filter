#pragma once

#ifndef FILTER_GAMMA_H
#define FILTER_GAMMA_H

#include <cmath>
#include "filter.h"

namespace imaging 
{
	class FilterGamma : public Filter
	{
	public:
		FilterGamma(){}
		~FilterGamma(){}
		Image operator << (const Image & image) {
			Image filtered_image = image;
			std::cout << "[DEBUG][FilterGamma]: Red pixel before gamma: " << filtered_image.getElement(0, 0).r << std::endl;

			for (unsigned int i = 0; i < image.getWidth(); ++i) {
				for (unsigned int j = 0; j < image.getHeight(); ++j) {

					int r = std::pow(filtered_image(i, j).r, 0.2);
					int g = std::pow(filtered_image(i, j).g, 0.2);
					int b = std::pow(filtered_image(i, j).b, 0.2);

					

					Color col;
					col.r = r;
					col.g = g;
					col.b = b;

					filtered_image.setElement(i, j, col);
				}
			}

			std::cout << "[DEBUG][FilterGamma]: Red pixel after gamma: " << filtered_image.getElement(0, 0).r << std::endl;
			return filtered_image;
		}
	private:


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
