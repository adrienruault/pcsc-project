/*
 * ImageBW.cpp
 *
 *  Created on: Nov 30, 2016
 *      Author: adrien
 */

#include <iostream>
#include <vector>
#include <cassert>

#include "CImg.h"
#include "ImageBW.hpp"
//#include "PixelBW.hpp"



using namespace cimg_library;
using namespace std;

/// Overriding default constructor
/// It constructs a black image of dimension 100x100 pixels
ImageBW::ImageBW()
//	: Image::Image()
{
	// Format of the image defined to Black and White
	mformat="BW";

	// Definition of dimensions attributes (initialized to 100 pixels by default)
	mwidth=100;
	mheight=100;

	// Is what is below correct to reserve 100x100 memory for a vector of vector ?
	// Image dimension:
	int n=100;
	mPmatrix.reserve(n);
	/*
	for (int i=0; i<n; i++)
	{
		mPmatrix[i].reserve(n);
	}
	*/

	/// Initialization of every matrix elements to 0.0
	PixelBW new_pixel(0.0);
	for (int i=0; i<n; i++)
	{
		for (int j=0; j<n; j++)
		{
			mPmatrix[i].push_back(new_pixel);
			//mPmatrix[i][j].ChangeI(0.0);
		}
	}
}


/// Defining constructor that builds an Image object based on a JPEG file
ImageBW::ImageBW(const string name)
{
	// In the future: try to implement a control on the string name
	// to verify that it is a JPG file

	// Defining the mname attribute
	mname=name;

	// Convert name which is a string into a const char* to pass it in CImg
	const char* char_name = name.c_str();
	CImg<double> img(char_name);

	// Check that spectrum is of size 1 which means that the image is Black and White
	assert(img.spectrum()==1);

	// Check that the image is effectively 2D which means its depth is 1
	assert(img.depth()==1);

	// Get the dimensions of the image
	mwidth=img.width();
	mheight=img.height();

	mPmatrix.reserve(mwidth);
	// Reserve the memory necessary for mPmatrix that contains the pixels of the image
	for (int i=0; i<mwidth; i++)
	{
		mPmatrix[i].reserve(mheight);
	}

	// Initialisation of matrix with 0



	// Transfer Black and White intensities of the image into the matrix
	// Please be careful that the indexing corresponds to the IP convention
	for (int i=0; i<mwidth; i++)
	{
		mPmatrix.push_back(vector<PixelBW>(mheight));
		for (int j=0; j<mheight; j++)
		{
			// Segmentation fault here
			mPmatrix[i][j].ChangeI(img(i,j));
		}
	}
}


/// Overloading of the () operator to be able to get and modify quickly the intensity
double& ImageBW::operator() (const int x, const int y, int channel /*=0*/)
{
	return &mPmatrix[x][y][0];
}

const double& ImageBW::operator() (const int x, const int y, int channel /*=0*/) const
{
	return mPmatrix[x][y][0];
}


/// Method that displays an image to the screen.
/// The idea is to convert our Pixel matrix in the format of the CImg library to be able
/// to use its facilities to display the image to the screen
void ImageBW::Display() const
{
	// Declare image using CImg library
	CImg<double> img(mwidth,mheight,1,1,0);

	// Transfer of the pixel value intensity
	for (int i=0; i<mwidth; i++)
	{
		for (int j=0; j<mheight; j++)
		{
			img(i,j)=mPmatrix[i][j][0];
		}
	}

	// Convert mname which is a string in const char*
	const char* char_name = mname.c_str();
	CImgDisplay disp_img(img,char_name);
	while (!disp_img.is_closed())
	{
		disp_img.wait();
	}
}


/// Method that saves the image with the provided name
/// The facilities provided by the CImg library are used here
void ImageBW::Save(const string save_name) const
{
	// Declare image using CImg library
	CImg<double> img(mwidth,mheight,1,1,0);

	// Transfer of the pixel value intensity
	for (int i=0; i<mwidth; i++)
	{
		for (int j=0; j<mheight; j++)
		{
			img(i,j)=mPmatrix[i][j][1];
		}
	}

	// Convert mname which is a string in const char*
	const char* char_name = save_name.c_str();
	img.save(char_name);
}






