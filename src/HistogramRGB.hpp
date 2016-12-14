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
public:
	HistogramRGB(const Image<PixelRGB>& subject);
};






#endif /* SRC_HISTOGRAMRGB_HPP_ */
