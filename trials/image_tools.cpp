#include "image_tools.h"

using namespace cimg_library;

CImg<double> add_mirror_boundary(const CImg<double>& img,int left, int right, int top, int bot)
{
  CImg<double> output(left + img.width() +right, top + img.height() + bot );
  for (size_t x = 0; x < output.width(); x++) {
    for (size_t y = 0; y < output.height(); y++) {
      //std ::cerr << "ok";
      int i;
      int j;
      if (x < left) {i = left-x-1;}
      else if (x >= (left + img.width())) {i = -1+img.width()-(x-(left+img.width()));}
      else {i = x-left;}
      if (y < top) {j = top-y-1;}
      else if (y >= top + img.height()) {j =  -1+img.height()-(y-(top+img.height()));}
      else {j = y-top;}
      output(x,y) = img(i,j);
      //if (x<100 and y<50) output(x,y) = 0;
    }
  }

  return output;


}


fourier_transform compute_dft(const cimg_library::CImg<double>& img)
{
  fourier_transform dft;
  dft.modulus = CImg<double>(img.width(),img.height());
  dft.argument = CImg<double>(img.width(),img.height());
  int N1 = img.width();
  int N2 = img.height();
  for (int x = -N1/2; x < N1/2; x++) {
    std::cerr << x;
    for (int y = -N2/2; y < N2/2; y++) {
      //ComplexNumber q(0);
      double qreal(0);
      double qim(0);
      for (int i = 0; i < img.width(); i++) {
        for (int j = 0; j < img.height(); j++) {
          //q += ComplexNumber(img(i,j)*cos(-2*M_PI*((1.0*x*i/(N1))+(1.0*y*j/(N2)))),
          //                  img(i,j)*sin(-2*M_PI*((1.0*x*i/(N1))+(1.0*y*j/(N2)))));
          qreal += img(i,j)*cos(-2*M_PI*((1.0*x*i/N1)+(1.0*y*j/N2)));
          qim += img(i,j)*sin(-2*M_PI*((1.0*x*i/N1)+(1.0*y*j/N2)));


        }
      }
      dft.modulus(x+img.width()/2,y+img.height()/2) = ComplexNumber(qreal,qim).CalculateModulus();
      dft.argument(x+img.width()/2,y+img.height()/2) = ComplexNumber(qreal,qim).CalculateArgument();
      dft.realPart(x+img.width()/2,y+img.height()/2) = qreal;
      dft.imPart(x+img.width()/2,y+img.height()/2) = qim;
    }
  }
  return dft;
}

fourier_transform compute_dft_for_reconstr(const cimg_library::CImg<double>& img)
{
  fourier_transform dft;
  dft.realPart = CImg<double>(img.width(),img.height());
  dft.imPart = CImg<double>(img.width(),img.height());
  int N1 = img.width();
  int N2 = img.height();
  for (int x = 0; x < N1; x++) {
    std::cerr << x;
    for (int y = 0; y < N2; y++) {
      //ComplexNumber q(0);
      double qreal(0);
      double qim(0);
      for (int i = 0; i < img.width(); i++) {
        for (int j = 0; j < img.height(); j++) {
          //q += ComplexNumber(img(i,j)*cos(-2*M_PI*((1.0*x*i/(N1))+(1.0*y*j/(N2)))),
          //                  img(i,j)*sin(-2*M_PI*((1.0*x*i/(N1))+(1.0*y*j/(N2)))));
          qreal += img(i,j)*cos(-2*M_PI*((1.0*x*i/N1)+(1.0*y*j/N2)));
          qim += img(i,j)*sin(-2*M_PI*((1.0*x*i/N1)+(1.0*y*j/N2)));


        }
      }
      //dft.modulus(x,y) = q.CalculateModulus();
      //dft.argument(x,y) = q.CalculateArgument();
      dft.realPart(x,y) = qreal;
      dft.imPart(x,y) = qim;
    }
  }
  return dft;
}

CImg<double> generate_rect(int N)
{
  CImg<double> img(N,N);
  int M = 8;
  for (size_t x = 0; x < N; x++) {
    for (size_t y = 0; y < N; y++) {
      if (abs((x-N/2)/M) < 0.5 and abs((y-N/2)/M) < 0.5 ) {
        img(x,y) = 255;
      } else {
        img(x,y) = 0;
      }

    }
  }
  return img;
}

CImg<double> inverse_dft(const fourier_transform& dft)
{
  CImg<double> img(dft.realPart.width(),dft.imPart.height());
  int N1 = img.width();
  int N2 = img.height();
  for (int x = 0; x < N1; x++) {
    std::cerr << x;
    for (int y = 0; y < N2; y++) {
      ComplexNumber q(0);
      for (int i = 0 ; i < N1 ; i++) {
        for (int j = 0; j < N2; j++) {
        //    q += ComplexNumber(1.0*dft.modulus(i,j)*cos(1.0*dft.argument(i,j)),
        //      1.0*dft.modulus(i,j)*sin(1.0*dft.argument(i,j)))  *((1.0/(N1*N2)))
        //      *ComplexNumber(cos(2.0*M_PI*((1.0*i*x/N1)+(1.0*j*y/N2))),sin(2.0*M_PI*((1.0*i*x/N1)+(1.0*j*y/N2))));

          q+= ComplexNumber(dft.realPart(i,j),dft.imPart(i,j))*((1.0/(N1*N2)))
               *ComplexNumber(cos(2.0*M_PI*((1.0*i*x/N1)+(1.0*j*y/N2))),sin(2.0*M_PI*((1.0*i*x/N1)+(1.0*j*y/N2))));
        }
      }
      //std::cerr << " : " << q << std::endl;
      img(x,y) = GetRealPart(q);
    }
  }
  return img;
}

std::vector<ComplexNumber> fft_1D(const std::vector<ComplexNumber>& signal)
{
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

std::vector<ComplexNumber> fft_1D_inv(const std::vector<ComplexNumber>& signal)
{
  int n = signal.size();
  if (n == 1) return signal;
  else {
    std::vector<ComplexNumber> signaleven(n/2);
    std::vector<ComplexNumber> signalodd(n/2);
    for (size_t i = 0; i < n; i+=2) {
      signaleven[i/2] = signal[i];
      signalodd[i/2] = signal[i+1];
    }
    std::vector<ComplexNumber> Feven = fft_1D_inv(signaleven);
    std::vector<ComplexNumber> Fodd = fft_1D_inv(signalodd);

    std::vector<ComplexNumber> signalcombined(n,0);
    for (size_t i = 0; i < n/2; i++) {
      signalcombined[i] = (1.0/2)*(Feven[i] + ComplexNumber(cos(2*M_PI*i/n),sin(2*M_PI*i/n))*Fodd[i]);
      signalcombined[i+n/2] = (1.0/2)*(Feven[i] - ComplexNumber(cos(2*M_PI*i/n),sin(2*M_PI*i/n))*Fodd[i]);
    }
    return signalcombined;
  }
}


fourier_transform compute_fft(const cimg_library::CImg<double>& img)
{
  int N1 = img.width();
  int N2 = img.height();

  fourier_transform fft;
  fft.realPart = CImg<double>(N1,N2);
  fft.imPart = CImg<double>(N1,N2);
  fft.modulus = CImg<double>(N1,N2);
  fft.argument = CImg<double>(N1,N2);


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
      fft.realPart(i,j) = GetRealPart(q[i][j]);
      fft.imPart(i,j) = GetImaginaryPart(q[i][j]);
      fft.modulus(i,j) = q[i][j].CalculateModulus();
      fft.argument(i,j) = q[i][j].CalculateArgument();
    }
  }
  return fft;
}

CImg<double> compute_inv_fft(const fourier_transform& fft)
{
  int N1 = fft.realPart.width();
  int N2 = fft.realPart.height();

  CImg<double> img(N1,N2);

  std::vector<ComplexNumber> qq(N1,0);
  std::vector< std::vector<ComplexNumber> > q(N2, qq);
  for (size_t i = 0; i < N1; i++) {
    for (size_t j = 0; j < N2; j++) {
      q[i][j] = ComplexNumber(fft.realPart(i,j),fft.imPart(i,j));
    }
  }

  for (int x = 0; x < N1; x++) {
    setColumn(q,fft_1D_inv(getColumn(q,x)),x);
  }

  for (int y = 0; y < N2; y++) {
    setRow(q, fft_1D_inv(getRow(q,y)),y);
  }

  for (size_t i = 0; i < N1; i++) {
    for (size_t j = 0; j < N2; j++) {
        img(i,j) = q[i][j].GetRealPart();
      //img(i,j) = q[i][j].GetImaginaryPart();
    }
  }
  return img;
}
