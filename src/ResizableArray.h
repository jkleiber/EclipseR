/*
 * EclipseDataArray.h
 *
 *  Created on: Sep 16, 2017
 *      Author: justin
 */

#ifndef RESIZABLEARRAY_H_
#define RESIZABLEARRAY_H_

#include <iostream>

#include "Eclipse.h"

/**
 * Class that manages a dynamic array, and can be sorted or searched on.
 */
template<class T>
class ResizableArray {

	/**
	 * Allows this class to override the << operator for stdout
	 * @param os ostream to use to output
	 * @param eclipseData the data to output
	 * @return an ostream to output through cout
	 */
	friend std::ostream& operator<<(std::ostream& os, ResizableArray &arr)
	{
		for(int i = 0; i < arr.numElements; ++i)
		{
			os << arr.get(i) << std::endl;
		}

		return os;
	}

	public:
		/**
		 * Constructor for the array wrapper class
		 */
		ResizableArray()
		{
			//Set the array memory allocation to size 10
			this->resizableArray = new T[10];
			this->arraySize = 10;
			this->numElements = 0;
		}

		/**
		 * Constructor for the array wrapper class with a size argument
		 * @param size size of initial allocation
		 */
		ResizableArray(int size)
		{
			//Set the array memory allocation to the user specified size
			this->resizableArray = new T[size];
			this->arraySize = size;
			this->numElements = 0;
		}

		/**
		 * Copy Constructor
		 * @param arr
		 */
		ResizableArray(ResizableArray &arr)
		{
			this->resizableArray = arr.resizableArray;
			this->arraySize = arr.arraySize;
			this->numElements = arr.numElements;
		}

		/**
		 * Copy assignment operator
		 * @param arr
		 */
		void operator=(const ResizableArray &arr)
		{
			this->numElements = 0;
			allocateMemory(arr.arraySize);

			for(int i = 0; i < arr.numElements; ++i)
			{
				add(arr.resizableArray[i]);
			}

			this->arraySize = arr.arraySize;
			this->resizableArray = arr.resizableArray;
			this->numElements = arr.numElements;
		}

		/**
		 * Gets a single element from the array
		 * @param index index to get element at
		 * @return An EclipseData object
		 */
		T& get(int index)
		{
			if(index >= this->numElements || index < 0)
			{
				throw("ResizableArray::get(): Index out of range");
			}
			//Get the value from the desired index
			return this->resizableArray[index];
		}

		/**
		 * Gets the number of elements in the dynamic array
		 * @return the number of elements in the dynamic array
		 */
		int getNumElements()
		{
			return this->numElements;
		}

		/**
		 * Gets the size of the array
		 * @return size in memory of the array
		 */
		int size()
		{
			return this->arraySize;
		}

		/**
		 * Adds an element to the array
		 * @param eclipseData the element to add
		 */
		void add(T& t)
		{
			//IF the next element puts us over allocation, add more memory to the array
			if((numElements + 1) >= this->arraySize)
			{
				this->allocateMemory(this->arraySize*2);
			}

			//Add the eclipse to the array
			this->resizableArray[numElements] = t;

			//increase the number of elements counter
			++numElements;
		}

		/**
		 * Adds an element at a certain position
		 * @param t Element to add
		 * @param index position to add element
		 */
		void addAt(T t, int index)
		{
			if(index > this->numElements || index < 0)
			{
				throw("ResizableArray::addAt(): Index out of range");
			}

			//IF the next element puts us over allocation, add more memory to the array
			if((numElements + 1) >= this->arraySize)
			{
				this->allocateMemory(this->arraySize*2);
			}

			//Shift the data to make room for the new data
			this->shiftRight(index);

			//Add the eclipse to the array
			this->resizableArray[index] = t;

			//increase the number of elements counter
			++numElements;
		}

		/**
		 * Replaces a value at an index with another value
		 * @param t The value to insert
		 * @param index The index of the value to replace
		 */
		void replaceAt(T t, int index)
		{
			if(index >= this->numElements || index < 0)
			{
				throw("ResizableArray::replaceAt(): Index out of range");
			}

			//Replace the old value with the new value
			this->resizableArray[index] = t;
		}

		/**
		 * Removes an element from the array
		 * @param eclipseData the element to remove
		 */
		void removeAt(int index)
		{
			if(index >= this->numElements || index < 0)
			{
				throw("ResizableArray::removeAt(): Index out of range");
			}

			//Only delete elements if the index is in bounds
			if(index < numElements)
			{
				//Overwrite the desired element thus deleting it from the array
				this->shiftLeft(index);

				//Subtract from numElements
				--this->numElements;

				//If the threshold is now less than half, we should reallocate memory.
				if((this->numElements + 1) >= (this->arraySize / 2) && (this->numElements) < (this->arraySize / 2))
				{
					this->allocateMemory(this->arraySize / 2);
				}
			}
		}

		/**
		 * Swaps two elements at certain indices
		 * @param i index of element to swap with element at index j
		 * @param j index of element to swap with element at index i
		 */
		void swap(int i, int j)
		{
			T temp;
			temp = resizableArray[i];
			resizableArray[i] = resizableArray[j];
			resizableArray[j] = temp;
		}

		/**
		 * Destructor
		 */
		virtual ~ResizableArray()
		{
			//delete [] this->resizableArray;
		}

	private:
		/**
		 * Array of Eclipses
		 */
		T *resizableArray;

		/**
		 * Memory allocation size of array
		 */
		int arraySize;

		/**
		 * Number of elements in the array
		 */
		int numElements;


		/**
		 * Give the array a new size
		 * @param newSize the new amount of memory to allocate
		 */
		void allocateMemory(int newSize)
		{
			//Allocate a new array for the new size
			T *newArray = new T[newSize]();

			//Copy elements from the old array to the new array
			for(int i = 0; i < this->numElements; ++i)
			{
				newArray[i] = this->resizableArray[i];
			}

			//Place the old array in a trash pointer
			T *trash = this->resizableArray;

			//Change the active array pointer to the new array and update the current size
			this->resizableArray = newArray;
			this->arraySize = newSize;

			//Free the memory used by the old array
			delete [] trash;
		}

		/**
		 * Move data on top of deleted data
		 * @param index the index of the deleted data in the array
		 */
		void shiftLeft(int index)
		{

			//Start with the deleted index
			int i = index;
			for(; i < this->numElements; ++i)
			{
				//If the next element is not past the array boundaries, then shift it to the left
				if((i + 1) != this->arraySize)
				{
					this->resizableArray[i] = this->resizableArray[i + 1];
				}
			}
		}

		/**
		 * Move data on top of deleted data
		 * @param index the index of the deleted data in the array
		 */
		void shiftRight(int index)
		{
			//Start with the deleted index
			int i = index;
			for(; i < this->numElements; ++i)
			{
				//If the next element is not past the array boundaries, then shift it to the left
				if((i - 1) >= 0)
				{
					this->resizableArray[i] = this->resizableArray[i - 1];
				}
			}
		}

};


#endif /* RESIZABLEARRAY_H_ */
