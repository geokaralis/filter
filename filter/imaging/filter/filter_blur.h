#ifndef FILTER_BLUR_H
#define FILTER_BLUR_H


#include "filter.h"
#include <cmath>
#include "../../data/array.h"

namespace imaging
{
	class FilterBlur : public Filter, public data::Array<Color>
	{
	protected:
		int N;
		int m, n;
		float** kernel;
	public:
		FilterBlur(int N) : N(N) {
			kernel = new float*[N];
			for (int i = 0; i < N; ++i)
				kernel[i] = new float[N];

			for (int i = 0; i < N; ++i) {
				for (int j = 0; j < N; ++j) {
					kernel[i][j] = 1 / (float) pow(N, 2);
				}
			}
			
		}
		FilterBlur() : Filter() { }
		Image operator<< (const Image & image);
	};

} // namespace imaging

#endif // !FILTER_BLUR_H