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
	addTestArray.Add(eD);
	if(!doesAddGetWork(eda2, eD))
	{
		cout << "\tFAIL: Add/Get Element Test\n";
	}

	//Add Memory Allocation Test
	ResizableArray<Eclipse> dataArray;
	Eclipse e;

	for(int i = 0; i < 100; ++i)
	{
		dataArray.Add(e);
	}
	if(dataArray.GetNumElements() != 100 || dataArray.size() != 160)
	{
		cout << "\tFAIL: Add Memory Allocation Test\n";
	}

	//Remove Memory Allocation Test
	ResizableArray<Eclipse> dataArray2;
	Eclipse ed;
	for(int i = 0; i < 100; ++i)
	{
		dataArray2.Add(ed);
	}

	for(int i = 0; i < 55; ++i)
	{
		dataArray2.RemoveAt(0);
	}

	if(dataArray2.GetNumElements() != 45 || dataArray2.size() != 80)
	{
		cout << "\tFAIL: Remove Memory Allocation Test\n";
	}

	//Throw exception test
	ResizableArray<Eclipse> dataArray3;
	Eclipse eclipse;
	//Get
	try{
		eclipse = dataArray3.Get(5);
		cout << "\tFAIL: Out of Range Test 1\n";
	}
	catch(const char* e)
	{

	}

	//RemoveAt
	try{
		dataArray3.RemoveAt(5);
		cout << "\tFAIL: Out of Range Test 1\n";
	}
	catch(const char* e)
	{

	}

	//AddAt
	Eclipse z;
	try{
		dataArray3.AddAt(z, 5);
		cout << "\tFAIL: Out of Range Test 1\n";
	}
	catch(const char* e)
	{

	}


	cout << "Testing Complete!\n";
}


bool UnitTests::doesDefaultConstructorWork(ResizableArray<Eclipse> eda)
{
	if(eda.GetNumElements() != 0 || eda.size() != 10)
	{
		return false;
	}
	return true;
}

bool UnitTests::doesOtherConstructorWork(ResizableArray<Eclipse> eda, int size)
{
	if(eda.GetNumElements() != 0 || eda.size() != size)
	{
		return false;
	}
	return true;
}

bool UnitTests::doesAddGetWork(ResizableArray<Eclipse> eda, Eclipse eD)
{
	if(eda.Get(0).Equals(eD))
	{
		return true;
	}
	return false;
}
