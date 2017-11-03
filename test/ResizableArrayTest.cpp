/*
 * ResizableArrayTest.cpp
 *
 *  Created on: Nov 2, 2017
 *      Author: justin
 */

#include "ResizableArrayTest.h"
using namespace std;

ResizableArrayTest::ResizableArrayTest() {

	//Default Constructor test
	ResizableArray<Eclipse> eda1;
	if(!doesDefaultConstructorWork(eda1))
	{
		cout << "\tFAIL: Default Constructor Test\n";
	}

	//Default Constructor test
	ResizableArray<Eclipse> eda2(20);
	if(!doesOtherConstructorWork(eda2, 20))
	{
		cout << "\tFAIL: Other Constructor Test\n";
	}

	//Add and Get Element Test
	ResizableArray<Eclipse> addTestArray;
	Eclipse eD;
	addTestArray.add(eD);
	if(!doesAddGetWork(addTestArray, eD))
	{
		cout << "\tFAIL: Add/Get Element Test\n";
	}

	//Add Memory Allocation Test
	ResizableArray<Eclipse> dataArray;
	Eclipse e;

	for(int i = 0; i < 100; ++i)
	{
		dataArray.add(e);
	}
	if(dataArray.getNumElements() != 100 || dataArray.size() != 160)
	{
		cout << "\tFAIL: Add Memory Allocation Test\n";
	}

	//Remove Memory Allocation Test
	ResizableArray<Eclipse> dataArray2;
	Eclipse ed;
	for(int i = 0; i < 100; ++i)
	{
		dataArray2.add(ed);
	}

	for(int i = 0; i < 55; ++i)
	{
		dataArray2.removeAt(0);
	}

	if(dataArray2.getNumElements() != 45 || dataArray2.size() != 80)
	{
		cout << "\tFAIL: Remove Memory Allocation Test\n";
	}

	//Throw exception test
	ResizableArray<Eclipse> dataArray3;
	Eclipse eclipse;
	//Get
	try{
		eclipse = dataArray3.get(5);
		cout << "\tFAIL: Out of Range Test 1\n";
	}
	catch(const char* e)
	{

	}

	//RemoveAt
	try{
		dataArray3.removeAt(5);
		cout << "\tFAIL: Out of Range Test 2\n";
	}
	catch(const char* e)
	{

	}

	//AddAt
	Eclipse z;
	try{
		dataArray3.addAt(z, 5);
		cout << "\tFAIL: Out of Range Test 3\n";
	}
	catch(const char* e)
	{

	}

}



bool ResizableArrayTest::doesDefaultConstructorWork(ResizableArray<Eclipse> eda)
{
	if(eda.getNumElements() != 0 || eda.size() != 10)
	{
		return false;
	}
	return true;
}

bool ResizableArrayTest::doesOtherConstructorWork(ResizableArray<Eclipse> eda, int size)
{
	if(eda.getNumElements() != 0 || eda.size() != size)
	{
		return false;
	}
	return true;
}

bool ResizableArrayTest::doesAddGetWork(ResizableArray<Eclipse> eda, Eclipse eD)
{
	if(eda.get(0).equals(eD))
	{
		return true;
	}
	return false;
}


ResizableArrayTest::~ResizableArrayTest() {
	// TODO Auto-generated destructor stub
}

