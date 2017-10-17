/*
 * EclipseOperations.h
 *
 *  Created on: Oct 16, 2017
 *      Author: justin
 */

#ifndef SRC_ECLIPSEOPERATIONS_H_
#define SRC_ECLIPSEOPERATIONS_H_

#include <string>
#include "ResizableArray.h"
#include "Eclipse.h"
#include "Cell.h"

class EclipseOperations {
	public:
		EclipseOperations();

		void sort(int col, ResizableArray<Eclipse>& resizableArray);
		void find(int col, Cell value, ResizableArray<Eclipse>& resizableArray);

		virtual ~EclipseOperations();

	private:
		void quickSort(int left, int right, ResizableArray<Eclipse>& resizableArray, int currentSort);
		void binarySearch(Cell needle, int col, int left, int right, ResizableArray<Eclipse>& resizableArray, ResizableArray<Eclipse>& printArray);
		int currentSort;
};

#endif /* SRC_ECLIPSEOPERATIONS_H_ */
