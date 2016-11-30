#ifndef IMAGE_TOOLS_H
#define IMAGE_TOOLS_H

#include <iostream>
#include "CImg.h"
#include <cstdio>
#include <jpeglib.h>
#include <jerror.h>
#include <vector>


cimg_library::CImg<double> add_mirror_boundary(const cimg_library::CImg<double>& img,int top, int bot, int left, int right);


#endif
