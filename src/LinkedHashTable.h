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

/**
 * Templated class for storing values in a hash table for fast lookup times
 */
template <class T>
class LinkedHashTable {

	/**
	 * Outputs the contents of the hash table
	 * @param os the stream to output to
	 * @param list the hash table list
	 * @return the stream for output
	 */
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
		/**
		 * Constructs the hash table with 0 size
		 */
		LinkedHashTable()
		{
			tableSize = 0;
		}

		/**
		 * Constructs a hash table with size size
		 * @param size
		 */
		LinkedHashTable(int size)
		{
			tableSize = size;
			hashTable.resize(size);
		}

		/**
		 * Copy constructr
		 * @param linkedHashTable the hash table to copy
		 */
		LinkedHashTable(LinkedHashTable &linkedHashTable)
		{
			this->tableSize = linkedHashTable.tableSize;
			this->insertOrder = linkedHashTable.insertOrder;
			this->hashTable = linkedHashTable.hashTable;
		}

		/**
		 * Copy assignment operator
		 * @param linkedHashTable the hash table to copy
		 */
		void operator=(LinkedHashTable &linkedHashTable)
		{
			this->tableSize = linkedHashTable.tableSize;
			this->insertOrder = linkedHashTable.insertOrder;
			this->hashTable = linkedHashTable.hashTable;
		}

		/**
		 * Insert a value into the hash table based on its key
		 * @param key the identifier used to look up the value
		 * @param value the item to insert
		 */
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

		/**
		 * Gets the chain attached to the bucket, where the head is the bucket
		 * @param bucket the index of the bucket to look for
		 * @return a linked list of eclipses that forms the chain
		 */
		LinkedList<T>& getChain(int bucket)
		{
			return hashTable.get(bucket);
		}

		/**
		 * Find a value in the hash table given a key and some search parameters
		 * @param key the identifier used to find the value
		 * @param searchParams a lookalike to the value that is not identical, used for comparisons
		 * @return the value if found
		 * @throws an exception if nothing is found
		 */
		T& getValue(int key, T searchParams)
		{
			int index = hash(key);

			return hashTable.get(index).search(searchParams);
		}

		/**
		 * Removes everything from the table
		 */
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

		/**
		 * Changes the size of the table
		 * @param newSize the new size of the table
		 */
		void resize(int newSize)
		{
			this->hashTable.resize(newSize);
			this->tableSize = newSize;
		}

		/**
		 * Return the linked list of insertion order
		 * @return the insertion order
		 */
		LinkedList<T>& getInsertionOrder()
		{
			return insertOrder;
		}

		virtual ~LinkedHashTable()
		{

		}


	private:

		/**
		 * Variable used to store the actual hash table
		 */
		ResizableArray<LinkedList<T> > hashTable;

		/**
		 * The linked list for insertion order
		 */
		LinkedList<T> insertOrder;

		/**
		 * Variable that tracks table size
		 */
		int tableSize;

		/**
		 * Hash the value's key to determine where to place the value
		 * @param key the key to hash
		 * @return the index where the value belongs
		 */
		int hash(int key)
		{
			return key % tableSize;
		}

};

#endif /* SRC_LINKEDHASHTABLE_H_ */
