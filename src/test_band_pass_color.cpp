/** This test creates a Band Pass Filter and apply it on lena
(512x512 RGB). It first makes the filtering in the frequency domain
(multiplication with the fourier transform of lena), then it does
a convolution in the space domain, to show that we obtain the same result **/

#include <iostream>
#include "Filter.hpp"

int main(int argc, char* argv[])
{
  Image<PixelRGB> img("../resources/lenaRGB.jpg");
  img.Display("Original image of lena");

  /// We construct a band pass Filter indicating the size of the images
  /// we want to filter with it. We precise that we want a band pass Filter
  /// passing the string "BP" in argument. The third argument is
  /// the first cutoff frequency (the lowest), the 4th argument is the sharpness
  /// of the cut and the 5th argument is the second cutoff frequency (the highest).
  /// However, you have to be careful about the values you put for your cutoff and your sharpness
  /// so that they do not overlap each others.
  Filter BP(512,512,"BP",30,20,100 );

  Fourier_Transform<Image<PixelRGB > > ft(img);
  ft.Display("fourier transform modulus of lena before filtering");
  Fourier_Transform<Image<PixelRGB > > BPft = BP.Apply(ft);
  BPft.Display("fourier transform modulus of lena after band pass filtering");

  Image< PixelRGB > BPimg(BPft);
  BPimg.Display("reconstructed lena after filtering in the Fourier Domain");



  Image<PixelRGB> BPimg2(BP.Apply(img));
  BPimg2.Display("lena filtered directly in the space domain with a convolution");
  /// Here we save the two filtered image so that we can compare them.
  /// To be sure of the result of the display after saving,
  /// which will not done with ImageMagic, we use our method rescale
  /// to put the values of the pixels between 0 and 255.
  (BPimg.RescaledCopy()).Save("../resources/lenaRGBBPinfourier.jpg");
  (BPimg2.RescaledCopy()).Save("../resources/lenaRGBBPinspace.jpg");


  return 0;
}
