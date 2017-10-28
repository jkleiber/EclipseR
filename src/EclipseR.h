/*
 * EclipseR.h
 *
 *  Created on: Sep 11, 2017
 *      Author: justin
 */

#ifndef ECLIPSER_H_
#define ECLIPSER_H_

#include <string>

#include "Eclipse.h"
#include "FileInput.h"
#include "ResizableArray.h"
#include "LinkedList.h"
#include "EclipseOperations.h"

/**
 * The loop that runs while the program collects data from the user
 * @param eclipseDataArray The data array to construct
 * @param fileInput The file input helper object
 */
void dataInputLoop(LinkedList<Eclipse>& eclipseDataArray, FileInput& fileInput);

/**
 * Loop that runs while the user manipulates data
 * @param eclipseDataArray the data array to manipulate
 * @param fileInput the file input helper object
 */
void dataManipLoop(LinkedList<Eclipse>& eclipseDataArray, FileInput& fileInput);

/**
 * Main function where the program runs and calls helper functions
 * @return 0 if the program completes successfully
 */
int main();


#endif /* ECLIPSER_H_ */
