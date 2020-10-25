#ifndef _IMAGE
#define _IMAGE

#include "pch.h"
#include <iostream>
#include <string>
#include "Vec3.h"
#include "Array.h"
#include "../ppm/ppm.h"


using namespace std;

namespace math {
	
	
	class Image : public Array<Vec3<float>> {

	public:

		// metric accessors

		/*! Returns the width of the image
		 */
		const unsigned int getWidth() const { return Array<Vec3<float>>::width; }

		/*! Returns the height of the image
		 */
		const unsigned int getHeight() const { return Array<Vec3<float>>::height; }

		// data accessors

		

		// constructors and destructor

		/*! Default constructor.
		 *
		 * By default, the dimensions of the image should be zero and the buffer must be set to nullptr.
		 */
		Image();

		/*! Constructor with width and height specification.
		 *
		 * \param width is the desired width of the new image.
		 * \param height is the desired height of the new image.
		 */
		Image(unsigned int width, unsigned int height);

		/*! Constructor with data initialization.
		 *
		 * \param width is the desired width of the new image.
		 * \param height is the desired height of the new image.
		 * \param data_ptr is the source of the data to copy to the internal image buffer.
		 *
		 * \see setData
		 */
		Image(unsigned int width, unsigned int height, const Vec3<float> * data_ptr);

		/*! Copy constructor.
		 *
		 * \param src is the source image to replicate in this object.
		 */
		Image(const Image &src);

		/*! The Image destructor.
		 */
		~Image();
		/*!
		 * Loads the image data from the specified file, if the extension of the filename matches the format string.
		 *
		 * Only the "ppm" extension is supported for now. The extension comparison should be case-insensitive. If the
		 * Image object is initialized, its contents are wiped out before initializing it to the width, height and data
		 * read from the file.
		 *
		 * \param filename is the string of the file to read the image data from.
		 * \param format specifies the file format according to which the image data should be decoded from the file.
		 * Only the "ppm" format is a valid format string for now.
		 *
		 * \return true if the loading completes successfully, false otherwise.
		 */
		bool load(const std::string & filename, const std::string & format);

		/*!
		* Stores the image data to the specified file, if the extension of the filename matches the format string.
		*
		* Only the "ppm" extension is supported for now. The extension comparison should be case-insensitive. If the
		* Image object is not initialized, the method should return immediately with a false return value.
		*
		* \param filename is the string of the file to write the image data to.
		* \param format specifies the file format according to which the image data should be encoded to the file.
		* Only the "ppm" format is a valid format string for now.
		*
		* \return true if the save operation completes successfully, false otherwise.
		*/
		bool save(const std::string & filename, const std::string & format);
	};
	

	
	inline Image::Image() : Array<Vec3<float>>::Array() {}

	
	inline Image::Image(unsigned int width, unsigned int height) : Array<Vec3<float>>::Array(width,height) {}

	
	inline Image::Image(unsigned int width, unsigned int height, const Vec3<float> * data_ptr) : Array<Vec3<float>>::Array(width,height,data_ptr) {}

	
	inline Image::Image(const Image & src): Array<Vec3<float>>::Array(src) {}

	
	inline Image::~Image() {}

	
	inline bool Image::load(const std::string & filename, const std::string & format)
	{
		if (filename.substr(filename.find_last_of(".") + 1) != format) {
			cout << "Wrong format!" << endl;
			return false;
		}
		else {
			int w;
			int h;
			float * _buffer;
			_buffer = ReadPPM(filename.c_str(), &w, &h);
			Array<Vec3<float>>::width = w;
			Array<Vec3<float>>::height = h;
			int size = Array<Vec3<float>>::width * Array<Vec3<float>>::height;
			Array<Vec3<float>>::buffer.resize(size);
			
			for (int i = 0; i < size; i++) {

				for (int j = 0; j < 3; j++) {

					Array<Vec3<float>>::buffer[i][j] = _buffer[3 * i + j];

				}
			}

			cout << "Image successfully loaded!" << endl;

			delete[] _buffer;

		}
		return true;
	}

	
	inline bool Image::save(const std::string & filename, const std::string & format)
	{
		if (filename.substr(filename.find_last_of(".") + 1) != format) {
			cerr << "Wrong format!" << endl;
			return false;
		}
		else if (Array<Vec3<float>>::buffer.empty()) {
			cerr << "Image object is not initialized" << endl;
			return false;
		}
		else {
			
			string new_filename = filename;
			new_filename.insert(0, "filtered_");

			float * data = new float[3 * Array<Vec3<float>>::width * Array<Vec3<float>>::height];

			for (int i = 0; i < Array<Vec3<float>>::width * Array<Vec3<float>>::height; i++) {
				for (int j = 0; j < 3; j++) {

					data[3 * i + j] = Array<Vec3<float>>::buffer[i][j];

				}
			}
			if (WritePPM(data, Array<Vec3<float>>::width, Array<Vec3<float>>::height, new_filename.c_str())) {
				cout << "Image successfully written!" << endl;
				return true;
			}
			else {
				return false;
			}
		}
	}
}
#endif