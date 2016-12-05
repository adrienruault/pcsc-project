/*
 * PixelRGB.cpp
 *
 *  Created on: Dec 1, 2016
 *      Author: adrien
 */

#include <iostream>
#include <cassert>

#include "PixelRGB.hpp";



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

/// Overloading the [] operator
/// Potential arguments with their returns: 1 -> Red intensity
///											2 -> Green intensity
/// 										3 -> Blue intensity
double PixelRGB::operator [](int index) const
{
	if (index==1)
	{
		return mRintensity;
	}
	else if (index==2)
	{
		return mGintensity;
	}
	else if (index==3)
	{
		return mBintensity;
	}
	/// Throw an error if index is neither 1, 2 or 3
	assert(0);
	return 0;
}






