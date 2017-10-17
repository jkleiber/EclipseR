	/*
 * Cell.h
 *
 *  Created on: Oct 15, 2017
 *      Author: justin
 */

#ifndef SRC_CELL_H_
#define SRC_CELL_H_

#include <string>

#define STR_CELL 0
#define INT_CELL 1
#define FLOAT_CELL 2

class Cell {

	friend std::ostream&operator<<(std::ostream& os, const Cell& cell);

	public:
		Cell();
		Cell(const Cell& c);
		Cell(std::string data);
		Cell(int data);
		Cell(int data, bool isMax);
		Cell(double data);

		void operator=(Cell c);

		bool operator<(Cell c);
		bool operator==(Cell c);
		bool operator!=(Cell c);
		bool operator>(Cell c);
		bool operator>=(Cell c);
		bool operator<=(Cell c);

		virtual ~Cell();
	private:
		std::string strData;
		int intData;
		double floatData;

		int cellType;

		bool isMax;
};

#endif /* SRC_CELL_H_ */
