/*
 * Eclipse.cpp
 *
 *  Created on: Sep 17, 2017
 *      Author: justin
 */

#include "Eclipse.h"

Eclipse::Eclipse()
{
	this->catalogNum = "0";
	this->eclipseType = " ";
	this->numCells = 24;
	this->numColumns = 0;
}


Eclipse::Eclipse(Eclipse &eclipse)
{
	this->catalogNum = eclipse.catalogNum;
	this->eclipseType = eclipse.eclipseType;
	this->numCells = eclipse.numCells;
	this->numColumns = eclipse.numColumns;

	for(int i = 0; i < 24; ++i)
	{
		this->cells[i] = eclipse.cells[i];
	}
}


void Eclipse::operator=(const Eclipse & eclipse)
{
	this->catalogNum = eclipse.catalogNum;
	this->eclipseType = eclipse.eclipseType;
	this->numCells = eclipse.numCells;
	this->numColumns = eclipse.numColumns;

	for(int i = 0; i < 24; ++i)
	{
		this->cells[i] = eclipse.cells[i];
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

void Eclipse::setRawInput(std::string rawInput)
{
	this->rawInput = rawInput;
}


std::string Eclipse::getRawInput()
{
	return this->rawInput;
}

std::ostream&operator<<(std::ostream& os, Eclipse eclipse)
{
	os << eclipse.rawInput;

	return os;
}
