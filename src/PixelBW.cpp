/*
 * PixelBW.cpp
 *
 *  Created on: Dec 1, 2016
 *      Author: adrien
 */

#include <cassert>
#include <iostream>
#include <exception>

#include "PixelBW.hpp"
#include "Error.hpp"




PixelBW::PixelBW()
{
	mspectra=1;
	mintensity=0.0;
}


PixelBW::PixelBW(const PixelBW& copiedPixel)
{
	mspectra=copiedPixel.mspectra;
	mintensity=copiedPixel.mintensity;
}


PixelBW::PixelBW(const double intensity)
{
	mspectra=1;
	mintensity=intensity;
}


double& PixelBW::operator[] (const int channel /*=0*/)
{
	if (channel!=0)
	{
		throw ErrorChannel(mspectra);
	}
	return mintensity;
}

const double& PixelBW::operator[] (const int channel /*=0*/) const
{
	if (channel!=0)
	{
		throw ErrorChannel(mspectra);

	}
	return mintensity;
}


double PixelBW::GetI(const int channel /*Set by default to 0*/) const
{
	// Verification that channel is equal to 1
	assert(channel==0);

	return mintensity;
}



void PixelBW::ChangeI(const double new_intensity, const int channel /*set by default to 0*/)
{
	// Verification that channel is equal to 1
	assert(channel==0);

	mintensity=new_intensity;
}
