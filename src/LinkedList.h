/*
 * LinkedList.h
 *
 *  Created on: Oct 28, 2017
 *      Author: justin
 */

#ifndef SRC_LINKEDLIST_H_
#define SRC_LINKEDLIST_H_

#include <iostream>
#include "ResizableArray.h"

template<class T>
class LinkedList {

	/**
	 * The struct that defines what a list node looks like
	 */
	struct node {
		T data;
		node* next;
	};

	/**
	 * Allows this class to override the << operator for stdout
	 * @param os ostream to use to output
	 * @param eclipseData the data to output
	 * @return an ostream to output through cout
	 */
	friend std::ostream& operator<<(std::ostream& os, LinkedList<T> &list)
	{
		node *currentNode = new node;
		currentNode = list.head;

		while(currentNode != NULL)
		{
			os << currentNode->data << std::endl;
			currentNode = currentNode->next;
		}

		return os;
	}

	public:
		LinkedList()
		{
			this->head = new node;
			head = NULL;

			this->listSize = 0;
		}

		void add(T t)
		{
			node *currentNode = new node;
			node *lastNode = new node;

			currentNode = this->head;
			lastNode = this->head;

			if(currentNode != NULL)
			{
				while(currentNode != NULL)
				{
					if(currentNode->data > t || currentNode->data == t)
					{
						break;
					}
					else
					{
						lastNode = currentNode;
						currentNode = currentNode->next;
					}
				}
			}

			//If we are inserting the new node at the end of the list
			if(currentNode == NULL)
			{
				node *newNode = new node;

				newNode->data = t;
				if(head == NULL)
				{
					head = newNode;
				}
				else
				{
					lastNode->next = newNode;
				}
			}
			//Replace a duplicate entry
			else if(currentNode->data == t)
			{
				currentNode->data = t;
			}
			//Insert into the middle of the list
			else
			{
				node *newNode = new node;

				newNode->data = t;
				if(currentNode == head)
				{
					newNode->next = head;
					head = newNode;
				}
				else
				{
					newNode->next = currentNode;
					lastNode->next = newNode;
				}
			}

			listSize++;
		}

		/**
		 *
		 * @param t
		 * @return
		 */
		bool remove(T t)
		{
			node *currentNode = new node;
			node *lastNode = new node;

			currentNode = this->head;
			lastNode = this->head;

			while(currentNode->data < t && currentNode != NULL)
			{
				lastNode = currentNode;
				currentNode = currentNode->next;
			}

			//If the end of the list was not reached
			if(currentNode != NULL)
			{
				//was the element found?
				if(currentNode->data == t)
				{
					lastNode->next = currentNode->next;
					listSize--;

					return true;
				}
			}
			return false;
		}

		bool doesValueExist(T t)
		{
			node *currentNode = new node;
			currentNode = head;

			if(currentNode != NULL)
			{
				while((currentNode != NULL))
				{
					if(currentNode->data != t)
					{
						currentNode = currentNode->next;
					}
					else
					{
						return true;
					}
				}
			}

			return false;
		}

		void buildArray(ResizableArray<T>& array)
		{
			array.clearAll();

			node *currentNode = new node;
			currentNode = this->head;

			if(currentNode != NULL)
			{
				while(currentNode != NULL)
				{
					array.add(currentNode->data);

					currentNode = currentNode->next;
				}
			}
		}

		/**
		 *
		 * @return
		 */
		int getSize()
		{
			return this->listSize;
		}

		virtual ~LinkedList()
		{

		}

	private:

		node *head;


		int listSize;
};

#endif /* SRC_LINKEDLIST_H_ */
