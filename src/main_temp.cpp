/*
 * main.cpp
 *
 *  Created on: Dec 2, 2016
 *      Author: adrien
 */


#include <iostream>
#include <vector>
#include <typeinfo>

//#include "Image.hpp"
#include "CImg.h"
//#include "Image.hpp""
#include "Fourier_Transform.hpp"
//#include "ImageBW.hpp"
//#include "ImageRGB.hpp"

#include "Image.hpp"
#include "PixelBW.hpp"
#include "PixelRGB.hpp"
#include "HistogramBW.hpp"
#include "HistogramRGB.hpp"

using namespace cimg_library;
using namespace std;

int main(int argc, char* argv[])
{

	/*
	Image<PixelBW> imgbw(100,100,0,"lourd");
	Image<PixelRGB> imgrgb(101,101,0);

	//cout << imgbw.Width() << "\n" << imgbw.Height() << "\n" << imgbw.GetName() << "\n";
	imgbw.SetName("BW1");
	//cout << imgbw.GetName() << "\n";

	//cout << imgrgb.Width() << "\n" << imgrgb.Height() << "\n" << imgrgb.GetName() << "\n";
	imgrgb.SetName("RGB1");
	//cout << imgrgb.GetName() << "\n";

	//cout << "\n\n";

	Image<PixelBW> imgbw2("lena.jpg");
	//cout << imgbw2.Width() << "\n" << imgbw2.Height() << "\n" << imgbw2.GetName() << "\n";
	//cout << imgbw2.GetName() << "\n";

	Image<PixelRGB> imgrgb2("len_std.jpg");
	//cout << imgrgb2.Width() << "\n" << imgrgb2.Height() << "\n" << imgrgb2.GetName() << "\n";
	//cout << imgrgb2.GetName() << "\n";

	//cout << "\n\n";

	//cout << imgbw2(5,5) << "\n" << imgbw2(5,5,0) << "\n";
	imgbw2(5,5)=0;
	cout << imgbw2(5,5) << "\n";
	try{
		cout << imgbw2(5,5,1) << "\n";
	}
	catch(std::exception const& e)
	{
		cerr << e.what();
	}
	try{
		cout << imgrgb2(5,5,3) << "\n";
	}
	catch(std::exception const& e)
	{
		cerr << e.what();
	}

	for(int c=0; c<imgrgb2.GetSpectra(); c++)
	{
		cout << imgrgb2(5,5,c) << "\t";
		imgrgb2(5,5,c)=0;
		cout << imgrgb2(5,5,c) << "\n";
	}

	cout << "\n\n";

	//imgbw2.Display();
	imgbw2.Save("black_white.jpg");
	imgbw2.SetName("new_bw2.jpg");
	imgbw2.Save();

	//imgrgb2.Display();
	imgrgb2.Save("RGB.jpg");
	imgrgb2.SetName("new_rgb2.jpg");
	imgrgb2.Save();

	// Compilation error here:
	//Image<int> img("len_std.jpg");

	try
	{
		Image<PixelBW> img_wrong_spectra("len_std.jpg");
	}
	catch(std::exception const& e)
	{
		cerr << e.what();
	}

	*/
	/*
	Image<PixelBW> imgbw3(100,50,0,"mdistribution_test.jpg");
	std::vector<int> k;
	k=imgbw3.GetDistribution();
	for(int i=0; i<imgbw3.Width(); i++)
	{
		for(int j=0; j<imgbw3.Height(); j++)
		{
			imgbw3(i,j)=i*j;
		}
	}
	std::cout << "Max intensity: " << imgbw3.MaxI() << "\n";
	double factor=(double)255/(4851.0);
	cout << "(double)255/(max_intensity): " << factor << "\n";
	int relay= factor * 4851.0;
	cout << "relay: " << relay << "\n";
	imgbw3.UpdateDistribution();
	k=imgbw3.GetDistribution();
	for(int i=0; i<257; i++)
	{
		cout << k[i] << "\n";
	}
	cout << imgbw3(3,3) << "\n" << "Length vec: " << k.size() << "\n";

	*/

/*
	Image<PixelBW> imglena("lena.jpg");

	HistogramBW histo(imglena);

	//histo.Display();

	cout << "\n\n";
	vector<int> dist;
	dist=imglena.GetDistribution();
	for (int i=0; i<257; i++)
	{
		cout << dist[i] << "\n";
	}

	cout << "Max is: " << imglena.MaxI() << "\n";

	cout << "Min is: " << imglena.MinI() << "\n";


	try
	{
		Image<PixelRGB> imglen_std("len_std.jpg");
		HistogramRGB histoRGB(imglen_std);
		histoRGB.Display();
	}
	catch(std::exception const& e)
	{
		cerr << e.what();
	}


	*/

	// Add mirror boundary

	Image<PixelRGB> lenacolor("len_std.jpg");
	lenacolor.Display();

	Image<PixelBW> lena("lena.jpg");

	lena.Display();

	Image<PixelBW> boundary=lena.AddMirrorBoundary(100,100,100,100);

	boundary.Display();

	/*
	vector<vector<int> > caca;
	cout << caca.size();
	*/


	Image<PixelBW> imglena("lena.jpg");
	Fourier_Transform<Image<PixelBW> > lena_fourier(imglena);
	lena_fourier.Display();



	return 0;
}
