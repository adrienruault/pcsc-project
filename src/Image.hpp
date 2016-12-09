/*
 * Image.hpp
 *
 *  Created on: Nov 30, 2016
 *      Author: adrien
 */

#ifndef SRC_IMAGE_HPP_
#define SRC_IMAGE_HPP_

#include <iostream>

/// Declaring the base class that contains the information related to an image.
/// It mainly uses the Pixel class and make a matrix of it.
/// It has two derived classes that are ImageBW and ImageRGB.
class Image
{
protected:
	/// mformat can be either "undefined", "BW", or "RGB"
	std::string mformat;
	std::string mname;

	/// Image dimensions
	int mwidth;
	int mheight;


public:
	Image();

	// Virtual destructor needed for purely abstract class
	virtual ~Image() {};

	virtual double& operator() (const int x, const int y, const int channel=0);
	virtual const double& operator() (const int x, const int y, const int channel=0) const;

	// Is the const keyword at the end of the declaration necessary?
	// virtual void Save(const string name=mname) const=0;
	virtual void Display() const=0;
	virtual void Save(const std::string save_name) const=0;
};

#endif /* SRC_IMAGE_HPP_ */
