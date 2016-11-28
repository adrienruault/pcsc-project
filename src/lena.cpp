#include <iostream>
#include "CImg.h"
#include <cstdio>
#include <jpeglib.h>
#include <jerror.h>

using namespace cimg_library;

int main()
{


	CImg<double> image("../resources/ruault.jpg");

	CImg<double> copy(image);

	/*std::cout << copy.width() << copy.height() << copy.depth() <<  copy.spectrum() << copy.atXYZC(5,100,0,0,0) << '\n';
	std::cout << copy.operator()(5,500);*/

	for (size_t x = 0; x < copy.width(); x++) {
		for (size_t y = 0; y < copy.height(); y++) {
			for (size_t c = 0; c < 1; c++) {
				if (copy.operator()(x,y,0,c) < 70)
				{
					copy.operator()(x,y,0,c) = 255-((255-70)/(70))*copy.operator()(x,y,0,c);
				}
			}


		}
	}
	copy.save("Nina_red.jpg");
	return 0;
}
