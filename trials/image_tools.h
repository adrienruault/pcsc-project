#ifndef IMAGE_TOOLS_H
#define IMAGE_TOOLS_H

#include <iostream>
#include "CImg.h"
#include <cstdio>
#include <jpeglib.h>
#include <jerror.h>
#include <vector>
#include "ComplexNumber.hpp"
#include <cmath>

/// Structure containing both the module and the phase of a fourier transform of an image.
struct fourier_transform{
  cimg_library::CImg<double> modulus;
  cimg_library::CImg<double> argument;
  cimg_library::CImg<double> realPart;
  cimg_library::CImg<double> imPart;

};

cimg_library::CImg<double> add_mirror_boundary(const cimg_library::CImg<double>& img,int top, int bot, int left, int right);

fourier_transform compute_dft(const cimg_library::CImg<double>&);

cimg_library::CImg<double> generate_rect(int N);

cimg_library::CImg<double> inverse_dft(const fourier_transform& dft);

fourier_transform compute_dft_for_reconstr(const cimg_library::CImg<double>& img);

std::vector<ComplexNumber> fft_1D(const std::vector<ComplexNumber>& signal);

std::vector<ComplexNumber> fft_1D_inv(const std::vector<ComplexNumber>& signal);

fourier_transform compute_fft(const cimg_library::CImg<double>& img);

cimg_library::CImg<double> compute_inv_fft(const fourier_transform& fft);

#endif
