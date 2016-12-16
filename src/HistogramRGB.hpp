/*
 * HistogramRGB.hpp
 *
 *  Created on: Dec 14, 2016
 *      Author: adrien
 */

#ifndef SRC_HISTOGRAMRGB_HPP_
#define SRC_HISTOGRAMRGB_HPP_

#include "Image.hpp"

class HistogramRGB
: public Image<PixelRGB>
{
private:
	// mdistributionR is a vector containing the number of pixels associated to Red intensity
	std::vector<int> mdistributionR;
	// mdistributionG is a vector containing the number of pixels associated to Green intensity
	std::vector<int> mdistributionG;
	// mdistributionB is a vector containing the number of pixels associated to Blue intensity
	std::vector<int> mdistributionB;
public:
	/// Constructor that creates a colored histogram of width 512 and height 600
	/// The abscissa represents the intensity, and the ordinate the number of
	/// pixels associated to a particular intensity of a particular channel.
	HistogramRGB(const Image<PixelRGB>& subject);

	/// Method that returns the mdistribution vector of the specified channell
	std::vector<int> GetDistribution(const int& channel=0) const;
};






#endif /* SRC_HISTOGRAMRGB_HPP_ */
