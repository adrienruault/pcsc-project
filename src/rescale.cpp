#include <iostream>
#include "digital_filter.h"


using namespace cimg_library;

int main()
{

  CImg<double> img("../ressources/lena.jpg");

  double max = img.max();
  std::cout << max << std::endl;
  //img *= 255/max;

  //img.save("scaled_zlena.jpg");
  return 0;
}
