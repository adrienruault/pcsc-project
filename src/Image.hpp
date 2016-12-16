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

	Image(const int& width, const int& height, const double& intensity=0, const std::string& name="undefined.jpg");
	Image(const std::string& name);
	Image(const Fourier_Transform< Image<P> >& fft );
	Image(const std::vector<std::vector<double> > intensity_array);
	Image(){mheight=0; mwidth=0; mspectra=0;};


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
	void Display(const std::string& save_name) const;
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
	Image<P> RescaledCopy() const;
	std::vector<int> ComputeDistribution(const int& channel=0) const;
	//std::vector<int> GetDistribution(const int& channel=0) const;
	//void UpdateDistribution(const int& channel=0);
	int GreatestPopDist(const int& channel=0) const;

	Image<P> AddMirrorBoundary(const int& left, const int& right, const int& top, const int& bot) const;
	Image<P> log_Rescale() const;
	void shift_zero_to_center(); // To modify for RGB




	/*
	// Is the const keyword at the end of the declaration necessary? -> Yes
	// virtual void Save(const string name=mname) const=0;

	double MaxI(const int& channel=0) const;
	double MinI(const int& channel=0) const;

	void Histogram(Image& histo, const std::string& provided_name="undefined")=0;
	*/
};


#endif /* SRC_IMAGE_HPP_ */
