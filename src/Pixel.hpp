/*
 * Pixel.hpp
 *
 *  Created on: Nov 30, 2016
 *      Author: adrien
 */

#ifndef SRC_PIXEL_HPP_
#define SRC_PIXEL_HPP_

#include <iostream>

using namespace std;


/// Declaring the base class that contains the information related to a single pixel
/// It has two derived classes that are PixelBW and PixelRGB
class Pixel
{
private:
	/// mformat can be either "undefined", "BW", or "RGB"
	string mformat;

public:
	// Virtual overloading of [] allowing to get the intensity of a pixel
	virtual double operator[] (const int index) const = 0;
};





/* Actually no constructor required since it is a purely abstract class
/// Overriding the default constructor
Pixel::Pixel()
{
	mformat="undefined";
}

/// Overriding the copy constructor
Pixel::Pixel(const Pixel& copiedPixel)
{
	mformat=copiedPixel.mformat;
}
*/




#endif /* SRC_PIXEL_HPP_ */
