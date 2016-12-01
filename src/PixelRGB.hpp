/*
 * PixelRGB.hpp
 *
 *  Created on: Nov 30, 2016
 *      Author: adrien
 */

#ifndef SRC_PIXELRGB_HPP_
#define SRC_PIXELRGB_HPP_

#include "Pixel.hpp"

/// Declaration of the class that represents a tricolor RGB pixel
class PixelRGB : public Pixel
{
private:
	double mRintensity;
	double mGintensity;
	double mBintensity;

public:
	PixelRGB();
	PixelRGB(const PixelRGB& copiedPixel);

	double operator[] (const int index) const;
};


/// Overriding the default constructor
/// Intensity for the 3 colors are set to 0.0 by default
PixelRGB::PixelRGB() : Pixel()
{
	mformat="RGB";

	mRintensity=0.0;
	mGintensity=0.0;
	mBintensity=0.0;
}

/// Overriding the copy constructor
PixelRGB::PixelRGB(const PixelRGB& copiedPixel) : Pixel(copiedPixel)
{
	mRintensity=copiedPixel.mRintensity;
	mGintensity=copiedPixel.mGintensity;
	mBintensity=copiedPixel.mBintensity;
}





#endif /* SRC_PIXELRGB_HPP_ */
