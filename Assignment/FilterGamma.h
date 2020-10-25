#ifndef _FILTERGAMMA
#define _FILTERGAMMA

#include "Image.h"
#include "Filter.h"
#include "Array.h"

using namespace std;

namespace math {

	

	class FilterGamma : public Filter {

	public:
		FilterGamma();

		FilterGamma(float filter);
		
		Image operator << (const Image & image) override;

	private:
		float g;
	};
}
#endif

