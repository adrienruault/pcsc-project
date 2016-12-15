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
private:
	double mintensity;

public:
	PixelBW();
	PixelBW(const PixelBW& copiedPixel);
	PixelBW& operator=(const PixelBW& pix);
	/// Construct Black and White Pixel with specified intensity
	PixelBW(const double intensity);

	/// Overloading of operator [] to get and set PixelBW intensity
	// For default values see: http://stackoverflow.com/questions/12139786/good-pratice-default-arguments-for-pure-virtual-method
	double& operator[] (const int channel);
	const double& operator[] (const int channel) const;

	// Declaration of two functions that allow to get and change the pixel intensities
	double GetI(const int channel=0) const;
	void ChangeI(const double new_intensity, const int channel=0);
};




#endif /* SRC_PIXELBW_HPP_ */
