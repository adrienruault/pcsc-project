/*
 * Histogram.hpp
 *
 *  Created on: Dec 12, 2016
 *      Author: adrien
 */

#ifndef SRC2_HISTOGRAM_HPP_
#define SRC2_HISTOGRAM_HPP_

#include "Image.hpp"

class HistogramBW
: public Image<PixelBW>
{
private:
	/// mdistributionBW is a vector containing the number of pixels associated to each intensity
	std::vector<int> mdistributionBW;
public:
	/// Constructor that creates a black and white histogram of width 512 and height 300
	/// The abscissa represents the intensity, and the ordinate the number of
	/// pixels associated to a particular intensity.
	HistogramBW(const Image<PixelBW>& subject);

	/// Method that returns the mdistributionBW vector
	std::vector<int> GetDistribution();
};

#endif /* SRC2_HISTOGRAM_HPP_ */
