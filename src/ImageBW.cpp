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

/// Overriding default constructor
/// It constructs a black image of dimension width x height pixels
ImageBW::ImageBW(const int width, const int height, const string name/*="undefined.jpg"*/)
//	: Image::Image()
{
	// Format of the image defined to Black and White
	mformat="BW";

	mname=name;

	// Definition of dimensions attributes (initialized to 100 pixels by default)
	mwidth=width;
	mheight=height;

	// Is what is below correct to reserve height x width memory for a vector of vector ?
	// Image dimension:
	mPmatrix.reserve(mwidth);
	for (int i=0; i<mwidth; i++)
	{
		mPmatrix[i].reserve(mheight);
	}


	for (int i=0; i<mwidth; i++)
	{
		mPmatrix.push_back(vector<PixelBW>(mheight));
		for (int j=0; j<mheight; j++)
		{
			mPmatrix[i][j].ChangeI(0.0);
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

	// Transfer Black and White intensities of the image into the matrix
	// Please be careful that the indexing corresponds to the IP convention
	for (int i=0; i<mwidth; i++)
	{
		mPmatrix.push_back(vector<PixelBW>(mheight));
		for (int j=0; j<mheight; j++)
		{
			mPmatrix[i][j].ChangeI(img(i,j));
		}
	}
}


/// Overloading of the () operator to be able to get and modify quickly the intensity
double& ImageBW::operator()(const int x, const int y, const int channel)
{
	//assert(channel==0);
	return mPmatrix[x][y][channel];
}

const double& ImageBW::operator()(const int x, const int y, const int channel) const
{
	//assert(channel==0);
	return mPmatrix[x][y][channel];
	//return const_cast<ImageBW*>(this)->operator()(x,y,channel);
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
void ImageBW::Save() const
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
	img.save(char_name);
}


void ImageBW::Save(const string save_name) const
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
	const char* char_name = save_name.c_str();
	img.save(char_name);
}






