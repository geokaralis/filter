#pragma once

#ifndef _ARRAY
#define _ARRAY


#include <string>
#include <vector>
#include "Vec3.h"

#define Color math::Vec3<float>

namespace math
{
	template<typename T>
	class Array
	{
	protected:
		std::vector<T> buffer;
		unsigned int width, height;

	public:
		const unsigned int getWidth() const { return width; }
		const unsigned int getHeight() const { return height; }

		std::vector<T> getRawDataPtr();

		T getElement(unsigned int x, unsigned int y) const;
		void setElement(unsigned int x, unsigned int y, T & value);

		void setData(const std::vector<T> data_ptr);

		Array();
		Array(unsigned int width, unsigned int height);
		Array(unsigned int width, unsigned int height, const T * data_ptr);
		Array(const Array &src);
		~Array();

		Array<T> & operator = (const Array & right);
		T operator () (unsigned int x, unsigned int y);

	};

} //namespace math

#endif