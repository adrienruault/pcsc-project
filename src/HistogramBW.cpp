/*
 * HistogramBW.cpp
 *
 *  Created on: Dec 14, 2016
 *      Author: adrien
 */


#include "HistogramBW.hpp"





HistogramBW::HistogramBW(const Image<PixelBW>& subject)
: Image<PixelBW>(512, 300, 255, "histogram"+subject.GetName())
{
	// Controls that max intensity is not above 255, otherwise it creates a copy of
	// the subject and rescale it
	Image<PixelBW> good_subject(subject);
	if (subject.MaxI() > 255)
	{
		good_subject.Rescale();
	}

	// Computes the max number of pixels that have the same intensity
	int greatest_pop_dist=good_subject.GreatestPopDist(0);

	// Computes the ratio that scale the max intensity such that the max peak of the
	// histogram reaches (4/5) of the height.
	double ratio=0.8*(double)mheight/(double)greatest_pop_dist;
	int nb_pixel;
	int col;
	mdistributionBW=good_subject.ComputeDistribution(0);
	for(int i=0; i<256; i++)
	{
		nb_pixel=(int)((double)mdistributionBW[i]*ratio);
		for (int k=0; k<nb_pixel; k++)
		{
			//std::cout << i << "\t" << k << "\n";
			col=2*i;
			mPmatrix[col][mheight-1-k][0]=0;
			mPmatrix[col+1][mheight-1-k][0]=0;
		}
	}
}


/// Method that returns the distribution of the distribution
std::vector<int> HistogramBW::GetDistribution()
{
	return mdistributionBW;
}




