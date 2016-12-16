#ifndef FILTER_HPP
#define FILTER_HPP

#include "Fourier_Transform.hpp"

class Filter
{
private:
  std::vector< std::vector< ComplexNumber> > fourierFilter;
  std::vector< std::vector< double > > realFilter;

public:
  Filter(int width, int height, const std::string& type, double cut_off, double sharpness, double cut_off_2=0);

  Fourier_Transform<Image<PixelBW> > Apply(const Fourier_Transform<Image<PixelBW> >& ft) const;
  Fourier_Transform<Image<PixelRGB> > Apply(const Fourier_Transform<Image<PixelRGB> >& ft) const;
  Image<PixelBW> Apply(const Image<PixelBW>& img ) const;
  Image<PixelRGB> Apply(const Image<PixelRGB>& img ) const;

  Fourier_Transform<Image<PixelBW> > getFilterFT() const;



};

#endif
