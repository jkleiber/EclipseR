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
#include "UnitTests.h"

using namespace std;


int main()
{
	//UNCOMMENT BELOW TO RUN UNIT TESTS HERE
	//UnitTests unitTest;

	//Create the array of Eclipse
	ResizableArray<Eclipse> eclipseDataArray;

	dataInputLoop(eclipseDataArray);

	//Print eclipses in reverse order
	cout << eclipseDataArray;

	return 0;
}

void dataInputLoop(ResizableArray<Eclipse>& eclipseDataArray)
{
	string filename = " ";

	while(filename != "")
	{
		cout << "Enter a data file name: ";
		cin >> filename;

		loadFile(eclipseDataArray, filename);
	}
}

void dataManipLoop(ResizableArray<Eclipse>& eclipseDataArray)
{

}


void loadFile(ResizableArray<Eclipse>& eclipseDataArray, string file)
{
	//Count rows of data read to avoid header
	int totalRows = 0;

	//string to keep the raw data for processing
	string rawData;

	//Read until the end of the data file
	while(getline(cin, rawData))
	{
		//If the header of the document has been skipped already, parse data
		if(totalRows >= 10)
		{
			//Do not consider empty lines
			if(rawData.length() > 0)
			{
				//Add data from this row to the array
				processRow(rawData, eclipseDataArray, totalRows);
			}
		}

		//Increment the row counter
		++totalRows;
	}

}

void processRow(string rawData, ResizableArray<Eclipse>& eclipseDataArray, int row)
{
	string cell = "";
	char lastChar = ' ';
	int col = 0;

	Eclipse eclipseData;

	//Go through the line one character at a time
	for(unsigned int s = 0; s < rawData.length(); ++s)
	{
		//If a space is not found, then a 'cell' is being viewed. Record this for later.
		if(rawData[s] != ' ')
		{
			cell.push_back(rawData[s]);
			lastChar = rawData[s];
		}
		else if(rawData[s] == ' ' && lastChar != ' ') //If we just reached the end of a cell...
		{
			/* Apply special cases for error checking reasons */

			//If column = 0, then check for catalog number uniqueness
			if(col == 0)
			{
				eclipseData.setCatalogNum(cell);
			}
			else if(col == 9) //If the column contains eclipse type, record it for later
			{
				eclipseData.setEclipseType(cell);
			}

			//Save the cells individually for later processing
			eclipseData.addCell(cell, col);

			//Reset the cell string
			cell = "";

			//Set the last character to whitespace
			lastChar = ' ';

			//Increment the column counter
			++col;
		}
	}

	//Add the last column if there is no whitespace to indicate the end of a row
	if(cell != "")
	{
		eclipseData.addCell(cell, col);
		++col;
	}

	//Set the number of columns in the eclipse
	eclipseData.setNumColumns(col);

	if(isValid(eclipseData, row) == true)
	{
		eclipseDataArray.incrementValidCount();
	}

	int duplicateIndex = isNumberUnique(eclipseDataArray, eclipseData);

	if(duplicateIndex != -1)
	{
		eclipseDataArray.removeAt(duplicateIndex);
	}

	//Add the processed eclipse to the array
	eclipseDataArray.add(eclipseData);
}


int isNumberUnique(ResizableArray<Eclipse> eclipseDataArray, Eclipse eclipse)
{
	//Search through eclipses to see if any before this eclipse have the same catalog number
	for(int k = 0; k < eclipseDataArray.size(); ++k)
	{
		//Only consider it a duplicate if the catalog numbers are the same and the output is valid
		if(eclipseDataArray.get(k).getCatalogNum() == eclipse.getCatalogNum())
		{
			return k;
		}
	}

	return -1;
}


bool isValid(Eclipse eclipse, int dataRow)
{
	//Array of columns to check for whole numbers
	const int wholeNumCols[10] = {1, 2, 3, 5, 7, 8, 9, 15, 16, 17};

	//Array of columns to check for floating point numbers
	const int floatNumCols[2] = {11, 12};

	bool isValidNumber = true;

	/* Check to see if eclipse type matches column numbers */

	//If an eclipse is partial, it should have exactly 16 columns
	if(eclipse.getEclipseType()[0] == 'P' && eclipse.getNumColumns() != 16)
	{
		cerr << "Error in data row " << dataRow << ": " << eclipse.getNumColumns() << " columns found. ";
		cerr << "Should be 16.\n";

		return false;
	}
	//If an eclipse is not partial, it should have exactly 18 columns
	else if(eclipse.getEclipseType()[0] != 'P' && eclipse.getNumColumns() != 18)
	{
		cerr << "Error in data row " << dataRow << ": " << eclipse.getNumColumns() << " columns found. ";
		cerr << "Should be 18.\n";

		return false;
	}


	//Check the first 7 applicable rows to see if they are whole numbers
	for(int c = 0; c < 7; c++)
	{
		isValidNumber = isWholeNumber(eclipse.getCell(wholeNumCols[c] - 1));

		if(!isValidNumber)
		{
			cerr << "Error in data row " << dataRow << ": Column " << wholeNumCols[c] << " is not a whole number.\n";
			return false;
		}
	}

	//Check the two floating point columns
	for(int c = 0; c < 2; c++)
	{
		isValidNumber = isDecimalNumber(eclipse.getCell(floatNumCols[c] - 1));

		if(!isValidNumber)
		{
			cerr << "Error in data row " << dataRow << ": Column " << floatNumCols[c] << " is not a decimal number.\n";
			return false;
		}
	}

	//Check the last 3 applicable columns for whole numbers
	for(int c = 7; c < 10; c++)
	{
		isValidNumber = isWholeNumber(eclipse.getCell(wholeNumCols[c] - 1));

		if(!isValidNumber)
		{
			cerr << "Error in data row " << dataRow << ": Column " << wholeNumCols[c] << " is not a whole number.\n";
			return false;
		}
	}

	//IF no errors are present, allow output
	return true;
}


bool isWholeNumber(string str)
{
	const char validDigits[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

	size_t decimal = str.find('.');

	if(decimal == string::npos)
	{
		for(unsigned int i = 0; i < str.length(); ++i)
		{
			for(int j = 0; j < 10; ++j)
			{
				if(str[i] == validDigits[j])
				{
					break;
				}
				else if(i == 0 && str[0] == '-'  && str.length() > 1)
				{
					break;
				}
				else if(str[i] != validDigits[j] && j == 9)
				{
					return false;
				}
			}
		}
	}
	else
	{
		return false;
	}

	return true;
}


bool isDecimalNumber(string str)
{
	const char validDigits[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

	size_t decimal = str.find('.');
	decimal = str.find('.', decimal + 1);

	if(decimal == string::npos)
	{
		for(unsigned int i = 0; i < str.length(); ++i)
		{
			for(int j = 0; j < 10; ++j)
			{
				if(str[i] == validDigits[j])
				{
					break;
				}
				else if(i == 0 && str[0] == '-' && str.length() > 1)
				{
					break;
				}
				else if(str[i] != validDigits[j] && j == 9 && str[i] != '.')
				{
					return false;
				}
			}
		}
	}
	else
	{
		return false;
	}

	return true;
}
