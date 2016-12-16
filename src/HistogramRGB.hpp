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
	std::vector<int> mdistributionR;
	std::vector<int> mdistributionG;
	std::vector<int> mdistributionB;
public:
	HistogramRGB(const Image<PixelRGB>& subject);

	std::vector<int> GetDistribution(const int& channel=0) const;
};






#endif /* SRC_HISTOGRAMRGB_HPP_ */
