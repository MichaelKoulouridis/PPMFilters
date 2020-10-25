#ifndef _FILTER
#define _FILTER

#include "Image.h"

using namespace std;

namespace math {

	
	class Filter {

	public:
		
		
		virtual Image operator << (const Image & image) = 0;

		Filter();

		Filter(Filter & Filter);
	};


}
#endif
