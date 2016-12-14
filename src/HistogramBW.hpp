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
public:
	HistogramBW(const Image<PixelBW>& subject);
};

#endif /* SRC2_HISTOGRAM_HPP_ */
