/*
 * main.cpp
 *
 *  Created on: Dec 2, 2016
 *      Author: adrien
 */

#include <iostream>
//#include "Image.hpp"
#include "CImg.h"
#include "ImageBW.hpp"
#include "PixelBW.hpp"

using namespace cimg_library;
using namespace std;

int main(int argc, char* argv[])
{
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


	ImageBW img("lena.jpg");
	img.Display();

	img.Save("test_of_saver.jpg");


	string name="len_std.jpg";

	cout << img(2,3);

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
