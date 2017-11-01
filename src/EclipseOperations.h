/*
 * EclipseOperations.h
 *
 *  Created on: Oct 16, 2017
 *      Author: justin
 */

#ifndef SRC_ECLIPSEOPERATIONS_H_
#define SRC_ECLIPSEOPERATIONS_H_

#include <string>
#include "FileInput.h"
#include "ResizableArray.h"
#include "Eclipse.h"
#include "Cell.h"

/**
 * Class used to sort and search the resizable aray of eclipses
 */
class EclipseOperations {
	public:
		/**
		 * Constructor
		 */
		EclipseOperations();

		/**
		 * User visible sort function. Starting point for the quicksort algorithm we have.
		 * @param col The column to sort
		 * @param resizableArray The array to sort
		 */
		void sort(int col, ResizableArray<Eclipse>& resizableArray);

		/**
		 * User visible entry point for finding elements in an array. Start point for binary and linear search
		 * @param col The column to search on
		 * @param value The value to search for
		 * @param resizableArray The array to search on
		 */
		void find(int col, Cell value, ResizableArray<Eclipse>& resizableArray, FileInput fileInput);

		/**
		 *
		 * @param col
		 */
		void setSortedColumn(int col);

		/**
		 * Destructor
		 */
		virtual ~EclipseOperations();

	private:
		/**
		 * Performs Quicksort on an array of Eclipses
		 * @param left The left boundary of the subarray
		 * @param right The right boundary of the sub array
		 * @param resizableArray The array to sort
		 * @param currentSort The column to sort
		 */
		void quickSort(int left, int right, ResizableArray<Eclipse>& resizableArray, int currentSort);

		/**
		 * Performs a binary search for multiple items of the same value
		 * @param needle Value to look for
		 * @param col Column of the array to look in
		 * @param left The left side of the searchable zone
		 * @param right The right side of the searchable zone
		 * @param resizableArray The array to search on
		 * @param printArray The array to store all found values in
		 */
		void binarySearch(Cell needle, int col, int left, int right, ResizableArray<Eclipse>& resizableArray, ResizableArray<Eclipse>& printArray);

		/**
		 * Keeps track of the currently sorted column
		 */
		int currentSort;
};

#endif /* SRC_ECLIPSEOPERATIONS_H_ */
