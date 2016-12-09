#ifndef DIGITAL_FILTER_H
#define DIGITAL_FILTER_H

#include <iostream>
#include "CImg.h"
#include <cstdio>
#include <jpeglib.h>
#include <jerror.h>

class TD_filter
{
private:
  cimg_library::CImg<double> _h;
  cimg_library::CImg<double> _H;

public:



};

cimg_library::CImg<double> z_transform(const cimg_library::CImg<double>& img);

#endif
