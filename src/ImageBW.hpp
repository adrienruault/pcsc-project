/*
 * ImageBW.hpp
 *
 *  Created on: Nov 30, 2016
 *      Author: adrien
 */

#ifndef SRC_IMAGEBW_HPP_
#define SRC_IMAGEBW_HPP_

#include <iostream>
#include <vector>

#include "Image.hpp"
#include "PixelBW.hpp"



class ImageBW : public Image
{
private:
	/// mPmatrix is a matrix containing the pixels of the image
	std::vector<std::vector<PixelBW> > mPmatrix;
public:
	ImageBW(const int width, const int height, const string name="undefined.jpg");
	ImageBW(const string name);


	double& operator()(const int x, const int y, const int channel);
	const double& operator()(const int x, const int y, const int channel) const;


	void Display() const;
	void Save() const;
	void Save(const string save_name) const;
};



#endif /* SRC_IMAGEBW_HPP_ */
