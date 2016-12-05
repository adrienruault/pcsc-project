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




#endif /* SRC_PIXELRGB_HPP_ */
