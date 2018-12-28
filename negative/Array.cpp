#include "Array.h"

using namespace math;

template<typename T>
std::vector<T> * Array<T>::getRawDataPtr()
{
	return buffer;
}

template<typename T>
T Array<T>::getElement(unsigned int x, unsigned int y) const
{

	if (x < width && y < height && x >= 0 && y >= 0)
	{

	}
	return T;
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
	setData(data_ptr);
}

template<typename T>
Array<T>::Array(const Array &src)
{
	width = src.width;
	height = src.height;
	buffer(src.buffer);
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
	width = src.width;
	height = src.height;
	buffer(src.buffer);
}

template<typename T>
Array<T> & Array<T>::operator()(unsigned int x, unsigned int y)
{
	Array arr(i, j);
	
	return T;
}
