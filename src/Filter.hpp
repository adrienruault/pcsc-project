#ifndef FILTER_HPP
#define FILTER_HPP

#include "Fourier_Transform.hpp"

class Filter
{
private:
  /// Represents the values of the filter in the frequency domain.
  std::vector< std::vector< ComplexNumber> > fourierFilter;

  /// Represents the values of the filter in the space domain.
  std::vector< std::vector< double > > realFilter;

public:
  /// Constructs a filter with :
  /// - the dimensions of the images (width and height) we want to process with this filter
  /// - the type of filter we want to create (high pass = "HP",low pass = "LP", band pass = "BP")
  /// - the cut off value(s) ; for example a high pass with cut off value of 40 will put to zero all
  ///   the frequencies in a radius of 40 pixels from the center (0 frequency) of the processed image.
  ///   For a band pass, we need two cut off values to know under which and above which value we cut.
  /// - The sharpness of the cut. It has to be large enough to avoid gibbs effects but small enough to not
  ///   overlap the area of action of the filter, especially for band pass filter.
  Filter(int width, int height, const std::string& type, double cut_off, double sharpness, double cut_off_2=0);

  /// Apply the filter in the Fourier domain of an image BW.
  /// It take as an argument directly the fourier transform of the image and returns
  /// the resultant fourier transform (allows to see the action of the filter in frequency domain
  /// before going back to space domain to get the resultant filtered image).
  /// This application is faster than the application in the space domain, but it generates
  /// some small boundaries effects around the image.
  Fourier_Transform<Image<PixelBW> > Apply(const Fourier_Transform<Image<PixelBW> >& ft) const;

  /// Apply the filter in the Fourier domain of an image RGB.
  Fourier_Transform<Image<PixelRGB> > Apply(const Fourier_Transform<Image<PixelRGB> >& ft) const;

  /// Apply the filter in the space domain (for Image RGB and BW)
  /// The results are better than in the frequency domain, in particular thanks to
  /// the mirror boundaries we can add with the Image class, but it takes more time for computation.
  /// Since we limit the size of the influence of our convolution to 31 to not have even longer
  /// time of computation, we may lose some filtering at very low frequencies, but the overall result
  /// should be similar.
  Image<PixelBW> Apply(const Image<PixelBW>& img ) const;
  Image<PixelRGB> Apply(const Image<PixelRGB>& img ) const;

  /// Returns the filter in the frequency domain as a Fourier_Transform type.
  Fourier_Transform<Image<PixelBW> > getFilterFT() const;



};

#endif
