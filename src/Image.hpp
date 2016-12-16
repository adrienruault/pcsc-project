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

#include "../CImg/CImg.h"
#include "ComplexNumber.hpp"
#include "PixelBW.hpp"
#include "PixelRGB.hpp"
#include "Error.hpp"

using namespace cimg_library;

template<typename I>
class Fourier_Transform;
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
	//std::vector<std::vector<int> > mdistribution;

public:
	/// Constructor that creates an image with specified dimensions.
	/// It initializes the intensity of every pixels to the specified intensity or to 0 if
	/// not provided.
	/// It names the image with the provided name.
	Image(const int& width, const int& height, const double& intensity=0, const std::string& name="undefined.jpg");

	/// Constructor that opens a .jpg image constructs an object Image from it.
	/// the path to the image have to be passed in argument as a string.
	Image(const std::string& name);




	/// Constructor that takes as input a vector of vector of double to build an image
	Image(const std::vector<std::vector<double> > intensity_array);
	Image(){mheight=0; mwidth=0; mspectra=0;};

	/// Overriding the copy constructor
	Image(const Image<P>& image_to_copy);

	/// Constructs an Image from its fourier transform
	/// if the fourier transform is RGB, the image constructed is RGB. Same for BW.
	Image(const Fourier_Transform< Image<P> >& fft );

	/// Overloading of the () operator to be able to modify quickly the intensity
	double& operator()(const int& x, const int& y, const int& channel=0);

	/// Overloading of the () operator to be able to get quickly the intensity
	const double& operator()(const int& x, const int& y, const int& channel=0) const;

	/// Method that returns the image width
	int Width() const;
	/// Method that returns the image height
	int Height() const;
	/// Method that changes the name of Image
	void SetName(const std::string& new_name);
	std::string GetName() const;
	/// Method that returns the number of channels of the image
	int GetSpectra() const;


	void Display() const;
	/// Method that displays the image under the name provided in argument
	void Display(const std::string& save_name) const;

	/// Method that saves the image with the provided name
	/// The facilities provided by the CImg library are used here
	void Save() const;
	void Save(const std::string& save_name) const;
	/// Set the intensity of every pixel at the one provided in argument for every channel
	void SetI(const double& new_intensity);
	// MaxI computes maximum intensity over all possible channel
	double MaxI() const;
	// MinI computes minimum intensity over all possible channels
	double MinI() const;
	// This rescale just multiply all pixel intensities by a factor computed such that
	// the highest intensity is fit to 255
	void Rescale();
	/// Method that returns an image that is rescaled so that the minimum intensity is 0
	/// and the maximum intensity is 255
	Image<P> RescaledCopy() const;

	/// Method that computes the distribution for the channel specified in argument
	std::vector<int> ComputeDistribution(const int& channel=0) const;

	/// Method that returns the greatest number of pixels associated to the same intensity
	/// for the channel specified in argument;
	int GreatestPopDist(const int& channel=0) const;

	/// Add symmetry boundary around an image. It is useful for the operation
	/// of convolution to not have boundary effects.
	Image<P> AddMirrorBoundary(const int& left, const int& right, const int& top, const int& bot) const;
	/// rescale the pixel values between 0 and 255 (same as rescale method) with a logarithmic scale
	Image<P> log_Rescale() const;
	/// Shift an image so that the top left pixel goes at the center of the image,
	/// useful for Fourier_Transform attributes to have the low frequencies
	/// in the center of the image.
	void shift_zero_to_center(); // To modify for RGB


};


#endif /* SRC_IMAGE_HPP_ */
