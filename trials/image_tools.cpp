#include "image_tools.h"

using namespace cimg_library;

CImg<double> add_mirror_boundary(const CImg<double>& img,int left, int right, int top, int bot)
{
  CImg<double> output(left + img.width() +right, top + img.height() + bot );
  for (size_t x = 0; x < output.width(); x++) {
    for (size_t y = 0; y < output.height(); y++) {
      //std ::cerr << "ok";
      int i;
      int j;
      if (x < left) {i = left-x-1;}
      else if (x >= (left + img.width())) {i = -1+img.width()-(x-(left+img.width()));}
      else {i = x-left;}
      if (y < top) {j = top-y-1;}
      else if (y >= top + img.height()) {j =  -1+img.height()-(y-(top+img.height()));}
      else {j = y-top;}
      output(x,y) = img(i,j);
      //if (x<100 and y<50) output(x,y) = 0;
    }
  }

  return output;


}
