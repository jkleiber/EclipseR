/*
 * EclipseOperations.cpp
 *
 *  Created on: Oct 16, 2017
 *      Author: justin
 */

#include "EclipseOperations.h"

EclipseOperations::EclipseOperations() {
	this->currentSort = -1;

}

EclipseOperations::~EclipseOperations() {
	// TODO Auto-generated destructor stub
}


void EclipseOperations::sort(int col, ResizableArray<Eclipse>& resizableArray)
{
	this->currentSort = col;

	//mergeSort(resizableArray, col, 0, resizableArray.getNumElements() - 1);
	quickSort(0, resizableArray.getNumElements() - 1, resizableArray, col);
}

void EclipseOperations::find(int col, Cell value, ResizableArray<Eclipse>& resizableArray)
{
	ResizableArray<Eclipse> printTheseValues;

	//If the column is already sorted, do a modified binary search
	if(col == currentSort)
	{
		binarySearch(value, col, 0, resizableArray.getNumElements() - 1, resizableArray, printTheseValues);
	}
	else //Otherwise do a linear search
	{
		for(int i = 0; i < resizableArray.getNumElements(); ++i)
		{
			if(resizableArray.get(i).getCell(col) == value)
			{
				printTheseValues.add(resizableArray.get(i));
			}
		}
	}

	if(printTheseValues.getNumElements() > 0)
	{
		//Print the header
		std::cout << resizableArray.getHeader() << std::endl;

		//Loop through and print each match
		for(int i = 0; i < printTheseValues.getNumElements(); ++i)
		{
			std::cout << printTheseValues.get(i) << std::endl;
		}

		//Tell the user how many eclipses were found
		std::cout << "Eclipses found: " << printTheseValues.getNumElements() << std::endl;
	}
}

void EclipseOperations::quickSort(int left, int right, ResizableArray<Eclipse>& resizableArray, int currentSort)
{
	if(left < right)
	{
		int pivot = (left + right) / 2;
		int i = left - 1, j = right + 1;

		do{
			do
			{
				if((i + 1) < resizableArray.getNumElements())
				{
					++i;
				}
				else
				{
					break;
				}

			} while(resizableArray.get(i).getCell(currentSort) <= resizableArray.get(pivot).getCell(currentSort) && i <= right);

			do
			{
				if(j > 0)
				{
					--j;
				}
				else
				{
					break;
				}

			} while(resizableArray.get(j).getCell(currentSort) >= resizableArray.get(pivot).getCell(currentSort) && j >= i);

			if(i < j)
			{
				resizableArray.swap(i, j);
			}
		} while(i < j);

		if(i < pivot)
		{
			j = i;
		}

		std::cout << pivot << std::endl;

		resizableArray.swap(pivot, j);

		quickSort(left, j-1, resizableArray, currentSort);
		quickSort(j+1, right, resizableArray, currentSort);
	}
}

void EclipseOperations::binarySearch(Cell needle, int col, int left, int right, ResizableArray<Eclipse>& resizableArray, ResizableArray<Eclipse>& printArray)
{
	int midpoint = (left + right) / 2;

	if(resizableArray.get(midpoint).getCell(col) == needle)//Found it!
	{
		//Look for duplicates
		int i = midpoint;

		//Find the start point of the duplicates
		while(resizableArray.get(i).getCell(col) == needle && i >= 0)
		{
			--i;
		}

		//Set the index to the first duplicate
		++i;

		//Go through all the duplicates and add them to the printArray
		while(resizableArray.get(i).getCell(col) == needle && i < resizableArray.getNumElements())
		{
			printArray.add(resizableArray.get(i));
			++i;
		}
	}
	else if(resizableArray.get(midpoint).getCell(col) < needle)
	{
		//Cut the array in half to only search the greater elements
		binarySearch(needle, col, midpoint + 1, right, resizableArray, printArray);
	}
	else if(resizableArray.get(midpoint).getCell(col) > needle)
	{
		//Cut the array in half to only look for smaller elements
		binarySearch(needle, col, left, midpoint - 1, resizableArray, printArray);
	}
}


