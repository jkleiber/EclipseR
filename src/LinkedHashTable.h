/*
 * LinkedHashTable.h
 *
 *  Created on: Nov 7, 2017
 *      Author: justin
 */

#ifndef SRC_LINKEDHASHTABLE_H_
#define SRC_LINKEDHASHTABLE_H_

#include <iostream>
#include "ResizableArray.h"
#include "LinkedList.h"

template <class T>
class LinkedHashTable {

	friend std::ostream& operator<<(std::ostream& os, LinkedHashTable &list)
	{
		for(int i = 0; i < list.tableSize; ++i)
		{
			os << i << " ";

			if(list.hashTable.get(i).getSize() == 0)
			{
				os << "NULL\n\n";
			}
			else
			{
				os << list.hashTable.get(i).get(0) << std::endl;

				for(int ii = 1; ii < list.hashTable.get(i).getSize(); ++ii)
				{
					if(ii == 1)
					{
						os << "OVERFLOW: \n";
					}

					os << list.hashTable.get(i).get(ii) << std::endl;
				}

				os << std::endl;
			}

		}

		return os;
	}

	public:

		LinkedHashTable()
		{
			tableSize = 0;
		}

		LinkedHashTable(int size)
		{
			tableSize = size;
			hashTable.resize(size);
		}

		LinkedHashTable(LinkedHashTable &linkedHashTable)
		{
			this->tableSize = linkedHashTable.tableSize;
			this->insertOrder = linkedHashTable.insertOrder;
			this->hashTable = linkedHashTable.hashTable;
		}

		void operator=(LinkedHashTable &linkedHashTable)
		{
			this->tableSize = linkedHashTable.tableSize;
			this->insertOrder = linkedHashTable.insertOrder;
			this->hashTable = linkedHashTable.hashTable;
		}

		void insert(int key, T value)
		{
			int index = hash(key);

			try{
				this->getChain(index).append(value);
			}
			catch(const char* message)
			{
				std::cout << "Invalid hash table input: " << message << " Index: " << index << "Table Size: " << hashTable.size() << std::endl;
			}

			insertOrder.append(value);
		}

		LinkedList<T>& getChain(int bucket)
		{
			return hashTable.get(bucket);
		}

		T& getValue(int key, T searchParams)
		{
			int index = hash(key);

			return hashTable.get(index).search(searchParams);
		}

		void clearTable()
		{
			try{
				this->hashTable.clearAll();
				this->insertOrder.clearAll();
			}
			catch(const char* msg)
			{
				std::cout << msg << std::endl;
			}
		}

		void resize(int newSize)
		{
			this->hashTable.resize(newSize);
			this->tableSize = newSize;
		}

		LinkedList<T>& getInsertionOrder()
		{
			return insertOrder;
		}

		virtual ~LinkedHashTable()
		{

		}


	private:

		ResizableArray<LinkedList<T> > hashTable;

		LinkedList<T> insertOrder;

		int tableSize;

		/**
		 *
		 * @param key
		 * @return
		 */
		int hash(int key)
		{
			return key % tableSize;
		}

};

#endif /* SRC_LINKEDHASHTABLE_H_ */
