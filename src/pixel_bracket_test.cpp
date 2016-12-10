/*
 * pixel_bracket_test.cpp
 *
 *  Created on: Dec 10, 2016
 *      Author: adrien
 */

#include <iostream>
#include "PixelBW.hpp"
#include "ImageBW.hpp"


int main(int argc, char* argv[])
{

	{
	PixelBW a(100);
	std::cout << "Pixel bracket overloading test:\n" << a[0] << "\n";
	a[0]=10;
	std::cout << a[0] << "\n";
	}

	{
	ImageBW c(100,100);
	double b;
	double d;

	const int x=50;
	const int y=50;
	const int channel=0;

	b=c(x,y,channel);
	c(x,y,channel)=100.0;
	d=c(x,y,channel);
	std::cout << "Image parenthesis overloading test:\n" << b << "\n";
	std::cout << d << "\n";
	}









	return 0;
}
