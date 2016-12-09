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
	ImageBW();
	ImageBW(const string name);

	void Display() const;
};



#endif /* SRC_IMAGEBW_HPP_ */
