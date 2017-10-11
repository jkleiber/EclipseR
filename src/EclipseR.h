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
#include "ResizableArray.h"


void dataInputLoop(ResizableArray<Eclipse>& eclipseDataArray);

void dataManipLoop(ResizableArray<Eclipse>& eclipseDataArray);


void loadFile(ResizableArray<Eclipse>& eclipseDataArray, std::string file);

bool isValid(Eclipse eclipse, int dataRow);


void processRow(std::string rawData, ResizableArray<Eclipse> & eclipseDataArray, int row);


/**
 * Checks to see if an eclipse's catalog number is unique
 * @param eclipseDataArray The entire database of eclipses
 * @param index The index of the eclipse to consider for uniqueness
 * @return -1 if the catalog number is unique, the index of the duplicate if it is repeated
 */
int isNumberUnique(ResizableArray<Eclipse> eclipseDataArray, Eclipse eclipse);

/**
 * Checks to see if a string could be a whole number
 * @param str String to check
 * @return true if the string could be an integer, false if not
 */
bool isWholeNumber(std::string str);

/**
 * Checks to see if a string could be a decimal number
 * @param str String to check
 * @return true if the string could be a floating point value, false if not
 */
bool isDecimalNumber(std::string str);

/**
 * Main function where the program runs and calls helper functions
 * @return 0 if the program completes successfully
 */
int main();


#endif /* ECLIPSER_H_ */
