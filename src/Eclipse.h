/*
 * EclipseData.h
 *
 *  Created on: Sep 17, 2017
 *      Author: justin
 */

#ifndef ECLIPSE_H_
#define ECLIPSE_H_

#include <string>

class Eclipse
{
	/**
	 * Allows this class to override the << operator for stdout
	 * @param os ostream to use to output
	 * @param eclipseData the data to output
	 * @return an ostream to output through cout
	 */
	friend std::ostream&operator<<(std::ostream& os, Eclipse &eclipse);

	public:
		/**
		 * Constructor for the EclipseData data type
		 */
		Eclipse();

		/**
		 * Copy Constructor for the EclipseData data type
		 * @param eclipseData the new EclipseData to set this object to
		 */
		Eclipse(Eclipse &eclipseData);


		void operator=(const Eclipse &eclipse);

		/**
		 * Destructor
		 */
		virtual ~Eclipse();

		/**
		 * Checks to see if this object equals another EclipseData object
		 * @param eclipseData the other object
		 * @return true if equal, false if not equal
		 */
		bool equals(Eclipse eclipseData);

		/**
		 * Retrieves the catalog number of this eclipse
		 * @return catalog number
		 */
		std::string getCatalogNum() const;

		/**
		 * Sets the catalog number of this eclipse
		 * @param catalogNum the catalog number to set
		 */
		void setCatalogNum(std::string catalogNum);

		/**
		 * Gets a specific cell from this eclipse
		 * @param index the column (0 indexed) to get the data from
		 * @return the desired cell data
		 */
		std::string getCell(int index) const;

		/**
		 * Adds a cell to the EclipseData
		 * @param cell the string data to add
		 * @param index the column (0 indexed) to add it to
		 */
		void addCell(std::string cell, int index);

		/**
		 * Gets the type of the eclipse
		 * @return the type of eclipse this is
		 */
		std::string getEclipseType() const;

		/**
		 * Sets the eclipse type
		 * @param eclipseType the new eclipse type
		 */
		void setEclipseType(std::string eclipseType);

		/**
		 * Gets the number of columns in the cells array
		 * @return number of columns in the cells array
		 */
		int getNumColumns() const;

		/**
		 * Sets how many columns there are
		 * @param numColumns the number of columns there are
		 */
		void setNumColumns(int numColumns);

		void addWholeNumber(int wholeNum, int index);
		int getWholeNumber(int index) const;

		void addFloatingPoint(double floatNum, int index);
		double getFloatingPoint(int index) const;

		/**
		 *
		 * @return
		 */
		int getMonthNumber() const;

		/**
		 *
		 */
		void setMonthNumber(std::string month);

		/**
		 *
		 * @return
		 */
		std::string getRawInput() const;

		/**
		 *
		 * @param rawInput
		 */
		void setRawInput(std::string rawInput);

		void addError(int col);

		void printAllErrors();

		int getNumErrors();

		void setRow(int row);

		int getRow();


	private:

		/**
		 * The catalog number of the eclipse
		 */
		std::string catalogNum;

		/**
		 * The type of eclipse
		 */
		std::string eclipseType;

		/**
		 * The raw data
		 */
		std::string cells[24];

		int wholeNumbers[24];

		double floatingPointNumbers[24];

		bool columnErrors[24];

		int numErrors;

		int row;

		/**
		 * The number corresponding to the month of the year
		 */
		int monthNumber;

		/**
		 * How this eclipse appears in the file
		 */
		std::string rawInput;

		/**
		 * Number of columns in the raw data
		 */
		int numColumns;

		/**
		 * Number of cells allocated in memory
		 */
		int numCells;
};

#endif /* ECLIPSE_H_ */
