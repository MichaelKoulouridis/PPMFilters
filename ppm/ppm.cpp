#include "ppm.h"
#include <fstream>
#include <iostream>
#include <string>


using namespace std;

namespace math
{ 
	float * ReadPPM(const char * filename, int * w, int * h)
	{
		char next_element;
		string header;
		int color_range;
		float * image;
		ifstream file(filename, ios::binary);

		if (file.is_open()) {
			file >> header >> *w >> *h >> color_range;
			if (header != "P6") {
				cerr << "Wrong format of an image" << endl;
				
			}
			else if (color_range > 255 || color_range < 0) {
				cerr << "Error with color range" << endl;
			}
			else {

				cout << "Image dimensions are: " << *w << " , " << *h << endl;

				int size = 3 * (*w) * (*h);

				image = new float[size];

				file.get(next_element);

				for (int i = 0; i < size; i++) {

					file.get(next_element);
					image[i] = (unsigned char)next_element / (float)color_range;

				}
				return image;
			}
		}
		else {
			cerr << "File could not be opened " << endl;
		}


		file.close();

	}


	bool WritePPM(const float * data, int w, int h, const char * filename)
	{
		char next_element;
		ofstream file(filename, ios::binary);
		if (data == nullptr) {
			return false;
		}
		else {
			if (file.is_open()) {

				string text = "P6\n" + to_string(w) + '\n' + to_string(h) + '\n' + to_string(255) + '\n';
				file.write(text.c_str(), text.size());

				int size = 3 * w * h;
				char * temp_data = new char[size];
				for (int i = 0; i < size; i++) {
					temp_data[i] = data[i] * 255;
				}
				file.write(temp_data, size);
				file.flush();
				file.close();
			}
		}
		return true;
	}
}



