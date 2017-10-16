/*
 * Cell.cpp
 *
 *  Created on: Oct 15, 2017
 *      Author: justin
 */

#include "Cell.h"


Cell::Cell()
{
	this->cellType = -1;
	this->strData = "";
	this->intData = 0;
	this->floatData = 0.0;
	this->isMax = false;
}

Cell::~Cell() {
	// TODO Auto-generated destructor stub
}

std::ostream&operator<<(std::ostream& os, const Cell& cell)
{
	if(cell.cellType == STR_CELL)
	{
		os << cell.strData;
	}
	else if(cell.cellType == INT_CELL)
	{
		os << cell.intData;
	}
	else
	{
		os << cell.floatData;
	}

	return os;
}


Cell::Cell(std::string data)
{
	cellType = STR_CELL;
	this->strData = data;
	this->intData = 0;
	this->floatData = 0.0;
	this->isMax = false;
}

Cell::Cell(int data)
{
	cellType = INT_CELL;
	this->strData = "";
	this->intData = data;
	this->floatData = 0.0;
	this->isMax = false;
}

Cell::Cell(double data)
{
	cellType = FLOAT_CELL;
	this->strData = "";
	this->intData = 0;
	this->floatData = data;
	this->isMax = false;
}

Cell::Cell(int data, bool isMax)
{
	cellType = INT_CELL;
	this->strData = "";
	this->intData = data;
	this->floatData = 0.0;
	this->isMax = isMax;
}

bool Cell::operator<(Cell c)
{
	if(cellType == STR_CELL)
	{
		if(c.strData == strData)
		{
			return false;
		}
		else if(strData == "")
		{
			return false;
		}
		else if(c.strData == "")
		{
			return true;
		}
		else
		{
			int comp = strData.compare(c.strData);

			return comp < 0;
		}
	}
	else if(cellType == INT_CELL)
	{
		if(intData == c.intData)
		{
			return false;
		}
		else if(isMax)
		{
			return false;
		}

		return intData < c.intData;
	}
	else
	{
		return floatData < c.floatData;
	}
}

bool Cell::operator==(Cell c)
{
	if(cellType == STR_CELL)
	{
		return strData == c.strData;
	}
	else if(cellType == INT_CELL)
	{
		return intData == c.intData;
	}
	else
	{
		return floatData == c.floatData;
	}
}

bool Cell::operator!=(Cell c)
{
	if(cellType == STR_CELL)
	{
		return strData.compare(c.strData) != 0;
	}
	else if(cellType == INT_CELL)
	{
		return intData != c.intData;
	}
	else
	{
		return floatData != c.floatData;
	}
}

bool Cell::operator>(Cell c)
{
	if(cellType == STR_CELL)
	{
		if(c.strData == strData)
		{
			return false;
		}
		else if(strData == "")
		{
			return true;
		}
		else if(c.strData == "")
		{
			return false;
		}
		else
		{
			int comp = strData.compare(c.strData);

			return comp > 0;
		}
	}
	else if(cellType == INT_CELL)
	{
		if(intData == c.intData)
		{
			return false;
		}
		else if(isMax)
		{
			return true;
		}

		return intData > c.intData;
	}
	else
	{
		return floatData > c.floatData;
	}
}

bool Cell::operator>=(Cell c)
{
	if(cellType == STR_CELL)
	{
		int comp = strData.compare(c.strData);

		if(comp != 0)
		{
			if(strData == "")
			{
				return true;
			}
			else if(c.strData == "")
			{
				return false;
			}
		}

		return comp >= 0;
	}
	else if(cellType == INT_CELL)
	{
		if(intData != c.intData)
		{
			if(isMax)
			{
				return true;
			}
			else if(c.isMax)
			{
				return false;
			}
		}

		return intData >= c.intData;
	}
	else
	{
		return floatData >= c.floatData;
	}
}

bool Cell::operator<=(Cell c)
{
	if(cellType == STR_CELL)
	{
		int comp = strData.compare(c.strData);

		if(comp != 0)
		{
			if(strData == "")
			{
				return false;
			}
			else if(c.strData == "")
			{
				return true;
			}
		}

		return comp <= 0;
	}
	else if(cellType == INT_CELL)
	{
		if(intData != c.intData)
		{
			if(isMax)
			{
				return false;
			}
			else if(c.isMax)
			{
				return true;
			}
		}

		return intData <= c.intData;
	}
	else
	{
		return floatData <= c.floatData;
	}
}

