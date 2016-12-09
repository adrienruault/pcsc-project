#include <iostream>
#include "digital_filter.h"


using namespace cimg_library;

int main()
{

  CImg<double> img("zlena.jpg");

  double max = img.max();
  std::cout << max << std::endl;
  //img *= 255/max;

  for (size_t x = 0; x < img.width(); x++) {
    for (size_t y = 0; y < img.height(); y++) {
      if (img(x,y) > 0)
      {
        std::cout << x << " " << y << " : " << img(x,y) << std::endl;
      }

    }
  }

  //img.save("scaled_zlena.jpg");
  return 0;
}
