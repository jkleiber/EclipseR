/*
 * EclipseR.cpp
 *
 *  Created on: Sep 6, 2017
 *      Author: Justin
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

#include "EclipseR.h"

#include "FileInput.h"
#include "UnitTests.h"

using namespace std;


int main()
{
	//UNCOMMENT BELOW TO RUN UNIT TESTS HERE
	//UnitTests unitTest;

	//Create the array of Eclipse
	ResizableArray<Eclipse> eclipseDataArray;

	//Create a FileInput object that will take care of all data input
	FileInput fileInput;

	//Load the data that the user wants
	dataInputLoop(eclipseDataArray, fileInput);

	//If the user actually gave us files with data, then continue, else exit.
	if(eclipseDataArray.getNumElements() > 0)
	{
		//Manipulate the data however the user wants until the program ends.
		dataManipLoop(eclipseDataArray, fileInput);
	}

	cout << "Thanks for using EclipseR!\n";

	return 0;
}

void dataInputLoop(ResizableArray<Eclipse>& eclipseDataArray, FileInput& fileInput)
{
	string filename = " ";

	while(filename != "")
	{
		cout << "Enter a data file name: ";
		getline(cin, filename);

		if(filename != "")
		{
			fileInput.loadFile(eclipseDataArray, filename);
		}
	}
}

void dataManipLoop(ResizableArray<Eclipse>& eclipseDataArray, FileInput& fileInput)
{
	string userInput = "";

	while(userInput != "Q")
	{
		cout << "(O)utput, (S)ort, (F)ind, or (Q)uit?\n";
		getline(cin, userInput);

		if(userInput == "O")
		{
			ofstream outputFile;
			string outputUserInput = "";
			bool usingStdout = false;

			while(true)
			{
				cout << "Enter the name of an output file: ";
				getline(cin, outputUserInput);

				if(outputUserInput == "")
				{
					usingStdout = true;
					break;
				}
				else
				{
					outputFile.open(outputUserInput.c_str());
				}

				if(outputFile.good())
				{
					break;
				}
				else
				{
					cerr << "File is not available.\n";
				}
			}

			if(usingStdout)
			{
				cout << eclipseDataArray;
				cout << "Data lines read: " << fileInput.getTotal();
				cout << "; Valid eclipses read: " << fileInput.getNumValid();
				cout << "; Eclipses in memory: " << eclipseDataArray.getNumElements();
				cout << endl;
			}
			else
			{
				outputFile << eclipseDataArray << endl;
				outputFile << "Data lines read: " << fileInput.getTotal();
				outputFile << "; Valid eclipses read: " << fileInput.getNumValid();
				outputFile << "; Eclipses in memory: " << eclipseDataArray.getNumElements();
				outputFile << endl;
			}
		}
		else if(userInput == "S")
		{

		}
		else if(userInput == "F")
		{

		}
		else if(userInput == "Q")
		{
			break;
		}
		else
		{
			//The user entered bad information, so just ask again?
		}
	}
}
