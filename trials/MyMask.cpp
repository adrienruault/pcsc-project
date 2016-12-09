#include "MyMask.h"

using namespace cimg_library;

MyMask::MyMask(const std::vector<std::vector<double> >& mask)
          :_mask(mask),_nx(mask[0].size()),_ny(mask.size()) {}

CImg<double> MyMask::apply(const CImg<double>& img)
{
  CImg<double> bimg(add_mirror_boundary(img,(_nx-1)/2,(_nx-1)/2,(_ny-1)/2,(_ny-1)/2));
  CImg<double> output(img);
  for (size_t x = 0; x < img.width(); x++) {
    for (size_t y = 0; y < img.height(); y++) {
      output(x,y) = 0;
      for (size_t i = 0; i < _nx; i++) {
        for (size_t j = 0; j < _ny; j++) {
          output(x,y) += _mask[i][j]*bimg(x+i,y+j);
        }
      }
    }
  }
  return output;
}
