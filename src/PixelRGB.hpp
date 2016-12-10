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

	/// Overloading of operator [] to get and set PixelRGB intensities
	// For default values see: http://stackoverflow.com/questions/12139786/good-pratice-default-arguments-for-pure-virtual-method
	double& operator[] (const int channel);
	const double& operator[] (const int channel) const;

	double GetI(const int channel=0) const
	{return 0;}
	void ChangeI(const double new_intensity, const int channel=0)
	{}

};




#endif /* SRC_PIXELRGB_HPP_ */
