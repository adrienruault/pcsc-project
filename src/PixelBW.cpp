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



/// Overriding the default constructor
/// Intensity is set to 0.0 by default
// No call for the default constructor of the base class here: Pixel()
// because it seems useless
PixelBW::PixelBW()
{
	mspectra=1;
	mintensity=0.0;
}

/// Overriding the copy constructor
PixelBW::PixelBW(const PixelBW& copiedPixel)
{
	mspectra=copiedPixel.mspectra;
	mintensity=copiedPixel.mintensity;
}

/// Constructs a BW Pixel with intensity specified in argument
PixelBW::PixelBW(const double intensity)
{
	mspectra=1;
	mintensity=intensity;
}

/// Overloading of the [] operator to get and set intensity
/// channel is set to 0 by default which is suitable for monochromatic Pixel.
/// Only channel 0 is accepted: throws an error otherwise.
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

/// Method that allows to get the intensity of a pixel.
/// The argument new intensity is used to provide the new intensity
/// The argument channel is used to indicate which color we want to modify. Here we are
/// in the monochromatic mode so this value has to be unchanged when the function is called
// Be careful: don't put default definition is function declaration but in prototype
double PixelBW::GetI(const int channel /*Set by default to 0*/) const
{
	// Verification that channel is equal to 1
	assert(channel==0);

	return mintensity;
}


/// Method that allows to change the intensity of a pixel.
/// The argument new intensity is used to provide the new intensity.
/// As in the GetI method the channel variable must be let to 1
/// because we only have one color
// Be careful: don't put default definition is function declaration but in prototype
void PixelBW::ChangeI(const double new_intensity, const int channel /*set by default to 0*/)
{
	// Verification that channel is equal to 1
	assert(channel==0);

	mintensity=new_intensity;
}

// Overloading the = (assignment) operator
PixelBW& PixelBW::operator=(const PixelBW& pix)
{
   mintensity = pix.mintensity;
   return *this;
}
