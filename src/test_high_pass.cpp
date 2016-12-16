/** This test creates a High Pass Filter and apply it on lena
(512x512 BW). It first makes the filtering in the frequency domain
(multiplication with the fourier transform of lena), then it does
a convolution in the space domain, to show that we obtain the same result **/

#include <iostream>
#include "Filter.hpp"

int main(int argc, char* argv[])
{
  Image<PixelBW> img("../resources/lenaBW.jpg");
  img.Display("Original image of lena");

  /// We construct a high pass Filter indicating the size of the images
  /// we want to filter with it. We precise that we want a high pass Filter
  /// passing the string "HP" in argument. The third argument is
  /// the cutoff frequency and the 4th argument is the sharpness
  /// of the cut.
  Filter HP(512,512,"HP",60,40);

  Fourier_Transform<Image<PixelBW > > ft(img);
  ft.Display("fourier transform modulus of lena before filtering");
  Fourier_Transform<Image<PixelBW > > HPft = HP.Apply(ft);
  HPft.Display("fourier transform modulus of lena after high pass filtering");

  Image< PixelBW > HPimg(HPft);
  HPimg.Display("reconstructed lena after filtering in the Fourier Domain");



  Image<PixelBW> HPimg2(HP.Apply(img));
  HPimg2.Display("lena filtered directly in the space domain with a convolution");
  /// Here we save the two filtered image so that we can compare them.
  /// To be sure of the result of the display after saving,
  /// which will not done with ImageMagic, we use our method rescale
  /// to put the values of the pixels between 0 and 255.
  (HPimg.RescaledCopy()).Save("../resources/lenaHPinfourier.jpg");
  (HPimg2.RescaledCopy()).Save("../resources/lenaHPinspace.jpg");


  return 0;
}
