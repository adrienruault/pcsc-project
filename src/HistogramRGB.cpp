/*
 * HistogramRGB.cpp
 *
 *  Created on: Dec 14, 2016
 *      Author: adrien
 */


//#include "Image.hpp"
#include "HistogramRGB.hpp"



HistogramRGB::HistogramRGB(const Image<PixelRGB>& subject)
: Image<PixelRGB>(512, 600, 255, "histogram"+subject.GetName())
{
	// Controls that max intensity is not above 255, otherwise it creates a copy of
	// the subject and rescale it
	Image<PixelRGB> good_subject(subject);
	if (subject.MaxI() > 255)
	{
		good_subject.Rescale();
	}

	// Computes the max number of pixels that have the same intensity for each channel
	int greatest_pop_dist0=good_subject.GreatestPopDist(0);
	int greatest_pop_dist1=good_subject.GreatestPopDist(1);
	int greatest_pop_dist2=good_subject.GreatestPopDist(2);

	// Computes the ratio that scale the max intensity such that the max peak of the
	// histogram reaches (4/5) of the height.
	int single_1plot=200;
	double ratio0=0.8*(double)single_1plot/(double)greatest_pop_dist0;
	double ratio1=0.8*(double)single_1plot/(double)greatest_pop_dist1;
	double ratio2=0.8*(double)single_1plot/(double)greatest_pop_dist2;

	// Red part of histogram, lowest one
	int pixels_to_fill;
	int col;
	mdistributionR=good_subject.ComputeDistribution(0);
	for(int i=0; i<256; i++)
	{
		pixels_to_fill=(int)((double)mdistributionR[i]*ratio0);
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
	mdistributionG=good_subject.ComputeDistribution(1);
	for(int i=0; i<256; i++)
	{
		pixels_to_fill=(int)((double)mdistributionG[i]*ratio1);
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
	mdistributionB=good_subject.ComputeDistribution(2);
	for(int i=0; i<256; i++)
	{
		pixels_to_fill=(int)((double)mdistributionB[i]*ratio2);
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


/// Method that returns the distribution for a specified channel
std::vector<int> HistogramRGB::GetDistribution(const int& channel) const
{
	// Check that the channel is allowed
	if (channel < 0 or channel >=3)
	{
		throw ErrorChannel(mspectra);
	}

	if (channel==0)
	{
		return mdistributionR;
	}
	if (channel==1)
	{
		return mdistributionG;
	}
	else
	{
		return mdistributionB;
	}
}

