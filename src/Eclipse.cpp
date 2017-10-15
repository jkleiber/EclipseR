/*
 * Eclipse.cpp
 *
 *  Created on: Sep 17, 2017
 *      Author: justin
 */

#include "Eclipse.h"
#include <iostream>

Eclipse::Eclipse()
{
	this->catalogNum = "0";
	this->eclipseType = " ";
	this->numCells = 24;
	this->numColumns = 0;
	this->rawInput = "";
	this->monthNumber = 0;
	this->numErrors = 0;
	this->row = 0;
}


Eclipse::Eclipse(Eclipse &eclipse)
{
	this->catalogNum = eclipse.catalogNum;
	this->eclipseType = eclipse.eclipseType;
	this->numCells = eclipse.numCells;
	this->numColumns = eclipse.numColumns;
	this->rawInput = eclipse.rawInput;
	this->monthNumber = eclipse.monthNumber;
	this->numErrors = eclipse.numErrors;
	this->row = eclipse.row;

	for(int i = 0; i < 24; ++i)
	{
		this->cells[i] = eclipse.cells[i];
	}

	for(int i = 0; i < 24; ++i)
	{
		this->wholeNumbers[i] = eclipse.wholeNumbers[i];
	}

	for(int i = 0; i < 24; ++i)
	{
		this->floatingPointNumbers[i] = eclipse.floatingPointNumbers[i];
	}

	for(int i = 0; i < 24; ++i)
	{
		this->columnErrors[i] = eclipse.columnErrors[i];
	}
}


void Eclipse::operator=(const Eclipse & eclipse)
{
	this->catalogNum = eclipse.catalogNum;
	this->eclipseType = eclipse.eclipseType;
	this->numCells = eclipse.numCells;
	this->numColumns = eclipse.numColumns;
	this->rawInput = eclipse.rawInput;
	this->monthNumber = eclipse.monthNumber;
	this->numErrors = eclipse.numErrors;
	this->row = eclipse.row;

	for(int i = 0; i < 24; ++i)
	{
		this->cells[i] = eclipse.cells[i];
	}

	for(int i = 0; i < 24; ++i)
	{
		this->wholeNumbers[i] = eclipse.wholeNumbers[i];
	}

	for(int i = 0; i < 24; ++i)
	{
		this->floatingPointNumbers[i] = eclipse.floatingPointNumbers[i];
	}

	for(int i = 0; i < 24; ++i)
	{
		this->columnErrors[i] = eclipse.columnErrors[i];
	}
}

Eclipse::~Eclipse()
{

}

bool Eclipse::equals(Eclipse Eclipse)
{
	if(this->catalogNum == Eclipse.catalogNum && this->eclipseType == Eclipse.eclipseType
			&& this->numCells == Eclipse.numCells && this->numColumns == Eclipse.numColumns) {

		bool areCellsSame = true;
		for(int i = 0; i < this->numColumns; ++i)
		{
			if(this->cells[i] != Eclipse.cells[i])
			{
				areCellsSame = false;
				break;
			}
		}

		if(areCellsSame)
		{
			return true;
		}
	}

	return false;
}

std::string Eclipse::getCatalogNum() const {
	return catalogNum;
}

void Eclipse::setCatalogNum(const std::string catalogNum) {
	this->catalogNum = catalogNum;
}

std::string Eclipse::getCell(int index) const {
	return cells[index];
}

void Eclipse::addCell(std::string cell, int index) {
	this->cells[index] = cell;

	numColumns++;
}

std::string Eclipse::getEclipseType() const {
	return eclipseType;
}

void Eclipse::setEclipseType(std::string eclipseType) {
	this->eclipseType = eclipseType;
}

int Eclipse::getNumColumns() const {
	return this->numColumns;
}

void Eclipse::setNumColumns(int numColumns) {
	this->numColumns = numColumns;
}

void Eclipse::addWholeNumber(int wholeNum, int index)
{
	if(index < 24 && index >= 0)
	{
		this->wholeNumbers[index] = wholeNum;
	}
	else
	{
		throw "Eclipse::addWholeNumber(): Index out of bounds.";
	}
}

int Eclipse::getWholeNumber(int index) const
{
	if(index < 24 && index >= 0)
	{
		return this->wholeNumbers[index];
	}

	throw "Eclipse::getWholeNumber(): Index out of bounds.";
}

void Eclipse::addFloatingPoint(double floatNum, int index)
{
	if(index < 24 && index >= 0)
	{
		this->floatingPointNumbers[index] = floatNum;
	}
	else
	{
		throw "Eclipse::addFloatingPoint(): Index out of bounds.";
	}
}

double Eclipse::getFloatingPoint(int index) const
{
	if(index < 24 && index >= 0)
	{
		return this->floatingPointNumbers[index];
	}

	throw "Eclipse::getFloatingPoint(): Index out of bounds.";
}

int Eclipse::getMonthNumber() const
{
	return this->monthNumber;
}

void Eclipse::setMonthNumber(std::string month)
{
	std::string months[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
	int i;

	for(i = 0; i < 12; ++i)
	{
		if(month == months[i])
		{
			break;
		}
	}

	this->monthNumber = i + 1;
}

std::string Eclipse::getRawInput() const {
	return rawInput;
}

void Eclipse::setRawInput(std::string rawInput)
{
	this->rawInput = rawInput;
}

void Eclipse::addError(int col)
{
	this->columnErrors[col] = true;
	numErrors++;
}

void Eclipse::printAllErrors()
{
	for(int i = 0; i < numErrors; ++i)
	{
		if(columnErrors[i] && (i == 10 || i == 11))
		{
			std::cerr << "Error in data row " << this->row << ": Column " << (i + 1) << " is not a decimal number.\n";
		}
		else if(columnErrors[i])
		{
			std::cerr << "Error in data row " << this->row << ": Column " << (i + 1) << " is not a whole number.\n";
		}
	}
}

int Eclipse::getNumErrors()
{
	return this->numErrors;
}

void Eclipse::setRow(int row)
{
	this->row = row;
}

int Eclipse::getRow()
{
	return this->row;
}

std::ostream& operator<<(std::ostream& os, Eclipse &eclipse)
{
	os << eclipse.rawInput;

	return os;
}
