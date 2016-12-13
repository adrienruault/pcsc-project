/*
 * Error.hpp
 *
 *  Created on: Dec 10, 2016
 *      Author: adrien
 */

#ifndef SRC_ERROR_HPP_
#define SRC_ERROR_HPP_

#include <exception>
#include <iostream>
#include <sstream>
#include <string>


class ErrorPixelType : public std::exception
{
private:
	std::string mphrase;
public:
	ErrorPixelType() throw()
	{
		mphrase="ERROR: wrong Pixel type for Image template, try PixelBW or PixelRGB\n";
	}

	virtual const char* what() const throw()
	{
		return mphrase.c_str();
	}
	virtual ~ErrorPixelType() throw()
	{}
};


class Error3DImage : public std::exception
{
private:
	std::string mphrase;
public:
	Error3DImage() throw()
	{
		mphrase="ERROR: trying to open 3D image which is not allowed\n";
	}

	virtual const char* what() const throw()
	{
		return mphrase.c_str();
	}
	virtual ~Error3DImage() throw()
	{}
};


/// Defining exception class to handle a channel error in PixelBW and PixelRGB
class ErrorChannel : public std::exception
{
private:
	std::string mphrase;
public:
	ErrorChannel(const int& spectra) throw()
	{
		if (spectra==1)
		{
			mphrase="ERROR: the channel index is not 0 for BW Image\n";
		}
		else
		{
			mphrase="ERROR: the channel index is not 0, 1 or 2 for RGB Image\n";
		}
	}

	virtual const char* what() const throw()
	{
		return mphrase.c_str();
	}
	virtual ~ErrorChannel() throw()
	{}
};


/// Defining exception class to ensure that there is no attempt to reach a Pixel that is
/// out of bounds
class ErrorDimensions : public std::exception
{
private:
	std::string mphrase;
public:
	ErrorDimensions(const int x, const int y) throw()
	{
		/*
		std::string x_coor;
		std::ostringstream convert1;
		convert1 << x;
		x_coor=convert1.str();

		std::string y_coor;
		std::ostringstream convert2;
		convert2 << y;
		y_coor=convert2.str();

		mphrase="ERROR: Pixel with index: (" + x_coor + "," + y_coor + ") is out of bounds\n";
		*/
		mphrase="ERROR: trying to reach a Pixel which is out of bound\n";
	}

	virtual const char* what() const throw()
	{
		return mphrase.c_str();
	}
	virtual ~ErrorDimensions() throw()
	{}
};


/// Exception class which ensures that the image format
/// is conformed when opening a JPEG file
/// It is used to verify that an opened image as ImageBW has only one color
/// and to verify that an opened image as ImageRGB has exactly 3 colors
class ErrorFormat : public std::exception
{
private:
	std::string mphrase;
public:
	ErrorFormat(const int& spectra) throw()
	{
		std::string test_string1="BW";
		if (spectra==1)
		{
			mphrase="ERROR: trying to open an image that is not Black and White through ImageBW class\n";
		}
		else
		{
			mphrase="Error: trying to open an image that is not RGB through ImageRGB class\n";
		}
	}

	virtual const char* what() const throw()
	{
		return mphrase.c_str();
	}
	virtual ~ErrorFormat() throw()
	{}
};


/// Exception that prevents from calculating the distribution if intensity is above 255
class ErrorIntensity : public std::exception
{
private:
	std::string mphrase;
public:
	ErrorIntensity() throw()
	{
		mphrase="ERROR: trying to compute distribution with intensity above 255, try to rescale\n";
	}

	virtual const char* what() const throw()
	{
		return mphrase.c_str();
	}
	virtual ~ErrorIntensity() throw()
	{}
};


/// Exception that prevents from using intensity distribution if not computed
class ErrorDistribution : public std::exception
{
private:
	std::string mphrase;
public:
	// Constructor that takes 3 possible arguments and throws different exception
	// according to their nature:
	// too_high_intensity / not_computed / out-dated
	ErrorDistribution(const std::string& type) throw()
	{
		if (type=="too_high_intensity")
		{
			mphrase="ERROR: trying to compute distribution with intensity above 255, try to rescale\n";
		}
		else if (type=="not_computed")
		{
			mphrase="ERROR: trying to use distribution which is not computed\n";
		}
		else if (type=="out-dated")
		{
			mphrase="ERROR: trying to use distribution which is out-dated";
		}
		else
		{
			mphrase="ERROR: invalid attempt to use distribution";
		}
	}

	virtual const char* what() const throw()
	{
		return mphrase.c_str();
	}
	virtual ~ErrorDistribution() throw()
	{}
};


#endif /* SRC_ERROR_HPP_ */
