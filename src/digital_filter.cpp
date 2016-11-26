#include "digital_filter.h"
#include <cmath>

using namespace cimg_library;

CImg<double> z_transform(const CImg<double>& img)
{
  std::cout << "ok3" << std::endl;
  CImg<double> imgtrans(img.width(),img.height(),1,1);
  std::cout << "ok4" << std::endl;
  for (size_t z1 = 0; z1 < img.width(); z1++) {
    std::cout << z1;
    for (size_t z2 = 0; z2 < img.height(); z2++) {
      imgtrans.operator()(z1,z2,0,0) = 0;
      for (size_t x = 0; x < img.width(); x++) {
        for (size_t y = 0; y < img.height(); y++) {
          imgtrans.operator()(z1,z2,0,0) = img.operator()(x,y,0,0)*pow(z1,-x)*pow(z2,-y)*255;
        }
      }

    }
  }
  return imgtrans;
}
