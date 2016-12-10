/*
 * Image.cpp
 *
 *  Created on: Dec 10, 2016
 *      Author: adrien
 */

#include "Image.hpp"


/// Method that returns the image width
int Image::Width() const
{
	return mwidth;
}

/// Method that returns the image height
int Image::Height() const
{
	return mheight;
}

/// Method that changes the name of Image
void Image::SetName(const std::string new_name)
{
	mname=new_name;
}
