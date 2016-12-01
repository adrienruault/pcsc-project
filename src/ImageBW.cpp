/*
 * ImageBW.cpp
 *
 *  Created on: Nov 30, 2016
 *      Author: adrien
 */

#include <iostream>
#include <vector>

#include "CImg.h";
#include "ImageBW.hpp"


using namespace cimg_library;


/// Overriden default constructor
/// It constructs a 100x100 pixels black image
ImageBW::ImageBW() : Image()
{
	// Is it correct to reserve 100x100 memory for a vector of vector ?
	//mPmatrix(100, vector<PixelBW>(100,1));
	vector<vector<PixelBW>> init(100, vector<PixelBW>(100,1));

	// We ensure that any change on init will be accounted by the pointer mPmatrix
	mPmatrix=&init;

	int n=100;
	for (int i=0; i<n; i++)
	{
		for (int j=0; j<n; j++)
		{
			init[i][j]
		}
	}
}


