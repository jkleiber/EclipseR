/*
 * EclipseData.h
 *
 *  Created on: Sep 17, 2017
 *      Author: justin
 */

#ifndef ECLIPSE_H_
#define ECLIPSE_H_

#include <string>
#include "Cell.h"

/**
 * Class that defines data from an eclipse
 */
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

		/**
		 * Copy assignment operator
		 * @param eclipse the eclipse set this one equal to
		 */
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
		Cell getCell(int index) const;

		/**
		 * Adds a cell to the EclipseData
		 * @param cell the data to add
		 * @param index the column (0 indexed) to add it to
		 */
		void addCell(Cell cell, int index);

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

		/**
		 * Returns the raw value of the row that the eclipse was generated from
		 * @return the raw data the eclipse came from
		 */
		std::string getRawInput() const;

		/**
		 * Adds the raw input row to the eclipse
		 * @param rawInput
		 */
		void setRawInput(std::string rawInput);

		/**
		 * Sets a column as having an error
		 * @param col
		 */
		void addError(int col);

		/**
		 * Prints all the errors present in the eclipse
		 */
		void printAllErrors();

		/**
		 * Gets the number of errors present
		 * @return the number of column errors in the eclipse
		 */
		int getNumErrors();

		/**
		 * Sets the data row of the eclipse
		 * @param row the row of the file the eclipse was formed from
		 */
		void setRow(int row);

		/**
		 * Gets the row the eclipse appeared on
		 * @return the row the eclipse appeared on
		 */
		int getRow();

		/**
		 * Determines if this eclipse has a lower catalog number than another
		 * @param eclipse the other eclipse
		 * @return true if this catalog number is less than the other
		 */
		bool operator<(const Eclipse& eclipse);

		/**
		 * Determines if this eclipse's catalog number is greater than another's
		 * @param eclipse the other eclipse
		 * @return true if this eclipse's catalognumber is greater
		 */
		bool operator>(const Eclipse& eclipse);

		/**
		 * Checks to see if two eclipses are equal
		 * @param eclipse the othe eclipse
		 * @return true if equal
		 */
		bool operator==(const Eclipse& eclipse);

		/**
		 * Checks to see if two eclipses are not equal
		 * @param eclipse another eclipse
		 * @return true if not equal
		 */
		bool operator!=(const Eclipse& eclipse);


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
		Cell cells[24];

		/**
		 * Array indicating if there were errors in a column or not
		 */
		bool columnErrors[24];

		/**
		 * Variable to track number of errors
		 */
		int numErrors;

		/**
		 * Row of the file this eclipse came from
		 */
		int row;

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
