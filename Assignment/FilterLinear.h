#ifndef _FILTERLINEAR
#define _FILTERLINEAR

#include "Image.h"
#include "Filter.h"
#include "Array.h"

using namespace std;

namespace math {

	

	class FilterLinear : public Filter {

	public:
		FilterLinear();

		FilterLinear(Vec3<float> a, Vec3<float> c);

		Image operator << (const Image & image) override;

	private:
		Vec3<float> a;
		Vec3<float> c;
	};
}
#endif

