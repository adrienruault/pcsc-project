/** This test creates a Low Pass Filter and apply it on lena
(512x512 BW). It first makes the filtering in the frequency domain
(multiplication with the fourier transform of lena), then it does
a convolution in the space domain, to show that we obtain the same result **/

#include <iostream>
#include "Filter.hpp"

int main(int argc, char* argv[])
{
  Image<PixelBW> img("../resources/lenaBW.jpg");
  img.Display("Original image of lena");

  /// We construct a Filter low pass indicating the size of the images
  /// we want to filter with it. We precise that we want a low pass Filter
  /// passing the string "LP" in argument. The third argument is
  /// the cutoff frequency and the 4th argument is the sharpness
  /// of the cut.
  Filter LP(512,512,"LP",50,30);

  Fourier_Transform<Image<PixelBW > > ft(img);
  ft.Display("fourier transform modulus of lena before filtering");
  Fourier_Transform<Image<PixelBW > > LPft = LP.Apply(ft);
  LPft.Display("fourier transform modulus of lena after low pass filtering");

  Image< PixelBW > LPimg(LPft);
  LPimg.Display("reconstructed lena after filtering in the Fourier Domain");



  Image<PixelBW> LPimg2(LP.Apply(img));
  LPimg2.Display("lena filtered directly in the space domain with a convolution");
  /// Here we save the two filtered image so that we can compare them.
  LPimg.Save("../resources/lenaLPinfourier.jpg");
  LPimg2.Save("../resources/lenaLPinspace.jpg");


  return 0;
}
