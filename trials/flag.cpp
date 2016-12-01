#include <iostream>
#include "CImg.h"
#include <cstdio>
#include <jpeglib.h>
#include <jerror.h>

using namespace cimg_library;

int main()
{
  CImg<double> blue("Nina_blue.jpg");
  CImg<double> white("Nina_solarized.jpg");
  CImg<double> red("Nina_red.jpg");

  CImg<double> flag(3*blue.width(),blue.height(),1,3);

  int w = blue.width();

  for (size_t x = 0; x <  blue.width(); x++) {
    for (size_t y = 0; y < blue.height(); y++) {
      for (size_t c = 0; c < 3; c++) {
        flag.operator()(x,y,0,c) = blue.operator()(x,y,0,c);
        flag.operator()(x+blue.width(),y,0,c) = white.operator()(x,y,0,c);
        flag.operator()(x+2*blue.width(),y,0,c) = red.operator()(x,y,0,c);
      }


    }
  }

  flag.save("Nina_flag.jpg");

return 0;
}
