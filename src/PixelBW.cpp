/*
 * PixelBW.cpp
 *
 *  Created on: Dec 1, 2016
 *      Author: adrien
 */

#include <cassert>
#include <iostream>

#include "PixelBW.hpp"

using namespace std;


/// Overriding the default constructor
/// Intensity is set to 0.0 by default
// No call for the default constructor of the base class here: Pixel()
// because it seems useless
PixelBW::PixelBW()
{
	mformat="BW";
	mintensity=0.0;
}

/// Overriding the copy constructor
PixelBW::PixelBW(const PixelBW& copiedPixel)
{
	mformat=copiedPixel.mformat;
	mintensity=copiedPixel.mintensity;
}

/// Constructs a BW Pixel with intensity specified in argument
PixelBW::PixelBW(const double intensity)
{
	mformat="BW";
	mintensity=intensity;
}

/// Overloading of the [] operator
/// If 1 is used as argument the intensity of the pixel is returned, otherwise it
/// throws an error. Only 1 is accepted because we are in the monochromatic mode.
double PixelBW::operator[] (int index) const
{
	assert(index==0);
	return mintensity;
}

/// Method that allows to get the intensity of a pixel.
/// The argument new intensity is used to provide the new intensity
/// The argument channel is used to indicate which color we want to modify. Here we are
/// in the monochromatic mode so this value has to be unchanged when the function is called
// Be careful: don't put default definition is function declaration but in prototype
double PixelBW::GetI(const int channel /*Set by default to 1*/) const
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
void PixelBW::ChangeI(const double new_intensity, const int channel /*set by default to 1*/)
{
	// Verification that channel is equal to 1
	assert(channel==0);

	mintensity=new_intensity;
}







