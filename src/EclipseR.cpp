/*
 * EclipseR.cpp
 *
 *  Created on: Sep 6, 2017
 *      Author: Justin
 */

#include <iostream>
#include <iomanip>
#include <string>

#include "EclipseR.h"
#include "UnitTests.h"

using namespace std;


int main()
{
	//UNCOMMENT BELOW TO RUN UNIT TESTS HERE
	//UnitTests unitTest;

	//Count rows of data read to avoid header
	int totalRows = 0;

	//Create the array of Eclipse
	ResizableArray<Eclipse> eclipseDataArray;

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
				ProcessRow(rawData, eclipseDataArray);
			}
		}

		//Increment the row counter
		++totalRows;
	}

	//Check for errors in each eclipse
	CheckForErrors(eclipseDataArray);

	//Print eclipses in reverse order
	cout << eclipseDataArray;

	return 0;
}


void ProcessRow(string rawData, ResizableArray<Eclipse> & eclipseDataArray)
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
				eclipseData.SetCatalogNum(cell);
			}
			else if(col == 9) //If the column contains eclipse type, record it for later
			{
				eclipseData.SetEclipseType(cell);
			}

			//Save the cells individually for later processing
			eclipseData.AddCell(cell, col);

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
		eclipseData.AddCell(cell, col);
		++col;
	}

	//Set the number of columns in the eclipse
	eclipseData.SetNumColumns(col);

	//Add the processed eclipse to the array
	eclipseDataArray.Add(eclipseData);
}


bool isNumberUnique(ResizableArray<Eclipse> eclipseDataArray, int index)
{
	//Search through eclipses to see if any before this eclipse have the same catalog number
	for(int k = 0; k < index; ++k)
	{
		//Only consider it a duplicate if the catalog numbers are the same and the output is valid
		if(eclipseDataArray.Get(k).GetCatalogNum() == eclipseDataArray.Get(index).GetCatalogNum())
		{
			return false;
		}
	}

	return true;
}


void CheckForErrors(ResizableArray<Eclipse> & eclipseDataArray)
{
	//Error flag to determine if CSV output is allowed for a certain row
	bool errorFlag = false;

	//Array of columns to check for whole numbers
	const int wholeNumCols[10] = {1, 2, 3, 5, 7, 8, 9, 15, 16, 17};

	//Array of columns to check for floating point numbers
	const int floatNumCols[2] = {11, 12};

	bool isValidNumber = true;

	//Keep track of data row number
	int dataRow = 1;

	//Go through each eclipse and check for errors
	for(int index = 0; index < eclipseDataArray.GetNumElements(); ++index)
	{
		//Keep track of error status throughout error checking process
		errorFlag = false;

		/* Check to see if eclipse type matches column numbers */

		//If an eclipse is partial, it should have exactly 16 columns
		if(eclipseDataArray.Get(index).GetEclipseType()[0] == 'P' && eclipseDataArray.Get(index).GetNumColumns() != 16)
		{
			cerr << "Error in data row " << dataRow << ": " << eclipseDataArray.Get(index).GetNumColumns() << " columns found. ";
			cerr << "Should be 16.\n";

			errorFlag = true;
		}
		//If an eclipse is not partial, it should have exactly 18 columns
		else if(eclipseDataArray.Get(index).GetEclipseType()[0] != 'P' && eclipseDataArray.Get(index).GetNumColumns() != 18)
		{
			cerr << "Error in data row " << dataRow << ": " << eclipseDataArray.Get(index).GetNumColumns() << " columns found. ";
			cerr << "Should be 18.\n";

			errorFlag = true;
		}

		//Check for whole and decimal numbers in appropriate columns
		if(!errorFlag)
		{
			//Check the first 7 applicable rows to see if they are whole numbers
			for(int c = 0; c < 7; c++)
			{
				isValidNumber = isWholeNumber(eclipseDataArray.Get(index).GetCell(wholeNumCols[c] - 1));

				if(!isValidNumber)
				{
					cerr << "Error in data row " << dataRow << ": Column " << wholeNumCols[c] << " is not a whole number.\n";
					errorFlag = true;
				}
			}

			//Check the two floating point columns
			for(int c = 0; c < 2; c++)
			{
				isValidNumber = isDecimalNumber(eclipseDataArray.Get(index).GetCell(floatNumCols[c] - 1));

				if(!isValidNumber)
				{
					cerr << "Error in data row " << dataRow << ": Column " << floatNumCols[c] << " is not a decimal number.\n";
					errorFlag = true;
				}
			}

			//Check the last 3 applicable columns for whole numbers
			for(int c = 7; c < 10; c++)
			{
				isValidNumber = isWholeNumber(eclipseDataArray.Get(index).GetCell(wholeNumCols[c] - 1));

				if(!isValidNumber)
				{
					cerr << "Error in data row " << dataRow << ": Column " << wholeNumCols[c] << " is not a whole number.\n";
					errorFlag = true;
				}
			}
		}

		//If all other tests have passed, check for catalog number uniqueness
		if(!errorFlag)
		{
			//Check to see if this catalog number is unique
			errorFlag = !isNumberUnique(eclipseDataArray, index);

			//If the catalog number is not unique, raise an error
			if(errorFlag)
			{
				cerr << "Error in data row " << dataRow << ": Duplicate catalog number " << eclipseDataArray.Get(index).GetCatalogNum() << "." << endl;
			}
		}

		//Stay at the same index and delete the old row at this location
		if(errorFlag)
		{
			eclipseDataArray.RemoveAt(index);
			--index;
		}

		//No matter what, increment dataRow to keep track of the line we are really on
		++dataRow;

		//IF no errors are present, allow output
	}
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
