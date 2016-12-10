/*
 * main.cpp
 *
 *  Created on: Dec 2, 2016
 *      Author: adrien
 */

#include <iostream>
#include <iostream>

//#include "Image.hpp"
#include "CImg.h"
#include "ImageBW.hpp"
#include "ImageRGB.hpp"
#include "PixelBW.hpp"
#include "PixelRGB.hpp"

using namespace cimg_library;
using namespace std;

int main(int argc, char* argv[])
{
	try
	{
		ImageRGB img("lena.jpg");
		img.Display();
	}
	catch(std::exception const& e)
	{
		cerr << e.what();
	}






	/*
	ImageBW img("lena.jpg");
	img.Display();
	img.Save("test_of_saver.jpg");
	*/


	/*
	cout << img(2,2,0) << "\n";
	cout << img(511,40,0) << "\n";
	cout << img(2,2,0) << "\n";
	cout << img(2,2,0) << "\n";
	cout << img(2,2,0) << "\n";


	ImageBW trial(512,512,"this_is_a_test.jpg");
	for(int i=0; i<100; i++)
	{
		for(int j=0; j<500; j++)
		{
			try
			{
				trial(i,j,0)=255;
			}
			catch(std::exception const& e)
			{
				cerr << e.what() << "\n";
				abort();
			}
		}
	}


	trial.Display();
	trial.Save();

	*/







	/*
	PixelBW a(10.0);
	a.ChangeI(20.0);

	cout << "a intensity: " << a.GetI() << "\n";


	string name = "lena.jpg";
	const char* char_name = name.c_str();
	CImg<double> img(char_name);

	cout << "Lena intensity in (2,3): " << img(100,100) << "\n";

	CImgDisplay disp(img,char_name);
	while (!disp.is_closed())
	{
		disp.wait();
	}
	*/







	/*
	// Conversion of string to char *
	const char * char_name = name.c_str();
	CImg<double> img(char_name);
	CImgDisplay disp_img(img,char_name);
	while (!disp_img.is_closed())
	{
		disp_img.wait();
	}
	*/

}
