/*
 * user.cpp
 *
 *  Created on: Dec 14, 2016
 *      Author: adrien
 */

#include <iostream>
#include <fstream>

#include "CImg.h"
#include "Image.hpp"

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
		while (!file.good() and quit=="NO")
		{
			file.close();
			cout << "\nI can't find the file, could you try another name?";
			cout << "\nOr just quit by typing quit!\n";
			cout << "\n>>";
			cin.clear();
			cin >> input;
			if (input != "quit")
			{
				image_input=input;
				ifstream file(image_input);
			}
			else
			{
				quit="YES";
			}
		}
		if (quit == "NO")
		{
			// Continue here
			cout << "OK! You opened the file:" << image_input << "\n";
		}
	}


	cout << "\nThanks for using me! Bye Bye!\n";

	return 0;
}
