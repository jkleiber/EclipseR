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
	this->numErrors = eclipse.numErrors;
	this->row = eclipse.row;

	for(int i = 0; i < 24; ++i)
	{
		this->cells[i] = eclipse.cells[i];
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
	this->numErrors = eclipse.numErrors;
	this->row = eclipse.row;

	for(int i = 0; i < 24; ++i)
	{
		this->cells[i] = eclipse.cells[i];
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

Cell Eclipse::getCell(int index) const {
	return cells[index];
}

void Eclipse::addCell(Cell cell, int index) {
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
	for(int i = 0; i < numColumns; ++i)
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

bool Eclipse::operator<(const Eclipse& eclipse)
{
	return this->cells[0] < eclipse.cells[0];
}

bool Eclipse::operator>(const Eclipse& eclipse)
{
	return this->cells[0] > eclipse.cells[0];
}

bool Eclipse::operator==(const Eclipse& eclipse)
{
	return this->cells[0] == eclipse.cells[0];
}

bool Eclipse::operator==(const int& catalogNum)
{
	return this->cells[0] == catalogNum;
}

bool Eclipse::operator!=(const Eclipse& eclipse)
{
	return this->cells[0] != eclipse.cells[0];
}

std::ostream& operator<<(std::ostream& os, Eclipse &eclipse)
{
	os << eclipse.rawInput;

	return os;
}
