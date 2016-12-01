/*
 * ImageBW.hpp
 *
 *  Created on: Nov 30, 2016
 *      Author: adrien
 */

#ifndef SRC_IMAGEBW_HPP_
#define SRC_IMAGEBW_HPP_

#include "Image.hpp";
#include "PixelBW.hpp";

class ImageBW : public Image
{
private:
	/// mPmatrix is a matrix containing the pixels of the image
	vector<vector<PixelBW>>* mPmatrix;
public:
	ImageBW();
};



#endif /* SRC_IMAGEBW_HPP_ */
