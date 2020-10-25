#include "pch.h"
#include "Filter.h"
#include "FilterGamma.h"
#include "Image.h"
#include "Vec3.h"
#include <math.h>

using namespace std;

namespace math {

	FilterGamma::FilterGamma() 
	{
		g = 1.0; 
	}
	
	Image FilterGamma::operator<<(const Image& image)
	{
		Image new_image(image);
		Vec3<float>  temp_element;

		for (int i = 0; i < new_image.getHeight(); i++) 
		{
			for (int j = 0; j < new_image.getWidth(); j++) 
			{
				temp_element = new_image.getElement(j, i);
				
				temp_element.r = pow(temp_element.r, g);
				temp_element.g = pow(temp_element.g, g);
				temp_element.b = pow(temp_element.b, g);
				
				new_image.setElement(j, i, temp_element);
			}
		}
		return new_image;
	}
	
	FilterGamma::FilterGamma(float filter) 
	{
		g = filter;
		
	}


	
}
