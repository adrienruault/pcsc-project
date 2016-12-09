#include "MyMask.h"


using namespace cimg_library;

int main()
{

  double a = 16.0*16.0;

  std::vector<double> a1 {1/a,4/a,6/a,4/a,1/a};
  std::vector<double> a2 {4/a,16/a,24/a,16/a,4/a};
  std::vector<double> a3 {6/a,24/a,36/a,24/a,6/a};
  std::vector<double> a4 {1/a,4/a,6/a,4/a,1/a};
  std::vector<double> a5 {4/a,16/a,24/a,16/a,4/a};

  std::vector<std::vector<double> > matrice {a1,a2,a3,a4,a5};

  MyMask m(matrice);

  CImg<double> filtered = m.apply(CImg<double>("../resources/lena.jpg"));

  for (size_t i = 0; i < 100; i++) {
    filtered = m.apply(filtered);
  }

  filtered.save("../resources/lena_maskedx100.jpg");

  /*int a = 512;

  CImg<double> img(add_mirror_boundary(CImg<double>("../resources/ruault.jpg"),577,577,960,960));

  img.save("../resources/ruault_mirror.jpg");*/


  return 0;

}
