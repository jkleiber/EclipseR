/*
 * FileInput.cpp
 *
 *  Created on: Oct 12, 2017
 *      Author: justin
 */

#include "FileInput.h"

using namespace std;

FileInput::FileInput() {
	this->totalElementsRead = 0;
	this->validElementsRead = 0;
}

FileInput::~FileInput() {
	// TODO Auto-generated destructor stub
}

int FileInput::getNumValid() const
{
	return this->validElementsRead;
}

int FileInput::getTotal() const
{
	return this->totalElementsRead;
}

void FileInput::loadFile(ResizableArray<Eclipse>& eclipseDataArray, string file)
{
	//Count rows of data read to avoid header
	int totalRows = 0;

	//string to keep the raw data for processing
	string rawData;

	//Extract the header from the file
	string header = "";

	//Open a file stream based on the file specified by the user
	ifstream f(file.c_str());

	if(f.good())
	{
		//Read until the end of the data file
		while(getline(f, rawData))
		{
			//If the header of the document has been skipped already, parse data
			if(totalRows >= 10)
			{
				//Do not consider empty lines
				if(rawData.length() > 0)
				{
					//Add data from this row to the array
					processRow(rawData, eclipseDataArray, totalRows - 9);
				}
			}
			else
			{
				header += rawData + "\n";
			}

			//Increment the row counter
			++totalRows;
		}
	}
	else
	{
		cerr << "File is not available.\n";
	}

	f.close();

	eclipseDataArray.setHeader(header);
}

void FileInput::processRow(string rawData, ResizableArray<Eclipse>& eclipseDataArray, int row)
{
	string cell = "";
	char lastChar = ' ';
	int col = 0;

	Eclipse eclipseData;

	eclipseData.setRawInput(rawData);
	eclipseData.setRow(row);

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
			else if(col == 3)
			{
				//Set the month number for sorting purposes
				eclipseData.setMonthNumber(cell);
			}
			else if(col == 9) //If the column contains eclipse type, record it for later
			{
				eclipseData.setEclipseType(cell);
			}

			//Convert the cell to an integer or double if it is in a numeric column
			if(col == 0 || col == 1 || col == 2 || col == 4 || col == 6 || col == 7 || col == 8 || col == 14 || col == 15 || col == 16)
			{
				try{
					int num = convertStrToInt(cell);
					eclipseData.addWholeNumber(num, col);
				}
				catch(...)
				{
					eclipseData.addError(col);
				}
			}
			else if(col == 10 || col == 11)
			{
				try{
					double fPoint = convertStrToDouble(cell);
					eclipseData.addFloatingPoint(fPoint, col);
				}
				catch(...)
				{
					eclipseData.addError(col);
				}
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
		this->validElementsRead++;

		int duplicateIndex = isNumberUnique(eclipseDataArray, eclipseData);

		if(duplicateIndex != -1)
		{
			try
			{
				cerr << "Error in data row " << row << ": Duplicate catalog number " << eclipseData.getCatalogNum() << "." << endl;
				eclipseDataArray.removeAt(duplicateIndex);
			}
			catch(const char* msg)
			{
				cout << msg << endl;
			}
		}

		//Add the processed eclipse to the array
		eclipseDataArray.add(eclipseData);
	}

	this->totalElementsRead++;
}


int FileInput::isNumberUnique(ResizableArray<Eclipse> eclipseDataArray, Eclipse eclipse)
{
	//Search through eclipses to see if any before this eclipse have the same catalog number
	for(int k = 0; k < eclipseDataArray.getNumElements(); ++k)
	{
		try
		{
			//Only consider it a duplicate if the catalog numbers are the same and the output is valid
			if(eclipseDataArray.get(k).getCatalogNum() == eclipse.getCatalogNum())
			{
				return k;
			}
		}
		catch(const char* msg)
		{
			cout << msg << " " << k << endl;
		}
	}

	return -1;
}


bool FileInput::isValid(Eclipse eclipse, int dataRow)
{
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
	else if(eclipse.getNumErrors() > 0)
	{
		eclipse.printAllErrors();
		return false;
	}

	//IF no errors are present, allow output
	return true;
}

int FileInput::convertStrToInt(std::string str)
{
	int output = 0;
	bool valid = true;

	int placeValue = 1;

	for(int i = str.length() - 1; i >= 0 ; --i)
	{
		if(isNumber(str[i]))
		{
			output += placeValue * (str[i] - '0');
			placeValue *= 10;
		}
		else if(i == 0 && str[0] == '-' && str.length() > 1)
		{
			output = -output;
		}
		else
		{
			valid = false;
			break;
		}
	}

	if(valid)
	{
		return output;
	}
	else
	{
		throw "Not a valid integer.";
	}
}

double FileInput::convertStrToDouble(std::string str)
{
	double left = 0.0, right = 0.0, output = 0.0;
	bool valid = true, isNegative = false;

	double placeValue = 1;

	size_t decimal = str.find('.');
	decimal = str.find('.', decimal + 1);

	if(decimal == string::npos)
	{
		decimal = str.find('.');

		for(int i = static_cast<int>(decimal) - 1; i >= 0; --i)
		{
			if(isNumber(str[i]))
			{
				left += placeValue * (str[i] - '0');
				placeValue *= 10;
			}
			else if(i == 0 && str[0] == '-'  && str.length() > 1)
			{
				isNegative = true;
			}
			else
			{
				valid = false;
				break;
			}
		}

		//Prepare for the stuff after the decimal
		placeValue = 0.1;

		if(valid)
		{
			for(unsigned int i = decimal + 1; i < str.length(); ++i)
			{
				if(isNumber(str[i]))
				{
					right += placeValue * (str[i] - '0');
					placeValue *= 0.1;
				}
				else
				{
					valid = false;
					break;
				}
			}
		}
	}
	else
	{
		valid = false;
	}

	output = left + right;

	output = isNegative ? -output : output;

	if(valid)
	{
		return output;
	}
	else
	{
		throw "Not a valid floating point number.";
	}
}

bool FileInput::isNumber(char c)
{
	const char validDigits[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

	for(int j = 0; j < 10; ++j)
	{
		if(c == validDigits[j])
		{
			break;
		}
		else if(j == 9)
		{
			return false;
		}
	}

	return true;
}
