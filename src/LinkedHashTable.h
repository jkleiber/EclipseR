/*
 * LinkedHashTable.h
 *
 *  Created on: Nov 7, 2017
 *      Author: justin
 */

#ifndef SRC_LINKEDHASHTABLE_H_
#define SRC_LINKEDHASHTABLE_H_

#include <iostream>

#include "LinkedList.h"

template <class T>
class LinkedHashTable {

	friend std::ostream& operator<<(std::ostream& os, LinkedHashTable<T> &list)
	{

		return os;
	}

	public:

		LinkedHashTable()
		{
			tableSize = 0;
		}

		LinkedHashTable(LinkedHashTable<T> linkedHashTable)
		{
			this->tableSize = linkedHashTable.tableSize;
			this->insertOrder = linkedHashTable.insertOrder;
			this->hashTable = linkedHashTable.hashTable;
		}

		void operator=(LinkedHashTable<T> linkedHashTable)
		{
			this->tableSize = linkedHashTable.tableSize;
			this->insertOrder = linkedHashTable.insertOrder;
			this->hashTable = linkedHashTable.hashTable;
		}

		void insert(int key, T value)
		{
			int index = hash(key);

			hashTable.get(index).add(value);

			insertOrder.add(value);
		}

		T& get(int key, T searchParams)
		{
			int index = hash(key);

			return hashTable.get(index).search(searchParams);
		}

		void clearTable()
		{
			this->hashTable.clearAll();
		}

		void resize(int newSize)
		{
			this->hashTable.resize(newSize);
		}

		LinkedList<T>& getInsertionOrder()
		{
			return insertOrder;
		}

		virtual ~LinkedHashTable()
		{

		}


	private:

		ResizableArray<LinkedList<T>> hashTable;

		LinkedList<T> insertOrder;

		int tableSize;

		/**
		 *
		 * @param key
		 * @return
		 */
		int hash(T key)
		{
			return 0;
		}

};

#endif /* SRC_LINKEDHASHTABLE_H_ */
