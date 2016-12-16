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
	/// Contains Red intensity
	double mRintensity;
	/// Contains Green intensity
	double mGintensity;
	/// Contains Blue intensity
	double mBintensity;

public:
	/// Overriding the default constructor
	/// Intensity for the 3 colors are set to 0.0 by default
	PixelRGB();
	PixelRGB(const PixelRGB& copiedPixel);

	/// Overloading of the [] operator to set and get PixelRGB intensities
	/// Potential arguments with their returns: 0 -> Red intensity
	///											1 -> Green intensity
	/// 										2 -> Blue intensityd
	double& operator[] (const int channel);
	const double& operator[] (const int channel) const;

	double GetI(const int channel=0) const
	{return 0;}
	void ChangeI(const double new_intensity, const int channel=0)
	{}
	

};




#endif /* SRC_PIXELRGB_HPP_ */
