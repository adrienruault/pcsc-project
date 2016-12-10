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
protected:
	/// mformat can be either "undefined", "BW", or "RGB"
	string mformat;

public:
	// Virtual overloading of [] allowing to set and get the intensity of a pixel
	// Some care has to be taken when defining default values for purely virtual methods
	virtual double& operator[] (const int channel) = 0;
	virtual const double& operator[] (const int channel) const=0;

	// Declaration of two virtual functions
	// that allow to get and change the pixel intensities
	virtual double GetI(const int channel=1) const = 0;
	virtual void ChangeI(const double new_intensity, const int channel=1) = 0;

	/* Do we need constructors in purely abstract class?
	// Overriding the default constructor
	Pixel()
	{
		mformat="undefined";
	}
	*/
	/*
	// Overriding the copy constructor
	Pixel(const Pixel& copiedPixel)
	{
		mformat=copiedPixel.mformat;
	}
	*/

	// Virtual deconstructor needed for purely abstract class
	virtual ~Pixel() {}
};










#endif /* SRC_PIXEL_HPP_ */
