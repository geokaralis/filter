#include "Array.h"

using namespace math;

template<typename T>
std::vector<T> Array<T>::getRawDataPtr()
{
	return buffer;
}

template<typename T>
T Array<T>::getElement(unsigned int x, unsigned int y) const
{
	T element;
	if (x < width && y < height && x >= 0 && y >= 0)
	{
		element = buffer[x*width + y];
	}
	return element;
}

template<typename T>
void Array<T>::setElement(unsigned int x, unsigned int y, T & value)
{
	if (x < width && y < height && x >= 0 && y >= 0)
	{
		buffer[x*width + y] = value;
	}
}

template<typename T>
void Array<T>::setData(const std::vector<T> data_ptr)
{

	buffer = data_ptr;
}

template<typename T>
Array<T>::Array()
{
	this->width = 0;
	this->height = 0;
}

template<typename T>
Array<T>::Array(unsigned int width, unsigned int height)
{
	this->width = width;
	this->height = height;
}

template<typename T>
Array<T>::Array(unsigned int width, unsigned int height, const T * data_ptr)
{
	this->width = width;
	this->height = height;
	//setData(data_ptr);
}

template<typename T>
Array<T>::Array(const Array &src)
{
	width = src.width;
	height = src.height;
	buffer = src.buffer;
}

template<typename T>
Array<T>::~Array()
{
	buffer.clear();
	buffer.shrink_to_fit();
}

template<typename T>
Array<T> & Array<T>::operator = (const Array & right)
{
	width = right.width;
	height = right.height;
	buffer = right.buffer;
	return *this;
}

template<typename T>
T Array<T>::operator()(unsigned int x, unsigned int y)
{
	return this->getElement(x, y);
}

template class Array<Color>;