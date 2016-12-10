/*
 * pixel_bracket_test.cpp
 *
 *  Created on: Dec 10, 2016
 *      Author: adrien
 */

#include <iostream>
#include "PixelBW.hpp"


int main(int argc, char* argv[])
{
	PixelBW a(100);

	std::cout << a[0] << "\n";

	a[0]=10;

	std::cout << a[0] << "\n";


	return 0;
}
