#ifndef FILTER_HPP
#define FILTER_HPP

#include "Fourier_Transform.hpp"

class Filter
{
private:
  std::vector< std::vector< ComplexNumber> > fourierFilter;
  std::vector< std::vector< double > > realFilter;

public:
  //Filter(const std::vector< std::vector < ComplexNumber > >& flt );
  Filter(int width, int height, const std::string& type, double cutoff, double sharpness);

  Fourier_Transform<Image<PixelBW> > Apply(const Fourier_Transform<Image<PixelBW> >& ft) const;
  Image<PixelBW> Apply(const Image<PixelBW>& img ) const;

  Fourier_Transform<Image<PixelBW> > getFilterFT() const;
  


};

#endif
