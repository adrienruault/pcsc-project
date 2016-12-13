#include <iostream>
#include "image_tools.h"

using namespace cimg_library;

int main()
{
  // Test dft on rect
  /*CImg<double> rect(generate_rect(100));

  rect.save("../resources/rect.jpg");

  fourier_transform dft = compute_dft(rect);

  dft.modulus.save("../resources/sinc_modulus.jpg");

  dft.argument.save("../resources/sinc_argument.jpg");*/

  // Test dft on rect for reconstruction
  /*CImg<double> rect(generate_rect(100));

  rect.save("../resources/rect.jpg");

  fourier_transform dft = compute_dft_for_reconstr(rect);

  dft.modulus.save("../resources/rect_modulus.jpg");

  dft.argument.save("../resources/rect_argument.jpg");*/


  // Test dft on Lena
  /*CImg<double> img("../resources/lenalow.jpg");

  fourier_transform dft = compute_dft(img);

  dft.modulus.save("../resources/lena_modulus.jpg");
  dft.argument.save("../resources/lena_argument.jpg");*/

  // Test dft for reconstruction on Lena
  /*CImg<double> img("../resources/lenalow.jpg");

  fourier_transform dft = compute_dft_for_reconstr(img);

  dft.realPart.save("../resources/lena_realPart.jpg");
  dft.imPart.save("../resources/lena_imPart.jpg");*/

  // Test reconstruction rect
  //fourier_transform dft;
  //dft.modulus = CImg<double>("../resources/rect_modulus.jpg");
  //dft.argument = CImg<double>("../resources/rect_argument.jpg");

  //inverse_dft(dft).save("../resources/rect_reconstructed.jpg");

  // Test reconstruction lena
  /*fourier_transform dft;
  dft.realPart = CImg<double>("../resources/lena_realPart.jpg");
  dft.imPart = CImg<double>("../resources/lena_imPart.jpg");

  inverse_dft(dft).save("../resources/lena_reconstructed.jpg");*/


  // Test fft_1D and fft_1D_inv
  /*std::vector<ComplexNumber> signal(8,0);
  signal[1] += ComplexNumber(1,0);

  std::vector<ComplexNumber> fft(fft_1D(signal));
  for (size_t i = 0; i < fft.size(); i++) {
    std::cout << fft[i] << std::endl;
  }

  std::vector<ComplexNumber> fft_inv(fft_1D_inv(fft));
  for (size_t i = 0; i < fft.size(); i++) {
    std::cout << fft_inv[i] << std::endl;
  }*/

  // Test fft and fft inv on lena
  CImg<double> img("../resources/lena.jpg");
  fourier_transform fft = compute_fft(img);

  fft.realPart.save("../resources/fft_lena_realPart.jpg");
  fft.imPart.save("../resources/fft_lena_imPart.jpg");
  fft.modulus.save("../resources/fft_cecilia_modulus.jpg");
  fft.argument.save("../resources/fft_lena_argument.jpg");

  compute_inv_fft(fft).save("../resources/fft_lena_reconstructed.jpg");

  // Test fft and fft inv on rect
  /*CImg<double> img(generate_rect(512));
  img.save("../resources/rect512.jpg");
  fourier_transform fft = compute_fft(img);

  fft.realPart.save("../resources/fft_rect_realPart.jpg");
  fft.imPart.save("../resources/fft_rect_imPart.jpg");
  fft.modulus.save("../resources/fft_rect_modulus.jpg");
  fft.argument.save("../resources/fft_rect_argument.jpg");

  compute_inv_fft(fft).save("../resources/fft_rect_reconstructed.jpg");*/

  // Test fft and fft inv on values
  /*int n =8;
  CImg<double> img(n,n);
  img(0, 1) = 255;
  img(2,3) = 122;

  img.save("../resources/tesimage.jpg");


    for (size_t j = 0; j < n; j++) {
      for (size_t i = 0; i < n; i++) {
        std::cout << img(i,j) << " ";
      }
      std::cout  << '\n';
    }
  fourier_transform fft = compute_dft_for_reconstr(img);
  for (size_t j = 0; j < n; j++) {
    for (size_t i = 0; i < n; i++) {
      std::cout << ComplexNumber(fft.realPart(i,j),fft.imPart(i,j)) << " ";
    }
    std::cout  << '\n';
  }

  CImg<double> reconst = compute_inv_fft(fft);

  for (size_t j = 0; j < n; j++) {
    for (size_t i = 0; i < n; i++) {
      std::cout << reconst(i,j) << " ";
    }
    std::cout  << '\n';
  }*/


  // Test mask applied on Fourier
  /*double a = 16.0*16.0;

  std::vector<double> a1 {1/a,4/a,6/a,4/a,1/a};
  std::vector<double> a2 {4/a,16/a,24/a,16/a,4/a};
  std::vector<double> a3 {6/a,24/a,36/a,24/a,6/a};
  std::vector<double> a4 {1/a,4/a,6/a,4/a,1/a};
  std::vector<double> a5 {4/a,16/a,24/a,16/a,4/a};

  std::vector<std::vector<double> > matrice {a1,a2,a3,a4,a5};

  CImg<double> mask(512,512);
  CImg<double> img("../resources/lena.jpg");

  for (size_t i = 0; i < 5; i++) {
    for (size_t j = 0; j < 5; j++) {
      mask(i,j) = matrice[j][i];
    }
  }

  //CImg<double> mask_mirror_bound(add_mirror_boundary(mask,256,256,256,256));
  //CImg<double> img_mirror_bound(add_mirror_boundary(img,256,256,256,256));

  fourier_transform fftmask(compute_fft(mask));


  fftmask.modulus.save("../resources/mask_modulus.jpg");

  fourier_transform fftimg(compute_fft(img));
  for (size_t c = 0; c < 5  ; c++) {
    for (size_t i = 0; i < 512; i++) {
      for (size_t j = 0; j < 512; j++) {
      ComplexNumber q = ComplexNumber(fftmask.realPart(i,j),fftmask.imPart(i,j))*
                        ComplexNumber(fftimg.realPart(i,j),fftimg.imPart(i,j));
      fftimg.realPart(i,j) = q.GetRealPart();
      fftimg.imPart(i,j) = q.GetImaginaryPart();
      }
    }
  }

  compute_inv_fft(fftimg).save("../resources/lenafourierfilteredx100.jpg");*/

  // Test filtering in Fourier domain
  /*CImg<double> img("../resources/lena.jpg");
  fourier_transform fftimg(compute_fft(img));
  std::cout << fftimg.modulus(511,511) << '\n';

  for (size_t i = 0; i < 512; i++) {
    for (size_t j = 0; j < 512; j++) {
      int n = 1250  ;
      ComplexNumber q = ComplexNumber(fftimg.realPart(i,j),fftimg.imPart(i,j))*
                        ((i*i+j*j<n) or ((512-i)*(512-i)+j*j<n) or ((512-j)*(512-j)+i*i<n) or ((512-i)*(512-i)+(512-j)*(512-j)<n));
      fftimg.realPart(i,j) = q.GetRealPart();
      fftimg.imPart(i,j) = q.GetImaginaryPart();
    }
  }

  compute_inv_fft(fftimg).save("../resources/lenafourierlowpass.jpg");*/


  return 0;
}
