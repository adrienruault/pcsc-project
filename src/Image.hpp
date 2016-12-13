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
	//Image();

	// Virtual destructor needed for purely abstract class
	virtual ~Image() {};

	virtual double& operator()(const int& x, const int& y, const int& channel=0)=0;
	virtual const double& operator()(const int& x, const int& y, const int& channel=0) const=0;

	int Width() const;
	int Height() const;
	void SetName(const std::string& new_name);
	std::string GetName() const;

	// Is the const keyword at the end of the declaration necessary? -> Yes
	// virtual void Save(const string name=mname) const=0;
	virtual int MostPopI(const int& channel=0)=0;
	virtual double MaxI(const int& channel=0) const=0;
	virtual double MinI(const int& channel=0) const=0;
	virtual void Display() const=0;
	virtual void Save() const=0;
	virtual void Save(const std::string& save_name) const=0;
	virtual void SetI(const double& new_intensity)=0;
	virtual void Histogram(Image& histo, const std::string& provided_name="undefined")=0;
};

#endif /* SRC_IMAGE_HPP_ */
