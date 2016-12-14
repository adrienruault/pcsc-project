/*
 * HistogramBW.cpp
 *
 *  Created on: Dec 14, 2016
 *      Author: adrien
 */


#include "HistogramBW.hpp"





HistogramBW::HistogramBW(const Image<PixelBW>& subject)
: Image<PixelBW>(512, 300, 255, "histogram"+subject.GetName(), "no")
{
	// Computes the max number of pixels that have the same intensity
	int greatest_pop_dist=subject.GreatestPopDist();

	// Computes the ratio that scale the max intensity such that the max peak of the
	// histogram reaches (4/5) of the height.
	double ratio=0.8*(double)mheight/(double)greatest_pop_dist;
	int nb_pixel;
	int col;
	std::vector<int> subject_distrib=subject.GetDistribution();
	for(int i=0; i<256; i++)
	{
		nb_pixel=(int)((double)subject_distrib[i]*ratio);
		for (int k=0; k<nb_pixel; k++)
		{
			//std::cout << i << "\t" << k << "\n";
			col=2*i;
			mPmatrix[col][mheight-1-k][0]=0;
			mPmatrix[col+1][mheight-1-k][0]=0;
		}
	}
}





