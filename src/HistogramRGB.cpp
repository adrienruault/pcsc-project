/*
 * HistogramRGB.cpp
 *
 *  Created on: Dec 14, 2016
 *      Author: adrien
 */


//#include "Image.hpp"
#include "HistogramRGB.hpp"



HistogramRGB::HistogramRGB(const Image<PixelRGB>& subject)
: Image<PixelRGB>(512, 600, 255, "histogram"+subject.GetName(), "no")
{
	// Computes the max number of pixels that have the same intensity for each channel
	int greatest_pop_dist0=subject.GreatestPopDist(0);
	int greatest_pop_dist1=subject.GreatestPopDist(1);
	int greatest_pop_dist2=subject.GreatestPopDist(2);

	// Computes the ratio that scale the max intensity such that the max peak of the
	// histogram reaches (4/5) of the height.
	int single_1plot=200;
	double ratio0=0.8*(double)single_1plot/(double)greatest_pop_dist0;
	double ratio1=0.8*(double)single_1plot/(double)greatest_pop_dist1;
	double ratio2=0.8*(double)single_1plot/(double)greatest_pop_dist2;

	// Red part of histogram, lowest one
	int pixels_to_fill;
	int col;
	std::vector<int> distrib0=subject.GetDistribution(0);
	for(int i=0; i<256; i++)
	{
		pixels_to_fill=(int)((double)distrib0[i]*ratio0);
		for(int j=0; j<pixels_to_fill; j++)
		{
			col=2*i;
			mPmatrix[col][mheight-j-1][1]=0;
			mPmatrix[col+1][mheight-j-1][1]=0;
			mPmatrix[col][mheight-j-1][2]=0;
			mPmatrix[col+1][mheight-j-1][2]=0;
		}
	}

	// Green part of histogram, lowest one
	pixels_to_fill=0;
	std::vector<int> distrib1=subject.GetDistribution(1);
	for(int i=0; i<256; i++)
	{
		pixels_to_fill=(int)((double)distrib1[i]*ratio1);
		for(int j=0; j<pixels_to_fill; j++)
		{
			col=2*i;
			mPmatrix[col][mheight-200-j-1][0]=0;
			mPmatrix[col+1][mheight-200-j-1][0]=0;
			mPmatrix[col][mheight-200-j-1][2]=0;
			mPmatrix[col+1][mheight-200-j-1][2]=0;
		}
	}

	// Blue part of histogram, lowest one
	pixels_to_fill=0;
	std::vector<int> distrib2=subject.GetDistribution(2);
	for(int i=0; i<256; i++)
	{
		pixels_to_fill=(int)((double)distrib2[i]*ratio2);
		for(int j=0; j<pixels_to_fill; j++)
		{
			col=2*i;
			mPmatrix[col][mheight-400-j-1][0]=0;
			mPmatrix[col+1][mheight-400-j-1][0]=0;
			mPmatrix[col][mheight-400-j-1][1]=0;
			mPmatrix[col+1][mheight-400-j-1][1]=0;
		}
	}
}

