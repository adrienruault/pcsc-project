#include <iostream>
#include "CImg.h"
#include <cstdio>
#include <jpeglib.h>
#include <jerror.h>

using namespace cimg_library;

int main()
{
  CImg<double> blue("ruault_blue.jpg");
  CImg<double> white("ruault_solarized.jpg");
  CImg<double> red("ruault_red.jpg");

  CImg<double> flag(3*0.5*blue.width(),blue.height(),1,3);

  int w = blue.width();

  for (size_t x = 0; x < 0.5*blue.width(); x++) {
    for (size_t y = 0; y < blue.height(); y++) {
      for (size_t c = 0; c < 3; c++) {
        flag.operator()(x,y,0,c) = blue.operator()(x+0.25*w,y,0,c);
        flag.operator()(x+0.5*blue.width(),y,0,c) = white.operator()(x+0.25*w,y,0,c);
        flag.operator()(x+0.5*2*blue.width(),y,0,c) = red.operator()(x+0.25*w,y,0,c);




      }


    }
  }

  flag.save("ruault_flag.jpg");







return 0;
}
