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

bool Eclipse::Equals(Eclipse Eclipse)
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

std::string Eclipse::GetCatalogNum() const {
	return catalogNum;
}

void Eclipse::SetCatalogNum(const std::string catalogNum) {
	this->catalogNum = catalogNum;
}

std::string Eclipse::GetCell(int index) const {
	return cells[index];
}

void Eclipse::AddCell(std::string cell, int index) {
	this->cells[index] = cell;

	numColumns++;
}

std::string Eclipse::GetEclipseType() const {
	return eclipseType;
}

void Eclipse::SetEclipseType(std::string eclipseType) {
	this->eclipseType = eclipseType;
}

int Eclipse::GetNumColumns() const {
	return this->numColumns;
}

void Eclipse::SetNumColumns(int numColumns) {
	this->numColumns = numColumns;
}

std::ostream&operator<<(std::ostream& os, Eclipse Eclipse)
{
	std::string csv = "";

	for(int i = 0; i < Eclipse.GetNumColumns(); ++i)
	{
		csv.append(Eclipse.GetCell(i));

		if(i != (Eclipse.GetNumColumns() - 1))
		{
			csv.append(",");
		}
	}

	os << csv;

	return os;
}
