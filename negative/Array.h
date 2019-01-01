// This class consists of an abstract array definition
// that manipulates data.

#ifndef _ARRAY_H
#define _ARRAY_H


#include <string>
#include <vector>
#include "Vec3.h"

namespace math
{
	template<typename T>
	class Array
	{
	protected:
		std::vector<T> buffer;
		unsigned int width;
		unsigned int height;

	public:
		const unsigned int getWidth() const { return width; }

		const unsigned int getHeight() const { return height; }

		std::vector<T> getRawDataPtr() {
			return buffer;
		}

		T getElement(unsigned int x, unsigned int y) const {
			T element;
			if (x < width && y < height && x >= 0 && y >= 0)
			{
				element = buffer[y*width + x];
			}
			return element;
		}

		void setElement(unsigned int x, unsigned int y, T & value) {
			if (x < width && y < height && x >= 0 && y >= 0)
			{
				buffer[y*width + x] = value;
			}
		}

		void setData(const std::vector<T> data_ptr) {
			buffer = data_ptr;
		}

		Array() {
			this->width = 0;
			this->height = 0;
		}

		Array(unsigned int width, unsigned int height) {
			this->width = width;
			this->height = height;
		}

		Array(unsigned int width, unsigned int height, const std::vector<T> data_ptr) {
			this->width = width;
			this->height = height;
			setData(data_ptr);
		}
		Array(const Array &src) {
			width = src.width;
			height = src.height;
			buffer = src.buffer;
		}

		~Array() {
			buffer.clear();
			buffer.shrink_to_fit();
		}

		Array<T>& operator=(const Array & right) {
			width = right.width;
			height = right.height;
			buffer = right.buffer;
			return *this;
		}

		T operator()(unsigned int x, unsigned int y) {
			T element = getElement(x, y);
			return element;
		}
	};

} //namespace math

#endif