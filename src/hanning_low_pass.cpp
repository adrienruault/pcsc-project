/*
 * low-pass.cpp
 *
 *  Created on: Dec 15, 2016
 *      Author: adrien
 */


#include <iostream>
#include <vector>
#include <math.h>
#include <iomanip>

#include "ComplexNumber.hpp"







std::vector<std::vector <double> > hanning_low_pass(int width, int height, double cut_off, double sharpness);
std::vector<std::vector <double> > hanning_high_pass(int width, int height, double cut_off, double sharpness);
std::vector<std::vector <double> > hanning_band_pass(int width, int height, double cut_off_1, double cut_off_2, double sharpness);







int main(int argc, char* argv[])
{

	std::vector<std::vector<double> > tab_test_low;
	std::vector<std::vector<double> > tab_test_high;
	std::vector<std::vector<double> > tab_test_band;

	int width=18;
	int height=18;

	tab_test_low=hanning_low_pass(width, height, 4, 1);
	tab_test_high=hanning_high_pass(width, height, 4, 1);
	tab_test_band=hanning_band_pass(width, height, 3, 6, 1);


	std::cout << std::setprecision(2);

	for(int i=0; i<width; i++)
	{
		std::cout << "\n";
		for(int j=0; j<height; j++)
		{
			std::cout << "\t" << tab_test_low[i][j];
		}
	}

	std::cout << "\n\n\n\n";

	for(int i=0; i<width; i++)
	{
		std::cout << "\n";
		for(int j=0; j<height; j++)
		{
			std::cout << "\t" << tab_test_high[i][j];
		}
	}

	std::cout << "\n\n\n\n";


	std::cout << "\n\n\n\n";

	for(int i=0; i<width; i++)
	{
		std::cout << "\n";
		for(int j=0; j<height; j++)
		{
			std::cout << "\t" << tab_test_band[i][j];
		}
	}

	return 0;
}



std::vector<std::vector <double> > hanning_low_pass(int width, int height, double cut_off, double sharpness)
{
	std::vector<std::vector<double>> tab;
	// initialisation of tab to 0;
	for(int i=0; i<width; i++)
	{
		tab.push_back(std::vector<double>(height));
	}

	double norm;
	double x_coo;
	double y_coo;

	ComplexNumber z;

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
				tab[i][j]=1;
			}
			else if (norm >= cut_off+sharpness)
			{
				tab[i][j]=0;
			}
			else
			{
				tab[i][j]=0.5*(1 - sin(M_PI*(norm-cut_off)/(2*sharpness)));
			}
		}
	}
	return tab;
}






std::vector<std::vector <double> > hanning_high_pass(int width, int height, double cut_off, double sharpness)
{
	std::vector<std::vector<double>> tab;

	for(int i=0; i<width; i++)
	{
		tab.push_back(std::vector<double>(height));
	}

	double norm;
	double x_coo;
	double y_coo;

	ComplexNumber z;

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
				tab[i][j]=0;
			}
			else if (norm >= cut_off+sharpness)
			{
				tab[i][j]=1;
			}
			else
			{
				tab[i][j]=1-0.5*(1 - sin(M_PI*(norm-cut_off)/(2*sharpness)));
			}
		}
	}
	return tab;
}



std::vector<std::vector <double> > hanning_band_pass(int width, int height, double cut_off_1, double cut_off_2, double sharpness)
{
	std::vector<std::vector<double>> tab;

	for(int i=0; i<width; i++)
	{
		tab.push_back(std::vector<double>(height));
	}

	double norm;
	double x_coo;
	double y_coo;

	ComplexNumber z;

	//for(int i=-width/2; i<width/2+1; i++)
	for(int i=0; i<width; i++)
	{
		//for(int j=-height/2; j<height/2+1; j++)
		for(int j=0; j<height; j++)
		{
			x_coo=i-(width/2)+0.5;
			y_coo=j-(height/2)+0.5;
			norm = sqrt(x_coo*x_coo+y_coo*y_coo);
			if (norm <= cut_off_1-sharpness)
			{
				tab[i][j]=0;
			}
			else if (cut_off_1-sharpness < norm and norm < cut_off_1+sharpness)
			{
				tab[i][j]=1-0.5*(1 - sin(M_PI*(norm-cut_off_1)/(2*sharpness)));
			}
			else if (cut_off_1+sharpness <= norm and norm <= cut_off_2-sharpness)
			{
				tab[i][j]=1;
			}
			else if (cut_off_2-sharpness <= norm and norm <= cut_off_2+sharpness)
			{
				tab[i][j]=0.5*(1 - sin(M_PI*(norm-cut_off_1)/(2*sharpness)));
			}
			else
			{
				tab[i][j]=0;
			}
		}
	}
	return tab;
}

