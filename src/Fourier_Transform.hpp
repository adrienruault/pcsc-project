#ifndef FOURIER_TRANSFORM_HPP
#define FOURIER_TRANSFORM_HPP

#include "ComplexNumber.hpp"
#include "Image.hpp"

/// This class contains the results of the computation of the Fourier Transform.
/// This result is stocked in 4 images : 2 images representing the Imaginary
/// part and the Real part of the transform, and 2 others representing
/// the modulus and the argument.
template<typename I>
class Fourier_Transform
{
private:
  I argument;
  I modulus;
  I imPart;
  I realPart;

public:
  Fourier_Transform( const I& img);

  void Display() const;
  I shift_zero_to_center(const I& img) const;

  I getArgument() const;
  I getModulus() const;
  I getimPart() const;
  I GetrealPart() const;


};

/// This function is the algorithm for the fft in one dimension.
/// It is called by the constructor of the Fourier_Transform class
/// to compute the fourier transform of both the rows and the columns
/// of the image passed as argument of the constructor.
std::vector<ComplexNumber> fft_1D(const std::vector<ComplexNumber>& signal)
{

  // TODO : verify if the image is squared with dimensions 2^n*2^m

  int n = signal.size();
  if (n == 1) return signal;
  else {
    std::vector<ComplexNumber> signaleven(n/2);
    std::vector<ComplexNumber> signalodd(n/2);
    for (size_t i = 0; i < n; i+=2) {
      signaleven[i/2] = signal[i];
      signalodd[i/2] = signal[i+1];
    }
    std::vector<ComplexNumber> Feven = fft_1D(signaleven);
    std::vector<ComplexNumber> Fodd = fft_1D(signalodd);

    std::vector<ComplexNumber> signalcombined(n,0);
    for (size_t i = 0; i < n/2; i++) {
      signalcombined[i] = Feven[i] + ComplexNumber(cos(2*M_PI*i/n),-sin(2*M_PI*i/n))*Fodd[i];
      signalcombined[i+n/2] = Feven[i] - ComplexNumber(cos(2*M_PI*i/n),-sin(2*M_PI*i/n))*Fodd[i];
    }
    return signalcombined;
  }
}




/// Compute the Fourier Transform of an image BW or RGB and constructs
/// a Fourier_Transform object.
template<typename I>
Fourier_Transform<I>::Fourier_Transform( const I& img)
          :realPart(img.Width(),img.Height()), imPart(img.Width(),img.Height()),
           modulus(img.Width(),img.Height()), argument(img.Width(),img.Height())
{
  int N1 = img.Width();
  int N2 = img.Height();

  realPart = I(N1,N2,0);
  imPart = I(N1,N2,0);
  modulus = I(N1,N2,0);
  argument = I(N1,N2,0);


  std::vector<ComplexNumber> qq(N2,0);
  std::vector< std::vector<ComplexNumber> > q(N1, qq);
  for (size_t i = 0; i < N1; i++) {
    for (size_t j = 0; j < N2; j++) {
      q[i][j] = ComplexNumber(img(i,j));
    }
  }

  for (int y = 0; y < N2; ++y) {
    setRow(q,fft_1D(getRow(q,y)),y);
  }

  for (int x = 0; x < N1; x++) {
    setColumn(q,fft_1D(getColumn(q,x)),x);
  }

  for (size_t i = 0; i < N1; i++) {
    for (size_t j = 0; j < N2; j++) {
      realPart(i,j) = GetRealPart(q[i][j]);
      imPart(i,j) = GetImaginaryPart(q[i][j]);
      modulus(i,j) = q[i][j].CalculateModulus();
      argument(i,j) = q[i][j].CalculateArgument();
    }
  }
}

/// This method shifts the zero frequence of an image contained in the
/// Fourier_Transform class to the center of this image.
template<typename I>
I Fourier_Transform<I>::shift_zero_to_center(const I& img) const
{
  int N1 = img.Width();
  int N2 = img.Height();
  I img_mirror(img.AddMirrorBoundary(N1/2,0,N2/2,0));
  I img_shifted(N1,N2,0);
  for (size_t x = 0; x < N1 ; x++) {
    for (size_t y = 0; y < N2; y++) {
      img_shifted(x,y) = img_mirror(x,y);
    }
  }
  return img_shifted;
}

/// This method displays the modulus of the Fourier_Transform, with a log scale,
/// and the zero frequence centered.
template<typename I>
void Fourier_Transform<I>::Display() const
{
  shift_zero_to_center(modulus.log_Rescale()).Display();
}

template<typename I>
I Fourier_Transform<I>::getArgument() const
{
  return argument;
}

template<typename I>
I Fourier_Transform<I>::getModulus() const
{
  return modulus;
}

template<typename I>
I Fourier_Transform<I>::getimPart() const
{
  return imPart;
}

template<typename I>
I Fourier_Transform<I>::GetrealPart() const
{
  return realPart;
}



#endif
