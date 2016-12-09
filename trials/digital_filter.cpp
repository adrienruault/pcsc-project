#include "digital_filter.h"
#include <cmath>

using namespace cimg_library;

CImg<double> z_transform(const CImg<double>& img)
{



  std::cout << "ok3" << std::endl;
  CImg<double> imgtrans(11,11,1,1);
  std::cout << "ok4" << std::endl;
  for (int z1 = 0; z1 < 11; z1++) {
    std::cerr << z1;
    for (int z2 = 0; z2 < 11; z2++) {
      imgtrans.operator()(z1,z2,0,0) = 0;
      for (size_t x = 0; x < img.width(); x++) {
        for (size_t y = 0; y < img.height(); y++) {
          imgtrans(z1,z2,0,0) += img(x,y,0,0)*pow(z1-5,-x+img.width()/2)*pow(z2-5,-y+img.height()/2);
        }
      }

    }
  }
  return imgtrans;
}
