/*
 * PixelRGB.cpp
 *
 *  Created on: Dec 1, 2016
 *      Author: adrien
 */

#include <iostream>
#include <cassert>

#include "PixelRGB.hpp"
#include "Error.hpp"



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

/// Overloading of the [] operator to set and get PixelRGB intensities
/// Potential arguments with their returns: 0 -> Red intensity
///											1 -> Green intensity
/// 										2 -> Blue intensity
double& PixelRGB::operator[](const int channel)
{
	if (channel==0)
	{
		return mRintensity;
	}
	else if (channel==1)
	{
		return mGintensity;
	}
	else if (channel==2)
	{
		return mBintensity;
	}
	/// Throw an error if index is neither 1, 2 or 3
	else
	{
		throw ErrorChannel(mformat);
	}
}

const double& PixelRGB::operator[](const int channel) const
{
	if (channel==0)
	{
		return mRintensity;
	}
	else if (channel==1)
	{
		return mGintensity;
	}
	else if (channel==2)
	{
		return mBintensity;
	}
	else
	{
		throw ErrorChannel(mformat);
	}
}






