/*
 * PixelBW.hpp
 *
 *  Created on: Nov 30, 2016
 *      Author: adrien
 */

#ifndef SRC_PIXELBW_HPP_
#define SRC_PIXELBW_HPP_

#include "Pixel.hpp"

/// Declaration of class that represents a monocolor black and white pixel
// It might be useful to think about the implementation of a template to allow more
// flexibility with the type in which is expressed the intensity. Actually it might be
// useless in the sense that we are going to call CImg ourselves and thus we will be
// able to control the type used.
class PixelBW: public Pixel
{
private:
	double mintensity;

public:
	/// Overriding the default constructor
	/// Intensity is set to 0.0 by default
	// No call for the default constructor of the base class here: Pixel()
	// because it seems useless
	PixelBW();
	/// Overriding the copy constructor
	PixelBW(const PixelBW& copiedPixel);
	/// Constructs a BW Pixel with intensity specified in argument
	PixelBW(const double intensity);

	/// Overloading of the [] operator to get and set intensity
	/// channel is set to 0 by default which is suitable for monochromatic Pixel.
	/// Only channel 0 is accepted: throws an error otherwise.
	double& operator[] (const int channel);
	const double& operator[] (const int channel) const;

	/// Get the intensity of a Pixel
	double GetI(const int channel=0) const;

	/// Method that allows to change the intensity of a pixel.
	/// The argument new intensity is used to provide the new intensity.
	/// As in the GetI method the channel variable must be let to 1
	/// because we only have one color
	/// Be careful: don't put default definition is function declaration but in prototype
	void ChangeI(const double new_intensity, const int channel=0);
};




#endif /* SRC_PIXELBW_HPP_ */
