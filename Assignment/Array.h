//------------------------------------------------------------
//
// C++ course assignment code 
//
// G. Papaioannou, 2017 - 2018
//
//


#ifndef _ARRAY
#define _ARRAY

#include "pch.h"
#include <string>
#include <vector>


/*! The imaging namespace contains every class or function associated with the image storage, compression and manipulation.
 */

using namespace std;

namespace math
{

	//------------------------------------ class Image ------------------------------------------------

		/*! It is the class that represents a generic data container for an image.
		 *
		 * It holds the actual buffer of the pixel values and provides methods for accessing them,
		 * either as individual pixels or as a memory block. The Image class alone does not provide
		 * any functionality for loading and storing an image, as it is the result or input to such a procedure.
		 *
		 * The internal buffer of an image object stores the actual bytes (data) of the color image as
		 * a contiguous sequence of Color structures. Hence, the size of the buffer variable holding these data is
		 * width X height X sizeof(Color) bytes.
		 *
		 * All values stored in the Color data type components are assumed to be floating point values and for typical (normalized)
		 * intensity ranges, each color component is within the range [0.0, 1.0].
		 */

	template <typename T>

	class Array
	{

	protected:
		vector<T> buffer;                              //! Holds the image data.
		
		unsigned int width, 						 //! The width of the image (in pixels)
			height;		                 //! The height of the image (in pixels)

	public:
		// metric accessors

		/*! Returns the width of the image
		 */
		const unsigned int getWidth() const { return width; }

		/*! Returns the height of the image
		 */
		const unsigned int getHeight() const { return height; }

		// data accessors

		/*! Obtains a pointer to the internal data.
		 *
		 *  This is NOT a copy of the internal image data, but rather a pointer
		 *  to the internally allocated space, so DO NOT attempt to delete the pointer.
		 */
		vector<T> getRawDataPtr();

		/*! Obtains the color of the image at location (x,y).
		 *
		 *  The method should do any necessary bounds checking.
		 *
		 *  \param x is the (zero-based) horizontal index of the pixel to get.
		 *  \param y is the (zero-based) vertical index of the pixel to get.
		 *
		 *  \return The color of the (x,y) pixel as a Color object. Returns a black (0,0,0) color in case of an out-of-bounds x,y pair.
		 */
		T getElement(unsigned int x, unsigned int y) const;

		// data mutators

		/*! Sets the RGB values for an (x,y) pixel.
		 *
		 *  The method should perform any necessary bounds checking.
		 *
		 *  \param x is the (zero-based) horizontal index of the pixel to set.
		 *  \param y is the (zero-based) vertical index of the pixel to set.
		 *  \param value is the new color for the (x,y) pixel.
		 */
		void setElement(unsigned int x, unsigned int y, T & value);

		/*! Copies the image data from an external raw buffer to the internal image buffer.
		 *
		 *  The member function ASSUMES that the input buffer is of a size compatible with the internal storage of the
		 *  Image object and that the data buffer has been already allocated. If the image buffer is not allocated or the
		 *  width or height of the image are 0, the method should exit immediately.
		 *
		 *  \param data_ptr is the reference to the preallocated buffer from where to copy the data to the Image object.
		 */
		void setData(const T * & data_ptr);

		// constructors and destructor

		/*! Default constructor.
		 *
		 * By default, the dimensions of the image should be zero and the buffer must be set to nullptr.
		 */
		Array();

		/*! Constructor with width and height specification.
		 *
		 * \param width is the desired width of the new image.
		 * \param height is the desired height of the new image.
		 */
		Array(unsigned int width, unsigned int height);

		/*! Constructor with data initialization.
		 *
		 * \param width is the desired width of the new image.
		 * \param height is the desired height of the new image.
		 * \param data_ptr is the source of the data to copy to the internal image buffer.
		 *
		 * \see setData
		 */
		Array(unsigned int width, unsigned int height, const T * data_ptr);

		/*! Copy constructor.
		 *
		 * \param src is the source image to replicate in this object.
		 */
		Array(const Array &src);

		/*! The Image destructor.
		 */
		~Array();

		/*! Copy assignment operator.
		 *
		 * \param right is the source image.
		 */
		Array & operator = (const Array & right);

		T & operator () (Array arr, int i , int j);

	};

	

	

	template<typename T>
	inline vector<T> Array<T>::getRawDataPtr()
	{
		return this->buffer;
	}

	template<typename T>
	inline T Array<T>::getElement(unsigned int x, unsigned int y) const
	{
		T element;
		
		if (x < getWidth() && y < getHeight()) {
		
			element = buffer.at(y * getWidth() + x);
			
			return element;
		}
		else {
			cout << x << " , " << y << '\n';
			cerr << "Pixel out of bounds while getting the element" << endl;
			return element;
		}
	}

	template<typename T>
	inline void Array<T>::setElement(unsigned int x, unsigned int y, T & value)
	{
		if (x < getWidth() && y < getHeight()) {
			
			buffer.at(y * getWidth() + x) = value;
			
		}
		else {

			cerr << "Pixel out of bounds while setting the element" << endl;
		}
	}

	template<typename T>
	inline void Array<T>::setData(const T *& data_ptr)
	{
		if (buffer.empty()) {
			return;
		}
		for (int i = 0; i <= getWidth() * getHeight(); i++) {
			buffer.at(i) = data_ptr[i];
		}
	}

	template<typename T>
	inline Array<T>::Array()
	{
		width = 0;
		height = 0;
		buffer.resize(0);
	}

	template<typename T>
	inline Array<T>::Array(unsigned int width, unsigned int height)
	{
		this->width = width;
		this->height = height;
		buffer.resize(width * height);
	}

	template<typename T>
	inline Array<T>::Array(unsigned int width, unsigned int height, const T * data_ptr)
	{
		this->width = width;
		this->height = height;
		buffer.resize(this->width * this->height);
		setData(data_ptr);
	}

	template<typename T>
	inline Array<T>::Array(const Array & src)
	{
		width = src.getWidth();
		height = src.getHeight();
		buffer.resize(width * height);
		for (int i = 0; i < width*height; i++) {
			buffer[i] = src.buffer[i];
		}
	}

	template<typename T>
	inline Array<T>::~Array()
	{
		if (!buffer.empty()) {
			buffer.clear();
		}
	}

	template <typename T>
	inline Array<T> & Array<T>::operator=(const Array & right)
	{
		width = right.getWidth();
		height = right.getHeight();
		buffer.resize(width * height);
		for (int i = 0; i < width*height; i++) {
			buffer[i] = right.buffer[i];
		}

		return *this;
	}

	template<typename T>
	inline T & Array<T>::operator()(Array arr, int i, int j)
	{
		
		return arr.buffer.at(j, i);
	}

	

} 

#endif