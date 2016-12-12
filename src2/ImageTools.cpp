/*
 * ImageTools.cpp
 *
 *  Created on: Dec 12, 2016
 *      Author: adrien
 */

#include "ImageTools.hpp"
//#include "Image.hpp"



void Histogram(Image& subject, const std::string& provided_name /*="undefined"*/)
{

	int height=histo.Height();
	histo.SetI(255);

	double ratio=0.75*(double)height/(double)ImageBW::MostPopI();
	int nb_pixel;
	int x;
	for(int i=0; i<255; i++)
	{
		nb_pixel=(int)((double)mdistribution[i]*ratio);
		for (int k=0; k<nb_pixel; k++)
		{
			//std::cout << i << "\t" << k << "\n";
			x=2*i;
			histo(x,height-1-k,0)=0;
			histo(x+1,height-1-k,0)=0;
		}
	}

	std::string save_histo;
	// Set the name to histo name attribute if no name is provided as argument
	if (provided_name=="undefined")
	{
		save_histo=histo.GetName();
	}
	else
	{
		save_histo=provided_name;
	}

	histo.Display();
	histo.Save(save_histo);

}
