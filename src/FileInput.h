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
#include "Eclipse.h"


class FileInput {
	public:
		FileInput();

		void loadFile(ResizableArray<Eclipse>& eclipseDataArray, std::string file);

		int getNumValid() const;

		int getTotal() const;

		virtual ~FileInput();

	private:

		int totalElementsRead;
		int validElementsRead;

		bool isValid(Eclipse eclipse, int dataRow);

		void processRow(std::string rawData, ResizableArray<Eclipse> & eclipseDataArray, int row);

		/**
		 * Checks to see if an eclipse's catalog number is unique
		 * @param eclipseDataArray The entire database of eclipses
		 * @param index The index of the eclipse to consider for uniqueness
		 * @return -1 if the catalog number is unique, the index of the duplicate if it is repeated
		 */
		int isNumberUnique(ResizableArray<Eclipse> eclipseDataArray, Eclipse eclipse);


		bool isNumber(char c);


		int convertStrToInt(std::string str);

		double convertStrToDouble(std::string str);
};



#endif /* SRC_FILEINPUT_H_ */
