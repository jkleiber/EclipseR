/*
 * FileInput.h
 *
 *  Created on: Oct 12, 2017
 *      Author: justin
 */

#ifndef SRC_FILEINPUT_H_
#define SRC_FILEINPUT_H_

#include <iostream>
#include <string>
#include <fstream>
#include "ResizableArray.h"

#include "Cell.h"
#include "Eclipse.h"


class FileInput {
	public:
		/**
		 * Construct the FileInput object
		 */
		FileInput();

		/**
		 * Load a file into the eclipse array
		 * @param eclipseDataArray The array
		 * @param file The file to load
		 */
		void loadFile(ResizableArray<Eclipse>& eclipseDataArray, std::string file);

		/**
		 * Gets the number of valid eclipses read
		 * @return The number of valid eclipses
		 */
		int getNumValid() const;

		/**
		 * Gets the total number of eclipses read
		 * @return The number of eclipses read
		 */
		int getTotal() const;

		/**
		 * Convert a string to an int
		 * @param str String to convert
		 * @return the int version of the string
		 * @throws an exception if the string is not a valid integer
		 */
		int convertStrToInt(std::string str);

		/**
		 * Convert a string to a double
		 * @param str String to convert
		 * @return the double version of the string
		 * @throws an exception if the string is not a valid double
		 */
		double convertStrToDouble(std::string str);

		/**
		 * Destructor
		 */
		virtual ~FileInput();

	private:

		/**
		 * Tracks total number of elements read
		 */
		int totalElementsRead;

		/**
		 * Tracks the number of valid elements read
		 */
		int validElementsRead;

		/**
		 * Error checking for each eclipse
		 * @param eclipse The eclipse to check
		 * @param dataRow The row of the file the eclipse is on
		 * @return true if the eclipse is valid, false if not
		 */
		bool isValid(Eclipse eclipse, int dataRow);

		/**
		 * Process raw row data into an Eclipse object and add that to the array
		 * @param rawData raw string of row data
		 * @param eclipseDataArray Array of all eclipses
		 * @param row the current row of the file we are on
		 */
		void processRow(std::string rawData, ResizableArray<Eclipse> & eclipseDataArray, int row);

		/**
		 * Checks to see if an eclipse's catalog number is unique
		 * @param eclipseDataArray The entire database of eclipses
		 * @param index The index of the eclipse to consider for uniqueness
		 * @return -1 if the catalog number is unique, the index of the duplicate if it is repeated
		 */
		int isNumberUnique(ResizableArray<Eclipse> eclipseDataArray, Eclipse eclipse);

		/**
		 * Checks to see if a character is a number or not
		 * @param c character to check
		 * @return true if the character is a number, false otherwise
		 */
		bool isNumber(char c);
};



#endif /* SRC_FILEINPUT_H_ */
