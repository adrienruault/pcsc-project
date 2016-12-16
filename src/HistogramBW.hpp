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
	std::vector<int> mdistributionBW;
public:
	HistogramBW(const Image<PixelBW>& subject);

	std::vector<int> GetDistribution();
};

#endif /* SRC2_HISTOGRAM_HPP_ */
