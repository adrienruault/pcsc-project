/*
 * Image.cpp
 *
 *  Created on: Dec 2, 2016
 *      Author: adrien
 */


#include "Image.hpp"


/// Overriding the default constructor
/// string variables are set to "undefined" and image dimensions to 0 by default
Image::Image()
{
	mformat="undefined";
	mname="undefined";
	mwidth=0;
	mheight=0;
}
