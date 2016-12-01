/*
 * Image.hpp
 *
 *  Created on: Nov 30, 2016
 *      Author: adrien
 */

#ifndef SRC_IMAGE_HPP_
#define SRC_IMAGE_HPP_

#include <iostream>

using namespace std;

class Image
{
private:
	/// mformat can be either "undefined", "BW", or "RGB"
	string mformat;
	string mname;

	/// Image dimensions
	int mwidth;
	int mheight;

public:
	Image();
};


/// Overriding the default constructor
/// string variables are set to "undefined" and image dimensions to 0 by default
Image::Image()
{
	mformat="undefined";
	mname="undefined";
	mwidth=0;
	mheight=0;
}




#endif /* SRC_IMAGE_HPP_ */
