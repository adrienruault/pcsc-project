/*
 * ImageRGB.hpp
 *
 *  Created on: Dec 10, 2016
 *      Author: adrien
 */

#ifndef SRC_IMAGERGB_HPP_
#define SRC_IMAGERGB_HPP_

#include <iostream>
#include <vector>

#include "Image.hpp"
#include "PixelRGB.hpp"


class ImageRGB : Image
{
private:
	/// mPmatrix is a matrix containing the pixels of the image
	std::vector<std::vector<PixelRGB> > mPmatrix;
public:
	ImageRGB(const int& width, const int& height, const std::string& name="undefined.jpg");
	ImageRGB(const std::string& name);

	double& operator()(const int& x, const int& y, const int& channel);
	const double& operator()(const int& x, const int& y, const int& channel) const;

	void Display() const;
	void Save() const;
	void Save(const std::string& save_name) const;
	void SetI(const double& new_intensity) {}
	void Histogram(const std::string& histo_name) const {}
};


#endif /* SRC_IMAGERGB_HPP_ */
