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
	EclipseOperations dataOps;
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
			int col;
			string c;

			//Request the column to sort
			cout << "Data field (1-18)?\n";
			getline(cin, c);

			//If the user did not just press enter, attempt to convert the input
			if(c != "")
			{
				try{
					col = fileInput.convertStrToInt(c);

					//Only operate on valid column numbers
					if(col >= 1 && col <= 18)
					{
						col = col - 1;

						dataOps.sort(col, eclipseDataArray);
					}
				}
				catch(const exception &msg)
				{
					cerr << msg.what() << endl;
					//The user entered an invalid value, reset to manip loop
				}
			}
		}
		else if(userInput == "F")
		{
			int col;
			string value, c;

			//Request the column to sort
			cout << "Data field (1-18)?\n";
			getline(cin, c);

			if(c != "")
			{
				try{
					//Convert the value...
					col = fileInput.convertStrToInt(c);

					//Only operate on valid column numbers
					if(col >= 1 && col <= 18)
					{
						col = col - 1;

						if(col == 0 || col == 1 || col == 2 || col == 4 || col == 6 || col == 7 || col == 8 || col == 14 || col == 15 || col == 16)
						{
							cout << "Number to find?\n";
							getline(cin, value);

							try{
								int num = fileInput.convertStrToInt(value);
								Cell c(num);
								dataOps.find(col, c, eclipseDataArray);
							}
							catch(...)
							{
								//This is not a valid value to look for; give up
							}
						}
						else if(col == 10 || col == 11)
						{
							cout << "Number to find?\n";
							getline(cin, value);

							try{
								double fPoint = fileInput.convertStrToDouble(value);
								Cell c(fPoint);
								dataOps.find(col, c, eclipseDataArray);
							}
							catch(...)
							{
								//This is not a valid value to look for; give up
							}
						}
						else if(col == 4)
						{
							cout << "Month abbreviation to find?\n";
							getline(cin, value);

							bool valid = false;
							string months[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

							for(int i = 0; i < 12; ++i)
							{
								if(value == months[i])
								{
									valid = true;
								}
							}

							if(valid)
							{
								Cell c(value);
								dataOps.find(col, c, eclipseDataArray);
							}
						}
						else
						{
							cout << "Value to find?\n";
							getline(cin, value);

							if(col == 16 && value == "")
							{
								Cell c(0, true);
								dataOps.find(col, c, eclipseDataArray);
							}
							else
							{
								Cell c(value);
								dataOps.find(col, c, eclipseDataArray);
							}
						}
					}
				}
				catch(...)
				{
					//The user entered an invalid number, go back to manip loop
				}
			}
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
