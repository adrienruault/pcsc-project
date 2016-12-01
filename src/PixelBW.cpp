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
PixelBW::PixelBW() : Pixel()
{
	mformat="BW";
	mintensity=0.0;
}

/// Overriding the copy constructor
PixelBW::PixelBW(const PixelBW& copiedPixel) : Pixel(copiedPixel)
{
	mintensity=copiedPixel.mintensity;
}

/// Overloading of the [] operator
double PixelBW::operator[] (int index) const
{
	assert(index==1);
	return mintensity;
}

