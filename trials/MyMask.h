#ifndef MASK_H
#define MASK_H

#include "image_tools.h"


class MyMask
{
private:
  std::vector<std::vector<double> > _mask;
  unsigned int _nx;
  unsigned int _ny;

public:

  MyMask(const std::vector<std::vector<double> >& mask);

  cimg_library::CImg<double> apply(const cimg_library::CImg<double>& img);



};

#endif
