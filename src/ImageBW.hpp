/*
 * ImageBW.hpp
 *
 *  Created on: Nov 30, 2016
 *      Author: adrien
 */

#ifndef SRC_IMAGEBW_HPP_
#define SRC_IMAGEBW_HPP_

#include <iostream>
#include <vector>

#include "Image.hpp"
#include "PixelBW.hpp"



class ImageBW : public Image
{
private:
	/// mPmatrix is a matrix containing the pixels of the image
	std::vector<std::vector<PixelBW> > mPmatrix;

	/// mdistribution contains the number of PixelBW associated to each intensity
	std::vector<int> mdistribution;
public:
	ImageBW(const int& width, const int& height, const double& intensity, const std::string& name="undefined.jpg");
	ImageBW(const std::string& name);

	double& operator()(const int& x, const int& y, const int& channel);
	const double& operator()(const int& x, const int& y, const int& channel) const;

	void UpdateDistribution();
	int MostPopI();
	double MaxI() {return 0;}
	double MinI() {return 0;}
	void Display() const;
	void Save() const;
	void Save(const std::string& save_name) const;
	void SetI(const double& new_intensity);
	void Histogram(Image& histo, const std::string& histo_name);
};



#endif /* SRC_IMAGEBW_HPP_ */
