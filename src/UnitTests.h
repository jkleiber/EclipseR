/*
 * UnitTests.h
 *
 *  Created on: Sep 18, 2017
 *      Author: justin
 */

#ifndef UNITTESTS_H_
#define UNITTESTS_H_

#include <iostream>
#include <iomanip>
#include <string>

#include "Eclipse.h"
#include "ResizableArray.h"

class UnitTests {
	public:
		UnitTests();

	private:
		bool doesDefaultConstructorWork(ResizableArray<Eclipse> eda);
		bool doesOtherConstructorWork(ResizableArray<Eclipse> eda, int size);
		bool doesAddGetWork(ResizableArray<Eclipse> eda, Eclipse eD);

};

#endif /* UNITTESTS_H_ */
