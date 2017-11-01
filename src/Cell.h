	/*
 * Cell.h
 *
 *  Created on: Oct 15, 2017
 *      Author: justin
 */

#ifndef SRC_CELL_H_
#define SRC_CELL_H_

#include <iostream>
#include <string>

/**
 * Define certain numbers as strings to make code more readable
 */
#define STR_CELL 0
#define INT_CELL 1
#define FLOAT_CELL 2

/**
 * Class used to represent a single column value in an Eclipse object
 */
class Cell {

	/**
	 * Makes the Cell printable on stdout and fstream
	 * @param os ostream to output to
	 * @param cell The Cell to output
	 * @return the ostream with our output
	 */
	friend std::ostream&operator<<(std::ostream& os, const Cell& cell);

	public:
		/**
		 * Default constructor. Do not use this
		 */
		Cell();

		/**
		 * Copy Constructor
		 * @param c Cell to copy
		 */
		Cell(const Cell& c);

		/**
		 * Sets Cell as string type and loads string data
		 * @param data String data
		 */
		Cell(std::string data);

		/**
		 * Sets Cell as int type and loads int data
		 * @param data int data
		 */
		Cell(int data);

		/**
		 * Sets Cell as int type and loads int data. Allows user to set if this is a max value
		 * @param data data to load
		 * @param isMax is this a maximum int value
		 */
		Cell(int data, bool isMax);

		/**
		 * Sets Cell as a double type and loads double data
		 * @param data the data to load
		 */
		Cell(double data);

		/**
		 * Copy assignment operator
		 * @param c Cell to copy
		 */
		void operator=(Cell c);

		/**
		 * Less than comparator
		 * @param c Cell to compare
		 * @return this Cell < Cell c?
		 */
		bool operator<(const Cell& c);

		/**
		 * Equals comparator
		 * @param c Cell to compare
		 * @return this Cell == Cell c
		 */
		bool operator==(const Cell& c);

		/**
		 * Not equals comparator
		 * @param c Cell to compare
		 * @return this Cell != Cell c
		 */
		bool operator!=(const Cell& c);

		/**
		 * Greater than comparator
		 * @param c Cell to compare
		 * @return this Cell > Cell c
		 */
		bool operator>(const Cell& c);

		/**
		 * Greater than or equal comparator
		 * @param c Cell to compare
		 * @return this Cell >= Cell c
		 */
		bool operator>=(const Cell& c);

		/**
		 * Less than or equal comparator
		 * @param c Cell to compare
		 * @return this Cell <= Cell c
		 */
		bool operator<=(const Cell& c);

		/**
		 * Destructor
		 */
		virtual ~Cell();

	private:

		/**
		 * String representation of the data
		 */
		std::string strData;

		/**
		 * Integer representation of data
		 */
		int intData;

		/**
		 * Double representation of data
		 */
		double floatData;

		/**
		 * Cell data type (String, int or double)
		 */
		int cellType;

		/**
		 * Is this the maximum value of the data type
		 */
		bool isMax;
};

#endif /* SRC_CELL_H_ */
