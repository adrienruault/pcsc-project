#include "Filter.hpp"


Filter::Filter( int width, int height, const std::string& type, double cut_off, double sharpness, double cut_off_2)
{
  if (type=="LP") {

	    //std::vector<std::vector<ComplexNumber> > tab;
	    // initialisation of tab to 0;
	    for(int i=0; i<width; i++)
	    {
		    fourierFilter.push_back(std::vector<ComplexNumber>(height));
	    }

	    double norm;
	    double x_coo;
	    double y_coo;

	    //for(int i=-width/2; i<width/2+1; i++)
	    for(int i=0; i<width; i++)
	    {
	       //for(int j=-height/2; j<height/2+1; j++)
		     for(int j=0; j<height; j++)
		     {
			        x_coo=i-(width/2);
			        y_coo=j-(height/2);
			        norm = sqrt(x_coo*x_coo+y_coo*y_coo);
			        if (norm < cut_off-sharpness)
			        {
				          fourierFilter[i][j]=ComplexNumber(1);
			        }
			        else if (norm > cut_off+sharpness)
			        {
				        fourierFilter[i][j]=ComplexNumber(0);
			        }
			        else
			        {
				         fourierFilter[i][j]=ComplexNumber(0.5*(1 - sin(M_PI*(norm-cut_off)/(2*sharpness))));
			        }
		     }
	    }
    }
    else if (type == "HP") {

    	for(int i=0; i<width; i++)
    	{
    		fourierFilter.push_back(std::vector<ComplexNumber>(height));
    	}


    	double norm;
    	double x_coo;
    	double y_coo;

    	//for(int i=-width/2; i<width/2+1; i++)
    	for(int i=0; i<width; i++)
    	{
    		//for(int j=-height/2; j<height/2+1; j++)
    		for(int j=0; j<height; j++)
    		{
    			x_coo=i-(width/2)+0.5;
    			y_coo=j-(height/2)+0.5;
    			norm = sqrt(x_coo*x_coo+y_coo*y_coo);
    			if (norm <= cut_off-sharpness)
    			{
    				fourierFilter[i][j]=ComplexNumber(0);
    			}
    			else if (norm >= cut_off+sharpness)
    			{
    				fourierFilter[i][j]=ComplexNumber(1);
    			}
    			else
    			{
    				fourierFilter[i][j]=ComplexNumber(1-0.5*(1 - sin(M_PI*(norm-cut_off)/(2*sharpness))));
    			}
    		}
    	}
    }
    else if (type=="BP") {

    	for(int i=0; i<width; i++)
    	{
    		fourierFilter.push_back(std::vector<ComplexNumber>(height));
    	}

    	double norm;
    	double x_coo;
    	double y_coo;

    	//for(int i=-width/2; i<width/2+1; i++)
    	for(int i=0; i<width; i++)
    	{
    		//for(int j=-height/2; j<height/2+1; j++)
    		for(int j=0; j<height; j++)
    		{
    			x_coo=i-(width/2)+0.5;
    			y_coo=j-(height/2)+0.5;
    			norm = sqrt(x_coo*x_coo+y_coo*y_coo);
    			if (norm <= cut_off-sharpness)
    			{
    				fourierFilter[i][j]=ComplexNumber(0);
    			}
    			else if (cut_off-sharpness < norm and norm < cut_off+sharpness)
    			{
    				fourierFilter[i][j]=ComplexNumber(1-0.5*(1 - sin(M_PI*(norm-cut_off)/(2*sharpness))));
    			}
    			else if (cut_off+sharpness <= norm and norm <= cut_off_2-sharpness)
    			{
    				fourierFilter[i][j]=ComplexNumber(1);
    			}
    			else if (cut_off_2-sharpness <= norm and norm <= cut_off_2+sharpness)
    			{
    				fourierFilter[i][j]=ComplexNumber(0.5*(1 - sin(M_PI*(norm-cut_off)/(2*sharpness))));
    			}
    			else
    			{
    				fourierFilter[i][j]=ComplexNumber(0);
    			}
    		}
    	}
    }

    Fourier_Transform<Image<PixelBW > > fft(fourierFilter);
    Image<PixelBW> img(fft);
    img.shift_zero_to_center();
    for (size_t x = 0; x < 31; x++) {
      realFilter.push_back(std::vector<double>(31,0));
      for (size_t y = 0; y < 31; y++) {
        realFilter[x][y] = img(x+(img.Width()/2)-15,y+(img.Height()/2)-15);
      }
    }

}

Image<PixelBW> Filter::Apply(const Image<PixelBW>& img ) const
{
  int nx = realFilter.size();
  int ny = realFilter[0].size();
  Image<PixelBW> bimg = img.AddMirrorBoundary((nx-1)/2,(nx-1)/2,(ny-1)/2,(ny-1)/2);
  Image<PixelBW> output(img);
  for (size_t x = 0; x < img.Width(); x++) {
    for (size_t y = 0; y < img.Height(); y++) {
      output(x,y) = 0;
      for (size_t i = 0; i < nx; i++) {
        for (size_t j = 0; j < ny; j++) {
          output(x,y) += realFilter[i][j]*bimg(x+i,y+j);
        }
      }
    }
  }
  return output;
}


Image<PixelRGB> Filter::Apply(const Image<PixelRGB>& img ) const
{
  int nx = realFilter.size();
  int ny = realFilter[0].size();
  Image<PixelRGB> bimg = img.AddMirrorBoundary((nx-1)/2,(nx-1)/2,(ny-1)/2,(ny-1)/2);
  Image<PixelRGB> output(img);
  for (size_t c = 0; c < img.GetSpectra(); c++) {
    for (size_t x = 0; x < img.Width(); x++) {
      for (size_t y = 0; y < img.Height(); y++) {
        output(x,y,c) = 0;
        for (size_t i = 0; i < nx; i++) {
          for (size_t j = 0; j < ny; j++) {
            output(x,y,c) += realFilter[i][j]*bimg(x+i,y+j,c);
          }
        }
      }
    }
  }
  return output;
}


Fourier_Transform< Image<PixelBW> > Filter::Apply(const Fourier_Transform<Image<PixelBW > >& ft) const
{
  int N1 = ft.getModulus().Width();
  int N2 = ft.getModulus().Height();

  std::vector< ComplexNumber > qq(N2,0);
  std::vector<std::vector < ComplexNumber > > q(N1,qq);
  for (size_t x = 0; x < N1; x++) {
    for (size_t y = 0; y < N2; y++) {
      q[x][y] = ComplexNumber(ft.getrealPart(x,y), ft.getimPart(x,y))*fourierFilter[x][y];
    }
  }

  return Fourier_Transform<Image<PixelBW > >(q);

}

Fourier_Transform<Image<PixelRGB> > Filter::Apply(const Fourier_Transform<Image<PixelRGB> >& ft) const
{
  int N1 = ft.getModulus().Width();
  int N2 = ft.getModulus().Height();

  std::vector <std::vector< ComplexNumber > > qq(N2,std::vector<ComplexNumber>(3));
  std::vector < std::vector<std::vector < ComplexNumber > > >q(N1,qq);
  for (size_t c = 0; c < 3; c++) {
    for (size_t x = 0; x < N1; x++) {
      for (size_t y = 0; y < N2; y++) {
        q[x][y][c] = ComplexNumber(ft.getrealPart(x,y,c), ft.getimPart(x,y,c))*fourierFilter[x][y];
      }
    }
  }

  return Fourier_Transform<Image<PixelRGB > >(q);
}


Fourier_Transform<Image<PixelBW> > Filter::getFilterFT() const
{
  return Fourier_Transform<Image<PixelBW > >(fourierFilter);
}
