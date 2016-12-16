/**
This test takes the image of lena (512x512 RGB), apply the FFT on it,
then display the argument and the modulus (in log scale) of its Fourier
transform. Finally, it applies the operation of inverse fft on its
Fourier transform to come back to the original image of lena.
**/

#include<iostream>
#include "Fourier_Transform.hpp"
#include "Image.hpp"

int main(int argc, char* argv[])
{
  /// Here we instantiate an image from a jpg file
  Image<PixelRGB> img("../resources/lenaRGB.jpg");
  img.Display("Original image of lena");

  /// We instantiate an object "Fourier_Transform"
  /// which is constructed from an image.
  Fourier_Transform<Image<PixelRGB> > ft(img);
  ft.Display("modulus of lena fourier transform in log scale");
  ft.getArgument().Display("argument of lena fourier transform");

  Image<PixelRGB> img_reconstructed(ft);
  img_reconstructed.Display("lena reconstructed from its Fourier Transform");

  return 0;
}
