/*
 * Pixel.hpp
 *
 *  Created on: Nov 30, 2016
 *      Author: adrien
 */

#ifndef SRC_PIXEL_HPP_
#define SRC_PIXEL_HPP_

#include <iostream>


/// Declaring the base class that contains the information related to a single pixel
/// It has two derived classes that are PixelBW and PixelRGB
class Pixel
{
protected:
	/// mformat can be either "undefined", "BW", or "RGB"
	int mspectra;

public:
	/// Virtual overloading of [] allowing to set and get the intensity of a pixel
	/// Some care has to be taken when defining default values for purely virtual methods
	virtual double& operator[] (const int channel) = 0;
	virtual const double& operator[] (const int channel) const=0;

	/// Declaration of two virtual functions
	/// that allow to get and change the pixel intensities
	/// Since we have the brackets, these methods are no longer essentials.
	virtual double GetI(const int channel=0) const = 0;
	virtual void ChangeI(const double new_intensity, const int channel=0) = 0;
};










#endif /* SRC_PIXEL_HPP_ */
