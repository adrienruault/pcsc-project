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


/// Defining exception class to handle a channel error in PixelBW and PixelRGB
class ErrorChannel : public std::exception
{
private:
	std::string mphrase;
public:
	ErrorChannel() throw()
	{
		mphrase="ERROR: the channel index is not allowed\n";
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
	ErrorFormat(std::string const& format) throw()
	{
		std::string test_string1="BW";
		if (test_string1.compare(format) == 0)
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


#endif /* SRC_ERROR_HPP_ */
