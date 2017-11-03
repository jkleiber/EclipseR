/*
 * LinkedListTest.cpp
 *
 *  Created on: Nov 2, 2017
 *      Author: justin
 */

#include "LinkedListTest.h"

LinkedListTest::LinkedListTest()
{
	Eclipse a;
	Cell z(1);
	a.addCell(z, 0);

	Eclipse b;
	Cell y(2);
	b.addCell(y, 0);

	//Test single insert
	LinkedList<Eclipse> list1;
	list1.add(a);
	if(list1.getSize() <= 0 || list1.get(0) != a)
	{
		std::cout << "\tFAIL: Linked List add test 1\n";
	}

	//Check ordering
	LinkedList<Eclipse> list2;
	list2.add(a);
	list2.add(b);
	if(list2.getSize() != 2 || list2.get(0) != a || list2.get(1) != b)
	{
		std::cout << "\tFAIL: Linked List add test 2\n";
	}

	//Test remove
	LinkedList<Eclipse> list3;
	list3.add(a);
	list3.add(b);
	list3.remove(a);
	if(list3.getSize() != 1 || list3.get(0) != b)
	{
		std::cout << "\tFAIL: Linked List remove test\n";
	}
}

LinkedListTest::~LinkedListTest() {
	// TODO Auto-generated destructor stub
}

