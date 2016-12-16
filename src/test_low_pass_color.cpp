/** This test creates a Low Pass Filter and apply it on lena
(512x512 RGB). It first makes the filtering in the frequency domain
(multiplication with the fourier transform of lena), then it does
a convolution in the space domain, to show that we obtain the same result **/

#include <iostream>
#include "Filter.hpp"

int main(int argc, char* argv[])
{
  Image<PixelRGB> img("../resources/lenaRGB.jpg");
  img.Display("Original image of lena");

  /// We construct a Filter low pass indicating the size of the images
  /// we want to filter with it. We precise that we want a low pass Filter
  /// passing the string "LP" in argument. The third argument is
  /// the cutoff frequency and the 4th argument is the sharpness
  /// of the cut.
  Filter LP(512,512,"LP",50,30);

  Fourier_Transform<Image<PixelRGB > > ft(img);
  ft.Display("fourier transform modulus of lena before filtering");
  Fourier_Transform<Image<PixelRGB > > LPft = LP.Apply(ft);
  LPft.Display("fourier transform modulus of lena after low pass filtering");

  Image< PixelRGB > LPimg(LPft);
  LPimg.Display("reconstructed lena after filtering in the Fourier Domain");


  Image<PixelRGB> LPimg2(LP.Apply(img));
  LPimg2.Display("lena filtered directly in the space domain with a convolution");
  /// Here we save the two filtered image so that we can compare them.
  /// To be sure of the result of the display after saving,
  /// which will not done with ImageMagic, we use our method rescale
  /// to put the values of the pixels between 0 and 255.
  (LPimg.RescaledCopy()).Save("../resources/lenaRGBLPinfourier.jpg");
  (LPimg2.RescaledCopy()).Save("../resources/lenaRGBLPinspace.jpg");


  return 0;
}
