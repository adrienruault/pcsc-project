#include <iostream>
#include "digital_filter.h"


using namespace cimg_library;

int main()
{
  CImg<double> image("../resources/lenalow.jpg");
  std::cout << "ok1" << std::endl;
	CImg<double> zlena(z_transform(image));

  std::cout << "ok2" << std::endl;

  zlena.save("zlena.jpg");
  
  return 0;

}
