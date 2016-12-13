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
#include "Error.hpp"
//#include "PixelBW.hpp"



using namespace cimg_library;

/// Constructs a black image of dimension width x height pixels
ImageBW::ImageBW(const int& width, const int& height, const double& intensity, const std::string& name/*="undefined.jpg"*/)
//	: Image::Image()
{
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
		mPmatrix.push_back(std::vector<PixelBW>(mheight));
		for (int j=0; j<mheight; j++)
		{
			mPmatrix[i][j][0]=intensity;
		}
	}

	// Computing the vector of distribution
	// Initialisation at 0
	mdistribution.reserve(257);
	for(int i=0; i<257; i++)
	{
		mdistribution.push_back(0);
	}

	// Filling of mdistribution
	for(int i=0; i<mwidth; i++)
	{
		for(int j=0; j<mheight; j++)
		{
			int k=mPmatrix[i][j][0];
			mdistribution[k]+=1;
		}
	}

	// Last element signals that mdistribution is up-to-date
	mdistribution[256]=1;
}


/// Constructor that builds an Image object based on a JPEG file
ImageBW::ImageBW(const std::string& name)
{
	// In the future: try to implement a control on the string name
	// to verify that it is a JPG file

	mformat="BW";
	mname=name;

	// Convert name which is a string into a const char* to pass it in CImg
	const char* char_name = name.c_str();
	CImg<double> img(char_name);

	// Check that spectrum is of size 3 which means that the image is RGB
	if (img.spectrum()!=1)
	{
		throw ErrorFormat(mformat);
	}

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
		mPmatrix.push_back(std::vector<PixelBW>(mheight));
		for (int j=0; j<mheight; j++)
		{
			mPmatrix[i][j][0]=img(i,j);
		}
	}

	// Computing the vector of distribution
	// Initialisation at 0
	mdistribution.reserve(257);
	for(int i=0; i<257; i++)
	{
		mdistribution.push_back(0);
	}

	// Filling of mdistribution
	for(int i=0; i<mwidth; i++)
	{
		for(int j=0; j<mheight; j++)
		{
			int k=mPmatrix[i][j][0];
			mdistribution[k]+=1;
		}
	}

	// Last element signals that mdistribution is up-to-date
	mdistribution[256]=1;
}


/// Overloading of the () operator to be able to get and modify quickly the intensity
double& ImageBW::operator()(const int& x, const int& y, const int& channel /*=0*/)
{
	if ((0<=x and x<mwidth) and (0<=y and y<mheight))
	{
		// Last element signals that mdistribution is out-dated
		mdistribution[256]=0;
		return mPmatrix[x][y][channel];
	}
	else
	{
		throw ErrorDimensions(x,y);
	}

}

const double& ImageBW::operator()(const int& x, const int& y, const int& channel /*=0*/) const
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


/// Method that updates mdistribution
void ImageBW::UpdateDistribution()
{
	// Resetting mdistribution to 0
	for(int i=0; i<256; i++)
	{
		mdistribution[i]=0;
	}

	// Filling of mdistribution
	for(int i=0; i<mwidth; i++)
	{
		for(int j=0; j<mheight; j++)
		{
			int k=mPmatrix[i][j][0];
			mdistribution[k]+=1;
		}
	}

	// Last element signals that mdistribution is up-to-date:
	mdistribution[256]=1;
}


/// Method that returns the greater number of pixel with identical intensity
int ImageBW::MostPopI(const int& channel)
{
	if (mdistribution[256]==0)
	{
		ImageBW::UpdateDistribution();
	}

	int max=0;
	for(int i=0; i<256; i++)
	{
		if (mdistribution[i] > max)
		{
			max=mdistribution[i];
		}
	}
	return max;
}


/// Method that returns the maximum intensity
double ImageBW::MaxI(const int& channel /*=0*/) const
{
	if (channel!=0)
	{
		throw ErrorChannel(mformat);
	}

	// Initialize max value with the intensity of the top-left corner
	double max=mPmatrix[0][0][0];
	for(int i=0; i<mwidth; i++)
	{
		for(int j=0; j<mheight; j++)
		{
			if (mPmatrix[i][j][0] > max)
			{
				max=mPmatrix[i][j][0];
			}
		}
	}
	return max;
}


/// Method that returns the minimum intensity
double ImageBW::MinI(const int& channel /*=0*/) const
{
	if (channel!=0)
	{
		throw ErrorChannel(mformat);
	}

	// Initialize max value with the intensity of the top-left corner
	double min=mPmatrix[0][0][0];
	for(int i=0; i<mwidth; i++)
	{
		for(int j=0; j<mheight; j++)
		{
			if (mPmatrix[i][j][0] < min)
			{
				min=mPmatrix[i][j][0];
			}
		}
	}
	return min;
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


/// Method that saves an image with the name provided in argument
void ImageBW::Save(const std::string& save_name) const
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


/// Method that sets the intensity of every pixel of the image to the intensity
/// provided in argument
void ImageBW::SetI(const double& new_intensity)
{
	for(int i=0; i<mwidth; i++)
	{
		for(int j=0; j<mheight; j++)
		{
			mPmatrix[i][j][0]=new_intensity;
		}
	}
	// Last element signals that mdistribution is out-dated
	mdistribution[256]=0;
}


/// Method that creates an histogram that shows the distribution of pixel intensities
/// The ImageBW instance histo provided as argument must match one requirement:
/// 	-> It must have a width of 512 pixels
void ImageBW::Histogram(Image& histo, const std::string& provided_name /*="undefined"*/)
{
	int height=histo.Height();
	histo.SetI(255);

	double ratio=0.75*(double)height/(double)ImageBW::MostPopI();
	int nb_pixel;
	int x;
	for(int i=0; i<255; i++)
	{
		nb_pixel=(int)((double)mdistribution[i]*ratio);
		for (int k=0; k<nb_pixel; k++)
		{
			//std::cout << i << "\t" << k << "\n";
			x=2*i;
			histo(x,height-1-k,0)=0;
			histo(x+1,height-1-k,0)=0;
		}
	}

	std::string save_histo;
	// Set the name to histo name attribute if no name is provided as argument
	if (provided_name=="undefined")
	{
		save_histo=histo.GetName();
	}
	else
	{
		save_histo=provided_name;
	}

	histo.Display();
	histo.Save(save_histo);
}

