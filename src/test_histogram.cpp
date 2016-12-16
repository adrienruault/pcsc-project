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
	// Histogram for lena
	try
	{
		// For a black and white image
		Image<PixelBW> lenaBW("../resources/lenaBW.jpg");
		//lenaBW.CreateDistribution();
		HistogramBW histoBW(lenaBW);
		histoBW.Display();
		histoBW.Save("../histo_lenaBW.jpg");
	}
	catch(std::exception const& e)
	{
		std::cerr << e.what();
	}

	// We now set all the intensities to 30 for this black and white image and then
	// display the histogram of the image to show a peak at abscissa that represents
	// 30 of intensity
	for(int i=0; i<lenaBW.Width(); i++)
	{

	}




	try
	{
		// For a RGB image
		Image<PixelRGB> lenaRGB("../resources/lenaRGB.jpg");
		//lenaRGB.CreateDistribution();
		HistogramRGB histoRGB(lenaRGB);
		histoRGB.Display();
		histoRGB.Save("histo_lenaRGB.jpg");
	}
	catch(std::exception const& e)
	{
		std::cerr << e.what();
	}




	return 0;
}
