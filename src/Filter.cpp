#include "Filter.hpp"

Filter::Filter(const std::vector< std::vector < ComplexNumber > >& flt )
              : fourierFilter(flt) {}

Image<PixelBW> Filter::Apply(const Fourier_Transform<Image<PixelBW > >& ft)
{
  int N1 = ft.getModulus().Width();
  int N2 = ft.getModulus().Height();

  std::vector< ComplexNumber > qq(N2,0);
  std::vector<std::vector < ComplexNumber > > q(N1,qq);
  for (size_t x = 0; x < N1; x++) {
    for (size_t y = 0; y < N2; y++) {
      q[x][y] = ComplexNumber(ft.getrealPart()(x,y), ft.getimPart()(x,y))*fourierFilter[x][y];
    }
  }

  return Image<PixelBW>(Fourier_Transform<Image<PixelBW > >(q));

}
