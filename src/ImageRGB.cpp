/*
 * ImageRGB.cpp
 *
 *  Created on: Dec 10, 2016
 *      Author: adrien
 */

#include <vector>

#include "CImg.h"
#include "ImageRGB.hpp"
#include "Error.hpp"

using namespace cimg_library;

/// Constructor that creates a colored image with provided dimensions and name
ImageRGB::ImageRGB(const int& width, const int& height, const std::string& name /*="undefined.jpg"*/)
{
	// Image format defined to Red Green Blue
	mformat="RGB";

	mname=name;

	// Definition of dimensions attributes (initialized to 100 pixels by default)
	mwidth=width;
	mheight=height;

	// Image dimension:
	mPmatrix.reserve(mwidth);
	for (int i=0; i<mwidth; i++)
	{
		mPmatrix[i].reserve(mheight);
	}


	for (int i=0; i<mwidth; i++)
	{
		mPmatrix.push_back(std::vector<PixelRGB>(mheight));
		for (int j=0; j<mheight; j++)
		{
			// Set three channels to 0 intensity
			mPmatrix[i][j][0]=0;
			mPmatrix[i][j][1]=0;
			mPmatrix[i][j][2]=0;
		}
	}
}


/// Constructor that builds an ImageRGB based on a JPEG file
ImageRGB::ImageRGB(const std::string& name)
{
	// In the future: try to implement a control on the string name
	// to verify that it is a JPG file

	mformat="RGB";
	mname=name;


	// Convert name which is a string into a const char* to pass it in CImg
	const char* char_name = name.c_str();
	CImg<double> img(char_name);

	// Check that spectrum is of size 3 which means that the image is RGB
	if (img.spectrum()!=3)
	{
		throw ErrorFormat(mformat);
	}


	// Check that the image is effectively 2D which means its depth is 1
	//assert(img.depth()==1);

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
		mPmatrix.push_back(std::vector<PixelRGB>(mheight));
		for (int j=0; j<mheight; j++)
		{
			mPmatrix[i][j][0]=img(i,j,0,0);
			mPmatrix[i][j][1]=img(i,j,0,1);
			mPmatrix[i][j][2]=img(i,j,0,2);
		}
	}
}


/// Overloading of the () operator to be able to get and modify quickly the intensity
double& ImageRGB::operator()(const int& x, const int& y, const int& channel /*=0*/)
{
	if ((0<=x and x<mwidth) and (0<=y and y<mheight))
	{
		return mPmatrix[x][y][channel];
	}
	else
	{
		throw ErrorDimensions(x,y);
	}

}

const double& ImageRGB::operator()(const int& x, const int& y, const int& channel /*=0*/) const
{
	if ((0<=x and x<mwidth) and (0<=y and y<mheight))
	{
		return mPmatrix[x][y][channel];
	}
	else
	{
		throw ErrorDimensions(x,y);
	}
}


/// Method that displays an image to the screen.
/// The idea is to convert our Pixel matrix in the format of the CImg library to be able
/// to use its facilities to display the image to the screen
void ImageRGB::Display() const
{
	// Declare image using CImg library
	CImg<double> img(mwidth,mheight,1,3,0);

	// Transfer of the pixel value intensity
	for (int i=0; i<mwidth; i++)
	{
		for (int j=0; j<mheight; j++)
		{
			img(i,j,0,0)=mPmatrix[i][j][0];
			img(i,j,0,1)=mPmatrix[i][j][1];
			img(i,j,0,2)=mPmatrix[i][j][2];
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
void ImageRGB::Save() const
{
	// Declare image using CImg library
	CImg<double> img(mwidth,mheight,1,3,0);

	// Transfer of the pixel value intensity
	for (int i=0; i<mwidth; i++)
	{
		for (int j=0; j<mheight; j++)
		{
			img(i,j,0,0)=mPmatrix[i][j][0];
			img(i,j,0,1)=mPmatrix[i][j][1];
			img(i,j,0,2)=mPmatrix[i][j][2];
		}
	}
	// Convert mname which is a string in const char*
	const char* char_name = mname.c_str();
	img.save(char_name);
}


void ImageRGB::Save(const std::string& save_name) const
{
	// Declare image using CImg library
	CImg<double> img(mwidth,mheight,1,3,0);

	// Transfer of the pixel value intensity
	for (int i=0; i<mwidth; i++)
	{
		for (int j=0; j<mheight; j++)
		{
			img(i,j,0,0)=mPmatrix[i][j][0];
			img(i,j,0,1)=mPmatrix[i][j][1];
			img(i,j,0,2)=mPmatrix[i][j][2];
		}
	}

	// Convert mname which is a string in const char*
	const char* char_name = save_name.c_str();
	img.save(char_name);
}


