/*
 * user.cpp
 *
 *  Created on: Dec 14, 2016
 *      Author: adrien
 */

#include <iostream>
#include <fstream>
#include <cmath>

#include "CImg.h"
#include "Filter.hpp"
#include "HistogramBW.hpp"
#include "HistogramRGB.hpp"

using namespace cimg_library;
using namespace std;

int main(int argc, char* argv[])
{
	std::string input;
	std::string image_input;
	std::string quit="NO";
	cout << "Hi! Welcome to your new Image Processing Tool!\n";
	cout << "First, let's try to open an image.\n";
	cout << "Please give me the name of a JPEG file present in the working directory:\n";
	cout << ">>";
	cin >> input;
	if (input!="quit")
	{
		image_input=input;
		ifstream file(image_input);
		if (!file.good() and quit=="NO")
		{
			cout << "\nI can't find the file, could you try another name?";
			cout << "\nI have to make you quit! Sorry ! \n";
			cout << "\n>>";
			return 0;
		}
		if (quit == "NO")
		{

			cout << "OK! You opened the file:" << image_input << "\n";
			int c(0);
			while(c!= 3 and c!=1)
			{
				cin.clear();
				cout << "But... I need your help : is this a colored or a greyscale image? Put 3 for color, 1 for black&white" << "\n";
				cin >> c;
			}
			cout << "Thank you ! Here is your image. " << "\n";
			if(c==1)
			{
				Image<PixelBW> img(image_input);
				img.Display();
				HistogramBW hist(img);
				std::cout << "Here is the Histogram of your image. Sweet isn't it?" << '\n';
				hist.Display();
				std::cout << "Now, it's time to go in the frequency domain : here is the modulus " <<
				"of the Fourier transform of your image" << '\n';
				Fourier_Transform<Image<PixelBW> > fft(img);
				fft.Display();
				std::string filter_type;
				while(filter_type != "LP" and filter_type != "HP" and filter_type != "BP")
				{
					cin.clear();
					cout << "Which filter do you want to apply on your image ? Please enter " <<
					"'LP' for Low Pass filter,'HP' for High Pass filter or 'BP' for Band Pass filter" << '\n';
					cin >> filter_type;
				}
				double cutoff(-1);
				double cutoff2(-1);
				double sharpness(-1);
				if(filter_type == "LP" or filter_type == "HP")
				{
					cin.clear();
					while (cutoff <= 0 or cutoff >= (sqrt(2)/2)*img.Width() ) {
						std::cout << "Choose the cutoff real value of your filter :  0 < cutoff < " << (sqrt(2)/2)*img.Width() << '\n';
						cin >> cutoff;
					}
					while ( sharpness <= 0){
						std::cout << "Now, you can choose the sharpness of your cut. Make sure you have a sharpness " <<
						"large enough not experience Gibb's effects and small enough to keep the behavior you want on your image. " << '\n';
						cin >> sharpness;
					}
				} else if (filter_type == "BP")
				{
					while (cutoff <= 0 or cutoff >= (sqrt(2)/2)*img.Width() ) {
						std::cout << "Choose the first cutoff real value (the lower one) of your band pass filter " <<
						":  0 < cutoff_1 < " << (sqrt(2)/2)*img.Width() << '\n';
						cin >> cutoff;
					}
					while (cutoff2 <= cutoff or cutoff2 >= (sqrt(2)/2)*img.Width() ) {
						std::cout << "Choose the second cutoff real value (the highest one) of your band pass filter " <<
						": " << cutoff << " < cutoff_2 < " << (sqrt(2)/2)*img.Width() << '\n';
						cin >> cutoff2;
					}
					while ( sharpness <= 0){
						std::cout << "Now, you can choose the sharpness of your cut. Make sure you have a sharpness " <<
						"large enough not experience Gibb's effects and small enough not to experience overlap between you two cuts. " << '\n';
						cin >> sharpness;
					}
				}
				std::cout << "Your filter is ready ! Let's apply it on the fourier transform of your image !" << '\n';
				Filter filter(img.Width(),img.Height(),filter_type, cutoff,sharpness,cutoff2);
				Fourier_Transform<Image<PixelBW> > filtered_fft(filter.Apply(fft));
				std::cout << "Here is the new modulus generated." << '\n';
				filtered_fft.Display("fourier modulus of the filtered Image");
				std::cout << "Now we can come back in the space domain..." << '\n';
				Image<PixelBW> reconstructed_image(filtered_fft);
				std::cout << "See the result ! " << '\n';
				reconstructed_image.Display("filtered image");
				reconstructed_image.Save("../resources/image_filtered_fourier.jpg");
				std::cout << "And we can obtain the same without passing in the Fourier domain..." << '\n';
				Image<PixelBW> img_filtered(filter.Apply(img));
				img_filtered.Display("Image filtered in the space domain");
				img_filtered.Save("../resources/image_filtered_real.jpg");
				std::cout << "Filtered image has been saved in your resources folder if you want to take a look !" << '\n';
				}
				if(c==3)
				{
					Image<PixelRGB> img(image_input);
					img.Display();
					HistogramRGB hist(img);
					std::cout << "Here is the Histogram of your image. Sweet isn't it?" << '\n';
					hist.Display();
					std::cout << "Now, it's time to go in the frequency domain : here is the modulus " <<
					"of the Fourier transform of your image" << '\n';
					Fourier_Transform<Image<PixelRGB> > fft(img);
					fft.Display();
					std::string filter_type;
					while(filter_type != "LP" and filter_type != "HP" and filter_type != "BP")
					{
						cin.clear();
						cout << "Which filter do you want to apply on your image ? Please enter " <<
						"'LP' for Low Pass filter,'HP' for High Pass filter or 'BP' for Band Pass filter" << '\n';
						cin >> filter_type;
					}
					double cutoff(-1);
					double cutoff2(-1);
					double sharpness(-1);
					if(filter_type == "LP" or filter_type == "HP")
					{
						cin.clear();
						while (cutoff <= 0 or cutoff >= (sqrt(2)/2)*img.Width() ) {
							std::cout << "Choose the cutoff real value of your filter :  0 < cutoff < " << (sqrt(2)/2)*img.Width() << '\n';
							cin >> cutoff;
						}
						while ( sharpness <= 0){
							std::cout << "Now, you can choose the sharpness of your cut. Make sure you have a sharpness " <<
							"large enough not experience Gibb's effects and small enough to keep the behavior you want on your image. " << '\n';
							cin >> sharpness;
						}
					} else if (filter_type == "BP")
					{
						while (cutoff <= 0 or cutoff >= (sqrt(2)/2)*img.Width() ) {
							std::cout << "Choose the first cutoff real value (the lower one) of your band pass filter " <<
							":  0 < cutoff_1 < " << (sqrt(2)/2)*img.Width() << '\n';
							cin >> cutoff;
						}
						while (cutoff2 <= cutoff or cutoff2 >= (sqrt(2)/2)*img.Width() ) {
							std::cout << "Choose the second cutoff real value (the highest one) of your band pass filter " <<
							": " << cutoff << " < cutoff_2 < " << (sqrt(2)/2)*img.Width() << '\n';
							cin >> cutoff2;
						}
						while ( sharpness <= 0){
							std::cout << "Now, you can choose the sharpness of your cut. Make sure you have a sharpness " <<
							"large enough not experience Gibb's effects and small enough not to experience overlap between you two cuts. " << '\n';
							cin >> sharpness;
						}
					}
					std::cout << "Your filter is ready ! Let's apply it on the fourier transform of your image !" << '\n';
					Filter filter(img.Width(),img.Height(),filter_type, cutoff,sharpness,cutoff2);
					Fourier_Transform<Image<PixelRGB> > filtered_fft(filter.Apply(fft));
					std::cout << "Here is the new modulus generated." << '\n';
					filtered_fft.Display("fourier modulus of the filtered Image");
					std::cout << "Now we can come back in the space domain..." << '\n';
					Image<PixelRGB> reconstructed_image(filtered_fft);
					std::cout << "See the result ! " << '\n';
					reconstructed_image.Display("filtered image");
					reconstructed_image.Save("../resources/image_filtered_fourier.jpg");
					std::cout << "And we can obtain the same without passing in the Fourier domain..." << '\n';
					Image<PixelRGB> img_filtered(filter.Apply(img));
					img_filtered.Display("Image filtered in the space domain");
					img_filtered.Save("../resources/image_filtered_real.jpg");
					std::cout << "Filtered image has been saved in your resources folder if you want to take a look !" << '\n';
					}

				}
			}
			cout << "\nThanks for using me! Bye Bye!\n";

			return 0;
		}
