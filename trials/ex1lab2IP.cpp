#include <iostream>
#include "CImg.h"
#include <cstdio>
#include <jpeglib.h>
#include <jerror.h>
#include <cmath>

using namespace cimg_library;

int main()
{
  CImg<double> img("../resources/lena.jpg");
  CImg<double> img2(img);
  double a = 0;
  for (size_t i = 0; i < img.width(); i++) {
    for (size_t j = 0; j < img.height(); j++) {
      img2(i,j) = 0;
      for (size_t k = 0; k < j; k++) {
        img2(i,j) += pow(a,k)*img(i-k,j);
      }
    }
  }

  img2.save("../resources/lenafiltered0.jpg");

  return 0;

}
