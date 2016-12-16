/*
 * Test_Histogram.cpp
 *
 *  Created on: Dec 15, 2016
 *      Author: adrien
 */


#include "HistogramBW.hpp"
#include "HistogramRGB.hpp"

/// The idea of this test file is to show applications of the histogramBW and
/// histogramRGB classes that derive from the class template Image<PixelBW> and
/// Image<PixelRGB>.
/// These classes produce black an white or RGB histograms of the images that are
/// provided in argument of their constructor.
/// Histogram's constructor needs the pixel intensity to be rescaled so that the
/// intensity is not more than 255 for each channel
/// The abscissa of the plot represents the intensity ranging from 0 to 255 and the
/// ordinate represents the number of pixels associated to each intensity.
/// To show the well behavior of the feature we are going to display and save histograms
/// for lena pictures and then set all the intensity of the image to a certain value to
/// show a unique peak in the histograms.
int main(int argc, char* argv[])
{
	// Histogram for lenaBW
	Image<PixelBW> lenaBW("../resources/lenaBW.jpg");
	HistogramBW histoBW(lenaBW);
	histoBW.Display();

	// We now set all the intensities to 30 for this black and white image and then
	// display the histogram of the image to show a peak at abscissa that represents
	// 30 of intensity
	for(int i=0; i<lenaBW.Width(); i++)
	{
		for(int j=0; j<lenaBW.Height(); j++)
		{
			lenaBW(i,j)=30;
		}
	}

	HistogramBW histoBW30(lenaBW);
	histoBW30.Display();
	//histoBW30.Save("histo_lenaBW30.jpg");


	// Histogram for lenaRGB
	Image<PixelRGB> lenaRGB("../resources/lenaRGB.jpg");
	HistogramRGB histoRGB(lenaRGB);
	histoRGB.Display();

	// We now set all the intensities respectively to the Red, Blue and Green to 30, 60
	// and 90

	// Red channel
	for(int i=0; i<lenaRGB.Width(); i++)
	{
		for(int j=0; j<lenaRGB.Height(); j++)
		{
			lenaRGB(i,j,0)=30;
		}
	}
	HistogramRGB histoRGB30(lenaRGB);
	histoRGB30.Display();

	// Green part
	for(int i=0; i<lenaRGB.Width(); i++)
	{
		for(int j=0; j<lenaRGB.Height(); j++)
		{
			lenaRGB(i,j,1)=60;
		}
	}
	HistogramRGB histoRGB60(lenaRGB);
	histoRGB60.Display();

	// Blue part
	for(int i=0; i<lenaRGB.Width(); i++)
	{
		for(int j=0; j<lenaRGB.Height(); j++)
		{
			lenaRGB(i,j,2)=90;
		}
	}
	HistogramRGB histoRGB90(lenaRGB);
	histoRGB90.Display();



	return 0;
}
