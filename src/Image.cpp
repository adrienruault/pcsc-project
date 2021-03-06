#include "Image.hpp"
#include "Fourier_Transform.hpp"

using namespace cimg_library;


template<typename P>
Image<P>::Image(const int& width, const int& height, const double& intensity /*=0*/, const std::string& name /*="undefined.jpg"*/)
{
	if (typeid(P)==typeid(PixelBW))
	{
		mspectra=1;
	}
	else if (typeid(P)==typeid(PixelRGB))
	{
		mspectra=3;
	}
	else
	{
		throw ErrorPixelType();
	}

	mname=name;

	// Definition of dimensions attributes (initialized to 100 pixels by default)
	mwidth=width;
	mheight=height;

	/*
	// Image dimension:
	mPmatrix.reserve(mwidth);
	for (int i=0; i<mwidth; i++)
	{
		mPmatrix[i].reserve(mheight);
	}
	*/

	for (int i=0; i<mwidth; i++)
	{
		mPmatrix.push_back(std::vector<P>(mheight));
		for (int j=0; j<mheight; j++)
		{
			// Set channels to 0 intensity
			for(int c=0; c<mspectra; c++)
			{
				mPmatrix[i][j][c]=intensity;
			}
		}
	}
}


template <typename P>
Image<P>::Image(const std::string& name)
{
	// In the future: try to implement a control on the string name
	// to verify that it is a JPG file
	if (typeid(P)==typeid(PixelBW))
	{
		mspectra=1;
	}
	else if (typeid(P)==typeid(PixelRGB))
	{
		mspectra=3;
	}
	else
	{
		throw ErrorPixelType();
	}

	mname=name;

	// Convert name which is a string into a const char* to pass it in CImg
	const char* char_name = name.c_str();
	CImg<double> img(char_name);

	// Check that the spectrum of the opened image coincide with that of Pixel type
	if (img.spectrum()!=mspectra)
	{
		throw ErrorFormat(mspectra);
	}

	// Check that the image is effectively 2D which means its depth is 1
	if (img.depth()!=1)
	{
		throw Error3DImage();
	}

	// Get the dimensions of the image
	mwidth=img.width();
	mheight=img.height();

	/*
	mPmatrix.reserve(mwidth);
	// Reserve the memory necessary for mPmatrix that contains the pixels of the image
	for (int i=0; i<mwidth; i++)
	{
		mPmatrix[i].reserve(mheight);
	}
	*/

	// Transfer Black and White intensities of the image into the matrix
	// Please be careful that the indexing corresponds to the IP convention
	for (int i=0; i<mwidth; i++)
	{
		mPmatrix.push_back(std::vector<P>(mheight));
		for (int j=0; j<mheight; j++)
		{
			// Copy pixels intensity
			for(int c=0; c<mspectra; c++)
			{
				mPmatrix[i][j][c]=img(i,j,0,c);
			}
		}
	}

	/*
	if (compute_distrib=="yes")
	{
		// Computation of the distribution array
		// Initialisation at 0

		for(int c=0; c<mspectra; c++)
		{
			mdistribution.push_back(std::vector<int>(257,0));
		}

		// Filling of mdistribution
		for(int i=0; i<mwidth; i++)
		{
			for(int j=0; j<mheight; j++)
			{
				for(int c=0; c<mspectra; c++)
				{
					int k=mPmatrix[i][j][c];
					mdistribution[c][k]+=1;
				}
			}
		}

		// Last element set to 1 signals that mdistribution[c] is up-to-date
		for(int c=0; c<mspectra; c++)
		{
			mdistribution[c][256]=1;
		}
	}
	else
	{
		//mdistribution.reserve(mspectra);
		for(int c=0; c<mspectra; c++)
		{
			mdistribution.push_back(std::vector<int>(1,0));
		}
	}
	*/
}


template <typename P>
Image<P>::Image(const std::vector<std::vector<double> > intensity_array)
{

	if (typeid(P)==typeid(PixelBW))
	{
		mspectra=1;
	}
	else if (typeid(P)==typeid(PixelRGB))
	{
		mspectra=3;
	}
	else
	{
		throw ErrorPixelType();
	}

	mname="undefined";

	// Definition of dimensions attributes (initialized to 100 pixels by default)
	mwidth=intensity_array.size();
	mheight=intensity_array[0].size();



	for (int i=0; i<mwidth; i++)
	{
		mPmatrix.push_back(std::vector<P>(mheight));
		for (int j=0; j<mheight; j++)
		{
			// Set channels to 0 intensity
			for(int c=0; c<mspectra; c++)
			{
				mPmatrix[i][j][c]=intensity_array[i][j];
			}
		}
	}


	/*
	//mdistribution.reserve(mspectra);
	for(int c=0; c<mspectra; c++)
	{
		mdistribution.push_back(std::vector<int>(1,0));
	}
	*/
}



template <typename P>
Image<P>::Image(const Image<P>& image_to_copy)
{
	mspectra=image_to_copy.mspectra;
	mname=image_to_copy.mname;
	mwidth=image_to_copy.mwidth;
	mheight=image_to_copy.mheight;

	mPmatrix=image_to_copy.mPmatrix;
	//mdistribution=image_to_copy.mdistribution;
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

template <typename P>
Image<P>::Image(const Fourier_Transform<Image<P > >& fft )
{
	int N1 = (fft.getrealPart()).Width();
	int N2 = (fft.getrealPart()).Height();
	Image<P> im = fft.getimPart();
	Image<P> real  = fft.getrealPart();
	im.shift_zero_to_center();
	real.shift_zero_to_center();

	Image<P> img(N1,N2,im.GetSpectra());

	for (int c = 0; c < im.GetSpectra(); c++) {

  	std::vector<ComplexNumber> qq(N1,0);
  	std::vector< std::vector<ComplexNumber> > q(N2, qq);
  	for (size_t i = 0; i < N1; i++) {
    	for (size_t j = 0; j < N2; j++) {
      	q[i][j] = ComplexNumber(real(i,j,c),im(i,j,c));
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
        	img(i,j,c) = q[i][j].GetRealPart();
      	//img(i,j) = q[i][j].GetImaginaryPart();
    	}
  	}

  	//img.shift_zero_to_center();
	}
	(*this) = img;
}


template <typename P>
double& Image<P>::operator()(const int& x, const int& y, const int& channel /*=0*/)
{
	if ((0<=x and x<mwidth) and (0<=y and y<mheight))
	{
		// Last element of mdistribution set to 0 signals that the array might be out-dated
		// Controls that the channel is allowed
		if (channel < 0 or channel >= mspectra)
		{
			throw ErrorChannel(mspectra);
		}
		/*
		// checking if mdistribution has been computed
		if(mdistribution[channel].size()==257)
		{
			mdistribution[channel][256]=0;
		}
		*/
		return mPmatrix[x][y][channel];
	}
	else
	{
		throw ErrorDimensions(x,y);
	}
}



template <typename P>
const double& Image<P>::operator()(const int& x, const int& y, const int& channel /*=0*/) const
{
	if ((0<=x and x<mwidth) and (0<=y and y<mheight))
	{
		return mPmatrix[x][y][channel];
	}
	else
	{
		throw ErrorDimensions(x,y);
	}
}



template<typename P>
int Image<P>::Width() const
{
	return mwidth;
}



template<typename P>
int Image<P>::Height() const
{
	return mheight;
}



template<typename P>
void Image<P>::SetName(const std::string& new_name)
{
	mname=new_name;
}

template<typename P>
std::string Image<P>::GetName() const
{
	return mname;
}


template<typename P>
int Image<P>::GetSpectra() const
{
	return mspectra;
}


/// Method that displays an image to the screen.
/// The idea is to convert our Pixel matrix in the format of the CImg library to be able
/// to use its facilities to display the image to the screen
template<typename P>
void Image<P>::Display() const
{
	// Declare image using CImg library
	CImg<double> img(mwidth,mheight,1,mspectra,0);

	// Transfer of the pixel value intensity
	for (int i=0; i<mwidth; i++)
	{
		for (int j=0; j<mheight; j++)
		{
			for(int c=0; c<mspectra; c++)
			{
				img(i,j,0,c)=mPmatrix[i][j][c];
			}
		}
	}

	// Convert mname which is a string in const char*
	const char* char_name = mname.c_str();
	CImgDisplay disp_img(img,char_name);
	// Seems to be mandatory to wait for the user to close
	//the displayed image to keep going
	while (!disp_img.is_closed())
	{
		disp_img.wait();
	}
	img = CImg<double>();
}


template<typename P>
void Image<P>::Display(const std::string& save_name) const
{
	// Declare image using CImg library
	CImg<double> img(mwidth,mheight,1,mspectra,0);

	// Transfer of the pixel value intensity
	for (int i=0; i<mwidth; i++)
	{
		for (int j=0; j<mheight; j++)
		{
			for(int c=0; c<mspectra; c++)
			{
				img(i,j,0,c)=mPmatrix[i][j][c];
			}
		}
	}

	// Convert mname which is a string in const char*
	const char* char_name = save_name.c_str();
	CImgDisplay disp_img(img,char_name);
	// Seems to be mandatory to wait for the user to close
	//the displayed image to keep going
	while (!disp_img.is_closed())
	{
		disp_img.wait();
	}
}


template<typename P>
void Image<P>::Save() const
{
	// Declare image using CImg library
	CImg<double> img(mwidth,mheight,1,mspectra,0);

	// Transfer of the pixel value intensity
	for (int i=0; i<mwidth; i++)
	{
		for (int j=0; j<mheight; j++)
		{
			for(int c=0; c<mspectra; c++)
			{
				img(i,j,0,c)=mPmatrix[i][j][c];
			}
		}
	}
	// Convert mname which is a string in const char*
	const char* char_name = mname.c_str();
	img.save(char_name);
}


template<typename P>
void Image<P>::Save(const std::string& save_name) const
{
	// Declare image using CImg library
	CImg<double> img(mwidth,mheight,1,mspectra,0);

	// Transfer of the pixel value intensity
	for (int i=0; i<mwidth; i++)
	{
		for (int j=0; j<mheight; j++)
		{
			for(int c=0; c<mspectra; c++)
			{
				img(i,j,0,c)=mPmatrix[i][j][c];
			}
		}
	}

	// Convert mname which is a string in const char*
	const char* char_name = save_name.c_str();
	img.save(char_name);
}


template<typename P>
void Image<P>::SetI(const double& new_intensity)
{
	for(int i=0; i<mwidth; i++)
	{
		for(int j=0; j<mheight; j++)
		{
			mPmatrix[i][j][0]=new_intensity;
		}
	}
	/*
	// Last element signals that mdistribution is out-dated
	for(int c=0; c<mspectra; c++)
	{
		mdistribution[c][256]=0;
	}
	*/
}


template <typename P>
std::vector<int> Image<P>::ComputeDistribution(const int& channel /*=0*/) const
{
	if (channel < 0 or channel >= mspectra)
	{
		throw ErrorChannel(mspectra);
	}

	// Controls that the maximum intensity is not above 255
	double max_intensity=(*this).MaxI();
	if (max_intensity>255)
	{
		throw ErrorDistribution("too_high_intensity");
	}

	// Reassign the mdistribution vector so that it has dimension 256 and 0 value
	std::vector<int> distribution(256,0);

	// Calculation of distribution
	for(int i=0; i<mwidth; i++)
	{
		for(int j=0; j<mheight; j++)
		{
			int k=mPmatrix[i][j][channel];
			distribution[k]+=1;

		}
	}
	return distribution;
}

/*
/// Method that sends the distribution of the channel provided in argument
template <typename P>
std::vector<int> Image<P>::GetDistribution(const int& channel */ /*=0*//*) const
{
	// Controls if the distribution is computed
	if (mdistribution[channel].size() != 257)
	{
		throw ErrorDistribution("not_computed");
	}

	// Controls that the channel is allowed
	if (channel < 0 or channel >= mspectra)
	{
		throw ErrorChannel(mspectra);
	}
	if (mdistribution[channel][256] != 1)
	{
		// too_high_intensity / not_computed / out-dated
		throw ErrorDistribution("out-dated");
	}
	return mdistribution[channel];
}
*/

/// Method that updates the distribution array for a particular channel provided in
/// argument.
/// If the distribution is not computed, call CreateDistribution() to compute it
/*
template<typename P>
void Image<P>::UpdateDistribution(const int& channel */ /*=0*/ /*)
{
	if (channel < 0 or channel >= mspectra)
	{
		throw ErrorChannel(mspectra);
	}

	//MaxI() for which channel?
	if(Image<P>::MaxI()>255)
	{
		throw ErrorDistribution("too_high_intensity");
	}

	if (mdistribution[channel].size() !=257)
	{
		throw ErrorDistribution("not_computed");
	}

	// Resetting mdistribution to 0
	for(int i=0; i<256; i++)
	{
		mdistribution[channel][i]=0;
	}

	// Filling of mdistribution
	for(int i=0; i<mwidth; i++)
	{
		for(int j=0; j<mheight; j++)
		{
			int k=mPmatrix[i][j][channel];
			mdistribution[channel][k]+=1;
		}
	}

	// Last element signals that mdistribution is up-to-date:
	mdistribution[channel][256]=1;
}
*/


template<typename P>
double Image<P>::MaxI() const
{
	double max=-std::numeric_limits<double>::infinity();;
	for(int i=0; i<mwidth; i++)
	{
		for(int j=0; j<mheight; j++)
		{
			for(int c=0; c<mspectra; c++)
			{
				if (mPmatrix[i][j][c] > max)
				{
					max=mPmatrix[i][j][c];
				}
			}
		}
	}
	return max;
}


template<typename P>
double Image<P>::MinI() const
{
	double min=std::numeric_limits<double>::infinity();
	for(int i=0; i<mwidth; i++)
	{
		for(int j=0; j<mheight; j++)
		{
			for(int c=0; c<mspectra; c++)
			{
				if (mPmatrix[i][j][c] < min)
				{
					min=mPmatrix[i][j][c];
				}
			}
		}
	}
	return min;
}


template<typename P>
void Image<P>::Rescale()
{
	double max_intensity = Image<P>::MaxI();
	double min_intensity = Image<P>::MinI();
	double factor=(double)255/(max_intensity-min_intensity);

	int relay;
	for(int i=0; i<mwidth; i++)
	{
		for(int j=0; j<mheight; j++)
		{
			for(int c=0; c<mspectra; c++)
			{
				relay=(mPmatrix[i][j][c]-min_intensity)*factor;
				mPmatrix[i][j][c]=relay;
			}
		}
	}
}



template<typename P>
Image<P> Image<P>::RescaledCopy() const
{
	Image<P> subject(*this);
	subject.Rescale();

	return subject;
}


template<typename P>
Image<P> Image<P>::log_Rescale() const
{
	Image<P> img(Width(),Height(),GetSpectra());
	for (size_t c = 0; c < GetSpectra(); c++) {
		for (size_t i = 0; i < Width(); i++) {
			for (size_t j = 0; j < Height(); j++) {
				if ((*this)(i,j,c) < 1 ) {img(i,j,c) = 0;}
				else {img(i,j,c) = log((*this)(i,j,c));}
			}
		}
	}
	img.Rescale();
	return img;
}



template <typename P>
int Image<P>::GreatestPopDist(const int& channel /*=0*/) const
{
	// Check if the channel request is allowed
	if (channel < 0 or channel >= mspectra)
	{
		throw ErrorChannel(mspectra);
	}
	/*
	// Check if distribution has been computed
	if (mdistribution[channel].size() != 257)
	{
		// too_high_intensity / not_computed / out-dated
		throw ErrorDistribution("not_computed");
	}


	// Check if distribution is up-to-date
	if (mdistribution[channel][256] != 1)
	{
		// too_high_intensity / not_computed / out-dated
		throw ErrorDistribution("out-dated");
	}
	*/

	std::vector<int> distribution=(*this).ComputeDistribution(channel);

	int greatest_pop=0;
	for(int i=0; i<256; i++)
	{
		if (distribution[i]>greatest_pop)
		{
			greatest_pop=distribution[i];
		}
	}
	return greatest_pop;
}


template<typename P>
Image<P> Image<P>::AddMirrorBoundary(const int& left, const int& right, const int& top, const int& bot) const
{
  Image<P> output(left+Image::Width()+right, top+Image::Height()+bot);

  int img_width = Image::Width();
  int img_height = Image::Height();

  for (size_t x = 0; x < output.Width(); x++) {
    for (size_t y = 0; y < output.Height(); y++) {
      int i;
      int j;
      if (x < left)
      {
    	  i = left-x-1;
      }
      else if (x >= (left + img_width))
      {
    	  i = -1+img_width-(x-(left+img_width));
      }
      else
      {
    	  i = x-left;
      }
      if (y < top)
      {
    	  j = top-y-1;
      }
      else if (y >= top + img_height)
      {
    	  j =  -1+img_height-(y-(top+img_height));
      }
      else
      {
    	  j = y-top;
      }
			for (size_t c = 0; c < GetSpectra(); c++) {
      	output(x,y,c) = (*this)(i,j,c);
			}
      //if (x<100 and y<50) output(x,y) = 0;
    }
  }
  return output;
}


template<typename P>
void Image<P>::shift_zero_to_center()
{
  int N1 = Width();
  int N2 = Height();
	int nc = GetSpectra();
  Image<P> img_shifted(N1,N2);
	for (size_t c = 0; c < nc; c++) {
		for (size_t i = 0; i < N1; i++) {
			for (size_t j = 0; j < N2; j++) {
				img_shifted(((N1/2)+i)%N1,((N2/2)+j)%N2,c) = (*this)(i,j,c);
			}
		}
	}


	(*this) = img_shifted;

}

template class Image<PixelBW>;
template class Image<PixelRGB>;
