/*
 * LinkedHashTable.h
 *
 *  Created on: Nov 7, 2017
 *      Author: justin
 */

#ifndef SRC_LINKEDHASHTABLE_H_
#define SRC_LINKEDHASHTABLE_H_

#include <iostream>

template <class T>
class LinkedHashTable {

	friend std::ostream& operator<<(std::ostream& os, LinkedHashTable<T> &list)
	{

		return os;
	}

	public:
		LinkedHashTable();

		void add(int key, T value)
		{
			int index = hash(key);

		}

		void get(int key)
		{
			int index = hash(key);
		}

		virtual ~LinkedHashTable();
	private:

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
