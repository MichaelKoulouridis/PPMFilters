#include "pch.h"
#include "FilterLinear.h"
#include "Image.h"
#include <algorithm>

using namespace std;
namespace math {

	FilterLinear::FilterLinear()
	{
	}

	FilterLinear::FilterLinear(Vec3<float> a, Vec3<float> c)
	{
		this->a = a;
		this->c = c;
	}

	Image math::FilterLinear::operator<<(const Image & image)
	{
		Image new_image(image);
		Vec3<float>  temp_element;

		
		for (int i = 0; i < new_image.getHeight(); i++)
		{
			for (int j = 0; j < new_image.getWidth(); j++)
			{
				temp_element = new_image.getElement(j, i);

				temp_element.r = min(temp_element.r * a[0] + c[0], 1.0f);
				temp_element.g = min(temp_element.g * a[1] + c[1], 1.0f);
				temp_element.b = min(temp_element.b * a[2] + c[2], 1.0f);

				if (temp_element.r > 1) {
					temp_element.r = 1;
				}
				if (temp_element.g > 1) {
					temp_element.g = 1;
				}
				if (temp_element.b > 1) {
					temp_element.b = 1;
				}
				new_image.setElement(j, i, temp_element);
			}
		}
		return new_image;
	}

}
