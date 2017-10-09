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

/**
 * Checks to see if there are errors in the data
 * @param eclipseDataArray the whole database of eclipses
 */
void CheckForErrors(ResizableArray<Eclipse> & eclipseDataArray);

/**
 * Processes a raw data string into usable modular data
 * @param rawData the raw input
 * @param eclipseDataArray The data structure that contains all the eclipses
 */
void ProcessRow(std::string rawData, ResizableArray<Eclipse> & eclipseDataArray);

/**
 * Checks to see if an eclipse's catalog number is unique
 * @param eclipseDataArray The entire database of eclipses
 * @param index The index of the eclipse to consider for uniqueness
 * @return true if the catalog number is unique, false if it is repeated
 */
bool isNumberUnique(ResizableArray<Eclipse> eclipseDataArray, int index);

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
