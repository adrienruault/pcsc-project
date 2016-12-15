/*
 * low-pass.cpp
 *
 *  Created on: Dec 15, 2016
 *      Author: adrien
 */


#include <iostream>
#include <vector>
#include <math.h>

#include "ComplexNumber.hpp"







std::vector<std::vector <double> > hanning_low_pass(int width, int height, double cut_off, double sharpness);



int main(int argc, char* argv[])
{

	std::vector<std::vector<double> > tab_test;

	int width=10;
	int height=10;

	tab_test=hanning_low_pass(width, height, 3, 0.5);


	for(int i=0; i<width; i++)
	{
		std::cout << "\n";
		for(int j=0; j<height; j++)
		{
			std::cout << "\t\t" << tab_test[i][j];
		}
	}

	std::cout << "\n";

	return 0;
}



std::vector<std::vector <double> > hanning_low_pass(int width, int height, double cut_off, double sharpness)
{
	double relay[width][height];

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
			if (norm < cut_off-sharpness)
			{
				tab[i][j]=1;
			}
			else if (norm > cut_off+sharpness)
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



