/*
 * PixelBW.hpp
 *
 *  Created on: Nov 30, 2016
 *      Author: adrien
 */

#ifndef SRC_PIXELBW_HPP_
#define SRC_PIXELBW_HPP_

#include "Pixel.hpp"

/// Declaration of class that represents a monocolor black and white pixel
// It might be useful to think about the implementation of a template to allow more
// flexibility with the type in which is expressed the intensity. Actually it might be
// useless in the sense that we are going to call CImg ourselves and thus we will be
// able to control the type used.
class PixelBW: public Pixel
{
protected:
	double mintensity;

public:
	PixelBW();
	PixelBW(const PixelBW& copiedPixel);
	/// Construct Black and White Pixel with specified intensity
	PixelBW(const double intensity);

	double operator[] (const int index) const;

	// Declaration of two functions that allow to get and change the pixel intensities
	double GetI(const int channel=1) const;
	void ChangeI(const double new_intensity, const int channel=1);
};




#endif /* SRC_PIXELBW_HPP_ */
