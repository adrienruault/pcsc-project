/*
 * Image.hpp
 *
 *  Created on: Nov 30, 2016
 *      Author: adrien
 */

#ifndef SRC_IMAGE_HPP_
#define SRC_IMAGE_HPP_

#include <iostream>
#include <vector>
#include <limits>
#include <typeinfo>

#include "CImg.h"

#include "PixelBW.hpp"
#include "PixelRGB.hpp"
#include "Error.hpp"

using namespace cimg_library;

/// Declaring the base class that contains the information related to an image.
/// It mainly uses the Pixel class and make a matrix of it.
/// It has two derived classes that are ImageBW and ImageRGB.
template<typename P>
class Image
{
protected:
	/// mformat can be either "undefined", "BW", or "RGB"
	//std::string mformat;
	int mspectra;
	std::string mname;

	/// Image dimensions
	int mwidth;
	int mheight;

	/// Matrix that contains every the pixels associated to each coordinates of the image
	std::vector<std::vector<P> > mPmatrix;

	/// Array with one entry for each channel that contains the number of pixels
	/// associated to each intensity
	std::vector<std::vector<int> > mdistribution;

public:
	Image(const int& width, const int& height, const double& intensity=0, const std::string& name="undefined.jpg", const std::string& compute_distrib="no");
	Image(const std::string& name, const std::string& compute_distrib="no");

	Image(const Image<P>& image_to_copy);

	// Virtual destructor needed for purely abstract class
	//virtual ~Image() {};

	double& operator()(const int& x, const int& y, const int& channel=0);
	const double& operator()(const int& x, const int& y, const int& channel=0) const;

	int Width() const;
	int Height() const;
	void SetName(const std::string& new_name);
	std::string GetName() const;
	int GetSpectra() const;

	void Display() const;
	void Save() const;
	void Save(const std::string& save_name) const;
	void SetI(const double& new_intensity);
	// MaxI computes maximum intensity over all possible channel
	double MaxI() const;
	// MinI computes minimum intensity over all possible channels
	double MinI() const;
	// This rescale just multiply all pixel intensities by a factor computed such that
	// the highest intensity is fit to 255
	void Rescale();
	std::vector<int> GetDistribution(const int& channel=0) const;
	void UpdateDistribution(const int& channel=0);
	int GreatestPopDist(const int& channel=0) const;

	Image<P> AddMirrorBoundary(const int& left, const int& right, const int& top, const int& bot) const;
	Image<P> log_Rescale() const;



	/*
	// Is the const keyword at the end of the declaration necessary? -> Yes
	// virtual void Save(const string name=mname) const=0;

	double MaxI(const int& channel=0) const;
	double MinI(const int& channel=0) const;

	void Histogram(Image& histo, const std::string& provided_name="undefined")=0;
	*/
};







/*
 * ************************************************************************************
 * ************************************************************************************
 * ************************************************************************************
 * METHODS DECLARATION
 * ************************************************************************************
 * ************************************************************************************
 * ************************************************************************************
 */


/// Constructor that creates an image with specified dimensions.
/// It initializes the intensity of every pixels to the specified intensity or to 0 if
/// not provided.
/// It names the image with the provided name.
template<typename P>
Image<P>::Image(const int& width, const int& height, const double& intensity /*=0*/, const std::string& name /*="undefined.jpg"*/, const std::string& compute_distrib /*="no"*/)
{
	if (typeid(P)==typeid(PixelBW))
	{
		mspectra=1;
	}
	else if (typeid(P)==typeid(PixelRGB))
	{
		mspectra=3;
	}
	else
	{
		throw ErrorPixelType();
	}

	mname=name;

	// Definition of dimensions attributes (initialized to 100 pixels by default)
	mwidth=width;
	mheight=height;

	/*
	// Image dimension:
	mPmatrix.reserve(mwidth);
	for (int i=0; i<mwidth; i++)
	{
		mPmatrix[i].reserve(mheight);
	}
	*/

	for (int i=0; i<mwidth; i++)
	{
		mPmatrix.push_back(std::vector<P>(mheight));
		for (int j=0; j<mheight; j++)
		{
			// Set channels to 0 intensity
			for(int c=0; c<mspectra; c++)
			{
				mPmatrix[i][j][c]=intensity;
			}
		}
	}

	if (compute_distrib=="yes")
	{
		if (intensity>255)
		{
			throw ErrorIntensity();
		}

		// Computation of the distribution array
		// Initialisation at 0
		mdistribution.reserve(mspectra);
		for(int c=0; c<mspectra; c++)
		{
			mdistribution[c].reserve(257);
		}

		for(int c=0; c<mspectra; c++)
		{
			mdistribution.push_back(std::vector<int>(257,0));
		}

		// Filling of mdistribution
		for(int i=0; i<mwidth; i++)
		{
			for(int j=0; j<mheight; j++)
			{
				for(int c=0; c<mspectra; c++)
				{
					int k=mPmatrix[i][j][c];
					mdistribution[c][k]+=1;
				}
			}
		}

		// Last element set to 1 signals that mdistribution[c] is up-to-date
		for(int c=0; c<mspectra; c++)
		{
			mdistribution[c][256]=1;
		}
	}
	else
	{
		mdistribution.reserve(mspectra);
		for(int c=0; c<mspectra; c++)
		{
			mdistribution.push_back(std::vector<int>(1,0));
		}
	}
}


/// Constructor that...
template <typename P>
Image<P>::Image(const std::string& name, const std::string& compute_distrib /*="no"*/)
{
	// In the future: try to implement a control on the string name
	// to verify that it is a JPG file
	if (typeid(P)==typeid(PixelBW))
	{
		mspectra=1;
	}
	else if (typeid(P)==typeid(PixelRGB))
	{
		mspectra=3;
	}
	else
	{
		throw ErrorPixelType();
	}

	mname=name;

	// Convert name which is a string into a const char* to pass it in CImg
	const char* char_name = name.c_str();
	CImg<double> img(char_name);

	// Check that the spectrum of the opened image coincide with that of Pixel type
	if (img.spectrum()!=mspectra)
	{
		throw ErrorFormat(mspectra);
	}

	// Check that the image is effectively 2D which means its depth is 1
	if (img.depth()!=1)
	{
		throw Error3DImage();
	}

	// Get the dimensions of the image
	mwidth=img.width();
	mheight=img.height();

	/*
	mPmatrix.reserve(mwidth);
	// Reserve the memory necessary for mPmatrix that contains the pixels of the image
	for (int i=0; i<mwidth; i++)
	{
		mPmatrix[i].reserve(mheight);
	}
	*/

	// Transfer Black and White intensities of the image into the matrix
	// Please be careful that the indexing corresponds to the IP convention
	for (int i=0; i<mwidth; i++)
	{
		mPmatrix.push_back(std::vector<P>(mheight));
		for (int j=0; j<mheight; j++)
		{
			// Copy pixels intensity
			for(int c=0; c<mspectra; c++)
			{
				mPmatrix[i][j][c]=img(i,j,0,c);
			}
		}
	}


	if (compute_distrib=="yes")
	{
		// Computation of the distribution array
		// Initialisation at 0
		mdistribution.reserve(mspectra);
		for(int c=0; c<mspectra; c++)
		{
			mdistribution[c].reserve(257);
		}

		for(int c=0; c<mspectra; c++)
		{
			mdistribution.push_back(std::vector<int>(257,0));
		}

		// Filling of mdistribution
		for(int i=0; i<mwidth; i++)
		{
			for(int j=0; j<mheight; j++)
			{
				for(int c=0; c<mspectra; c++)
				{
					int k=mPmatrix[i][j][c];
					mdistribution[c][k]+=1;
				}
			}
		}

		// Last element set to 1 signals that mdistribution[c] is up-to-date
		for(int c=0; c<mspectra; c++)
		{
			mdistribution[c][256]=1;
		}
	}
	else
	{
		mdistribution.reserve(mspectra);
		for(int c=0; c<mspectra; c++)
		{
			mdistribution.push_back(std::vector<int>(1,0));
		}
	}
}


/// Overriding the copy constructor
template <typename P>
Image<P>::Image(const Image<P>& image_to_copy)
{
	mspectra=image_to_copy.mspectra;
	mname=image_to_copy.mname;
	mwidth=image_to_copy.mwidth;
	mheight=image_to_copy.mheight;

	mPmatrix=image_to_copy.mPmatrix;
	mdistribution=image_to_copy.mdistribution;
}

/// Overloading of the () operator to be able to get and modify quickly the intensity
template <typename P>
double& Image<P>::operator()(const int& x, const int& y, const int& channel /*=0*/)
{
	if ((0<=x and x<mwidth) and (0<=y and y<mheight))
	{
		// Last element of mdistribution set to 0 signals that the array might be out-dated
		// Controls that the channel is allowed
		if (channel < 0 or channel >= mspectra)
		{
			throw ErrorChannel(mspectra);
		}
		// checking if mdistribution has been computed
		if(mdistribution[channel].size()==257)
		{
			mdistribution[channel][256]=0;
		}
		return mPmatrix[x][y][channel];
	}
	else
	{
		throw ErrorDimensions(x,y);
	}
}


template <typename P>
const double& Image<P>::operator()(const int& x, const int& y, const int& channel /*=0*/) const
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



/// Method that returns the image width
template<typename P>
int Image<P>::Width() const
{
	return mwidth;
}


/// Method that returns the image height
template<typename P>
int Image<P>::Height() const
{
	return mheight;
}


/// Method that changes the name of Image
template<typename P>
void Image<P>::SetName(const std::string& new_name)
{
	mname=new_name;
}

template<typename P>
std::string Image<P>::GetName() const
{
	return mname;
}


/// Method that returns the number of channels of the image
template<typename P>
int Image<P>::GetSpectra() const
{
	return mspectra;
}


/// Method that displays an image to the screen.
/// The idea is to convert our Pixel matrix in the format of the CImg library to be able
/// to use its facilities to display the image to the screen
template<typename P>
void Image<P>::Display() const
{
	// Declare image using CImg library
	CImg<double> img(mwidth,mheight,1,mspectra,0);

	// Transfer of the pixel value intensity
	for (int i=0; i<mwidth; i++)
	{
		for (int j=0; j<mheight; j++)
		{
			for(int c=0; c<mspectra; c++)
			{
				img(i,j,0,c)=mPmatrix[i][j][c];
			}
		}
	}

	// Convert mname which is a string in const char*
	const char* char_name = mname.c_str();
	CImgDisplay disp_img(img,char_name);
	// Seems to be mandatory to wait for the user to close
	//the displayed image to keep going
	while (!disp_img.is_closed())
	{
		disp_img.wait();
	}
}


/// Method that saves the image with the provided name
/// The facilities provided by the CImg library are used here
template<typename P>
void Image<P>::Save() const
{
	// Declare image using CImg library
	CImg<double> img(mwidth,mheight,1,mspectra,0);

	// Transfer of the pixel value intensity
	for (int i=0; i<mwidth; i++)
	{
		for (int j=0; j<mheight; j++)
		{
			for(int c=0; c<mspectra; c++)
			{
				img(i,j,0,c)=mPmatrix[i][j][c];
			}
		}
	}
	// Convert mname which is a string in const char*
	const char* char_name = mname.c_str();
	img.save(char_name);
}


template<typename P>
void Image<P>::Save(const std::string& save_name) const
{
	// Declare image using CImg library
	CImg<double> img(mwidth,mheight,1,mspectra,0);

	// Transfer of the pixel value intensity
	for (int i=0; i<mwidth; i++)
	{
		for (int j=0; j<mheight; j++)
		{
			for(int c=0; c<mspectra; c++)
			{
				img(i,j,0,c)=mPmatrix[i][j][c];
			}
		}
	}

	// Convert mname which is a string in const char*
	const char* char_name = save_name.c_str();
	img.save(char_name);
}


/// Set the intensity of every pixel at the one provided in argument for every channel
template<typename P>
void Image<P>::SetI(const double& new_intensity)
{
	for(int i=0; i<mwidth; i++)
	{
		for(int j=0; j<mheight; j++)
		{
			mPmatrix[i][j][0]=new_intensity;
		}
	}
	// Last element signals that mdistribution is out-dated
	for(int c=0; c<mspectra; c++)
	{
		mdistribution[c][256]=0;
	}
}


/// Method that sends
template <typename P>
std::vector<int> Image<P>::GetDistribution(const int& channel /*=0*/) const
{
	// Controls that the channel is allowed
	if (channel < 0 or channel >= mspectra)
	{
		throw ErrorChannel(mspectra);
	}
	if (mdistribution[channel][256] != 1)
	{
		// too_high_intensity / not_computed / out-dated
		throw ErrorDistribution("out-dated");
	}
	return mdistribution[channel];
}

/// Method that updates the distribution array for a particular channel provided in
/// argument
template<typename P>
void Image<P>::UpdateDistribution(const int& channel /*=0*/)
{
	if (channel < 0 or channel >= mspectra)
	{
		throw ErrorChannel(mspectra);
	}

	if(Image<P>::MaxI()>255)
	{
		Image<P>::Rescale();
	}

	// Resetting mdistribution to 0
	for(int i=0; i<256; i++)
	{
		mdistribution[channel][i]=0;
	}

	// Filling of mdistribution
	for(int i=0; i<mwidth; i++)
	{
		for(int j=0; j<mheight; j++)
		{
			int k=mPmatrix[i][j][channel];
			mdistribution[channel][k]+=1;
		}
	}

	// Last element signals that mdistribution is up-to-date:
	mdistribution[channel][256]=1;
}


/// Methods that output the maximum pixel intensity of the image over all possible channels
template<typename P>
double Image<P>::MaxI() const
{
	double max=-std::numeric_limits<double>::infinity();;
	for(int i=0; i<mwidth; i++)
	{
		for(int j=0; j<mheight; j++)
		{
			for(int c=0; c<mspectra; c++)
			{
				if (mPmatrix[i][j][c] > max)
				{
					max=mPmatrix[i][j][c];
				}
			}
		}
	}
	return max;
}


/// Methods that output the minimum pixel intensity of the image over all possible channels
template<typename P>
double Image<P>::MinI() const
{
	double min=std::numeric_limits<double>::infinity();
	for(int i=0; i<mwidth; i++)
	{
		for(int j=0; j<mheight; j++)
		{
			for(int c=0; c<mspectra; c++)
			{
				if (mPmatrix[i][j][c] < min)
				{
					min=mPmatrix[i][j][c];
				}
			}
		}
	}
	return min;
}

/// Methods that rescale the pixel intensity so that the max value is 255
template<typename P>
void Image<P>::Rescale()
{
	double max_intensity = Image<P>::MaxI();
	double min_intensity = Image<P>::MinI();
	double factor=(double)255/(max_intensity);

	int relay;
	for(int i=0; i<mwidth; i++)
	{
		for(int j=0; j<mheight; j++)
		{
			for(int c=0; c<mspectra; c++)
			{
				relay=mPmatrix[i][j][c]*factor;
				mPmatrix[i][j][c]=relay;
			}
		}
	}

	for(int c=0; c<mspectra; c++)
	{
		mdistribution[c][256]=0;
	}
}

template<typename P>
Image<P> Image<P>::log_Rescale() const
{
	Image<P> img(Width(),Height());
	for (size_t i = 0; i < Width(); i++) {
		for (size_t j = 0; j < Height(); j++) {
			img(i,j) = log((*this)(i,j));
		}
	}
	img.Rescale();
	return img;
}


/// Method that
template <typename P>
int Image<P>::GreatestPopDist(const int& channel /*=0*/) const
{
	// Check if the channel request is allowed
	if (channel < 0 or channel >= mspectra)
	{
		throw ErrorChannel(mspectra);
	}

	// Check if distribution has been computed
	if (mdistribution[channel].size() != 257)
	{
		// too_high_intensity / not_computed / out-dated
		throw ErrorDistribution("not_computed");
	}

	// Check if distribution is up-to-date
	if (mdistribution[channel][256] != 1)
	{
		// too_high_intensity / not_computed / out-dated
		throw ErrorDistribution("out-dated");
	}
	int greatest_pop=0;
	for(int i=0; i<256; i++)
	{
		if (mdistribution[channel][i]>greatest_pop)
		{
			greatest_pop=mdistribution[channel][i];
		}
	}
	return greatest_pop;
}



template<typename P>
Image<P> Image<P>::AddMirrorBoundary(const int& left, const int& right, const int& top, const int& bot) const
{
  Image<P> output(left+Image::Width()+right, top+Image::Height()+bot);

  int img_width = Image::Width();
  int img_height = Image::Height();

  for (size_t x = 0; x < output.Width(); x++) {
    for (size_t y = 0; y < output.Height(); y++) {
      int i;
      int j;
      if (x < left)
      {
    	  i = left-x-1;
      }
      else if (x >= (left + img_width))
      {
    	  i = -1+img_width-(x-(left+img_width));
      }
      else
      {
    	  i = x-left;
      }
      if (y < top)
      {
    	  j = top-y-1;
      }
      else if (y >= top + img_height)
      {
    	  j =  -1+img_height-(y-(top+img_height));
      }
      else
      {
    	  j = y-top;
      }
      output(x,y) = (*this)(i,j,0);
      //if (x<100 and y<50) output(x,y) = 0;
    }
  }
  return output;
}






#endif /* SRC_IMAGE_HPP_ */
