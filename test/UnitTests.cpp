/*
 * UnitTests.cpp
 *
 *  Created on: Sep 18, 2017
 *      Author: justin
 */

#include "UnitTests.h"

using namespace std;

UnitTests::UnitTests()
{
	cout << "Beginning Tests:\n";

	//Test the ResizableArray class
	ResizableArrayTest RATest;

	//Test the LinkedList class
	LinkedListTest LLTest;

	cout << "Testing Complete!\n";
}
