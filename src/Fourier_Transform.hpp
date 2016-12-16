#ifndef FOURIER_TRANSFORM_HPP
#define FOURIER_TRANSFORM_HPP

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
  Fourier_Transform( const std::vector< std::vector<ComplexNumber > >&  vec);
  Fourier_Transform( const std::vector<std::vector< std::vector<ComplexNumber > > >&  vec);

  void Display() const;
  //I shift_zero_to_center(const I& img) const; // now in Image class

  I getArgument() const;
  I getModulus() const;
  I getimPart() const;
  I getrealPart() const;
  double getimPart(int i, int j, int c = 0) const;
  double getrealPart(int i, int j, int c = 0) const;

  std::vector<ComplexNumber> fft_1D(const std::vector<ComplexNumber>& signal);


};

template<typename I>
I Fourier_Transform<I>::getrealPart() const
{
  return realPart;
}

/// This function is the algorithm for the fft in one dimension.
/// It is called by the constructor of the Fourier_Transform class
/// to compute the fourier transform of both the rows and the columns
/// of the image passed as argument of the constructor.
template<typename I>
std::vector<ComplexNumber> Fourier_Transform<I>::fft_1D(const std::vector<ComplexNumber>& signal)
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
  //        :realPart(img.Width(),img.Height()), imPart(img.Width(),img.Height()),
    //       modulus(img.Width(),img.Height()), argument(img.Width(),img.Height())
{
  int N1 = img.Width();
  int N2 = img.Height();
  int c = img.GetSpectra();


  realPart = I(N1,N2);
  imPart = I(N1,N2);
  modulus = I(N1,N2);
  argument = I(N1,N2);

  for (size_t b = 0; b < c; b++) {

    std::vector<ComplexNumber> qq(N2,0);
    std::vector< std::vector<ComplexNumber> > q(N1, qq);
    for (size_t i = 0; i < N1; i++) {
      for (size_t j = 0; j < N2; j++) {
        q[i][j] = ComplexNumber(img(i,j,b));
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
        realPart(i,j,b) = GetRealPart(q[i][j]);
        imPart(i,j,b) = GetImaginaryPart(q[i][j]);
        modulus(i,j,b) = q[i][j].CalculateModulus();
        argument(i,j,b) = q[i][j].CalculateArgument();
      }
    }

  }
  realPart.shift_zero_to_center();
  imPart.shift_zero_to_center();
  modulus.shift_zero_to_center();
  argument.shift_zero_to_center();
}

/// Construct a Fourier_Transform of Image<PixelBW>
/// Usefull for the Filter class
template<typename I>
Fourier_Transform<I>::Fourier_Transform( const std::vector< std::vector<ComplexNumber > >&  vec)
{

  // TODO : Gestion d'erreur. Useful constructor ?

  int N1 = vec.size();
  int N2 = vec[0].size();
  argument = Image<PixelBW>(N1,N2);
  modulus = Image<PixelBW>(N1,N2);
  realPart = Image<PixelBW>(N1,N2);
  imPart = Image<PixelBW>(N1,N2);
  for (int x = 0; x < N1; x++) {
    for (int y = 0; y < N2; y++) {
      realPart(x,y) = vec[x][y].GetRealPart();
      imPart(x,y) = vec[x][y].GetImaginaryPart();
      modulus(x,y) = vec[x][y].CalculateModulus();
      argument(x,y) = vec[x][y].CalculateArgument();
    }
  }
}

/// Construct a Fourier_Transform of Image<PixelRGB>
/// Usefull for the Filter class
template<typename I>
Fourier_Transform<I>::Fourier_Transform( const std::vector<std::vector< std::vector<ComplexNumber > > >&  vec)
{
  int N1 = vec.size();
  int N2 = vec[0].size();
  int nc = vec[0][0].size();
  argument = Image<PixelRGB>(N1,N2);
  modulus = Image<PixelRGB>(N1,N2);
  realPart = Image<PixelRGB>(N1,N2);
  imPart = Image<PixelRGB>(N1,N2);
  for (size_t c = 0; c < nc; c++) {
    for (int x = 0; x < N1; x++) {
      for (int y = 0; y < N2; y++) {
        realPart(x,y,c) = vec[x][y][c].GetRealPart();
        imPart(x,y,c) = vec[x][y][c].GetImaginaryPart();
        modulus(x,y,c) = vec[x][y][c].CalculateModulus();
        argument(x,y,c) = vec[x][y][c].CalculateArgument();
      }
    }
  }
}


/// This method displays the modulus of the Fourier_Transform, with a log scale,
/// and the zero frequence centered.
template<typename I>
void Fourier_Transform<I>::Display() const
{
  (modulus.log_Rescale()).Display();
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
double Fourier_Transform<I>::getimPart(int i, int j, int c) const
{
  return imPart(i,j,c);
}

template<typename I>
double Fourier_Transform<I>::getrealPart(int i, int j, int c) const
{
  return realPart(i,j,c);
}





#endif
