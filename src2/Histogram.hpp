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
	HistogramBW(Image<PixelBW>& subject);
};


HistogramBW::HistogramBW(Image<PixelBW>& subject)
: Image<PixelBW>(512, 300, 255, "histogram"+subject.GetName(), "no")
{
	// Computes the max number of pixels that have the same intensity
	int greatest_pop_dist=subject.GreatestPopDist(0);

	// Computes the ratio that scale the max intensity such that the max peak of the
	// histogram reaches (3/4) of the height.
	double ratio=0.75*(double)mheight/(double)greatest_pop_dist;
	int nb_pixel;
	int x;
	std::vector<int> subject_distrib=subject.GetDistribution();
	for(int i=0; i<255; i++)
	{
		nb_pixel=(int)((double)subject_distrib[i]*ratio);
		for (int k=0; k<nb_pixel; k++)
		{
			//std::cout << i << "\t" << k << "\n";
			x=2*i;
			mPmatrix[x][mheight-1-k][0]=0;
			mPmatrix[x+1][mheight-1-k][0]=0;
		}
	}
}












/*
 * HistogramRGB
 */
/*
class HistogramRGB
: public
*/


#endif /* SRC2_HISTOGRAM_HPP_ */
