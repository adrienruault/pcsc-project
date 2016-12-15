#ifndef FILTER_HPP
#define FILTER_HPP

#include "Fourier_Transform.hpp"

class Filter
{
private:
  std::vector< std::vector< ComplexNumber> > fourierFilter;

public:
  Filter(const std::vector< std::vector < ComplexNumber > >& flt );

  Image<PixelBW> Apply(const Fourier_Transform<Image<PixelBW> >& ft);



};

#endif
