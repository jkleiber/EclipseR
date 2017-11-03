/*
 * ResizableArrayTest.h
 *
 *  Created on: Nov 2, 2017
 *      Author: justin
 */

#ifndef SRC_RESIZABLEARRAYTEST_H_
#define SRC_RESIZABLEARRAYTEST_H_

#include <iostream>
#include <iomanip>
#include <string>

#include "../src/Eclipse.h"
#include "../src/ResizableArray.h"

class ResizableArrayTest {
	public:
		ResizableArrayTest();
		virtual ~ResizableArrayTest();

	private:
		bool doesDefaultConstructorWork(ResizableArray<Eclipse> eda);
		bool doesOtherConstructorWork(ResizableArray<Eclipse> eda, int size);
		bool doesAddGetWork(ResizableArray<Eclipse> eda, Eclipse eD);
};

#endif /* SRC_RESIZABLEARRAYTEST_H_ */
