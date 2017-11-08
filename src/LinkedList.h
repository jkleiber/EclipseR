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

/**
 * Class that manages a linked list of any type, and keeps it in a sorted order
 */
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
		/**
		 * Constructor of the linked list. Sets the head pointer to NULL for later additions
		 */
		LinkedList()
		{
			this->head = new node;
			head = NULL;

			this->listSize = 0;
		}

		void operator=(LinkedList<T> linkedList)
		{
			node* currentNode = head;
			node* throwaway = new node;

			while(currentNode != NULL)
			{
				throwaway = currentNode;
				currentNode = currentNode->next;
				delete throwaway;
			}

			this->head = linkedList.head;

			this->listSize = linkedList.listSize;
		}

		/**
		 * Adds an element to the list
		 * @param t the element to add
		 */
		void add(T t)
		{
			node *currentNode = new node;
			node *lastNode = new node;

			//start from the head node
			currentNode = this->head;
			lastNode = this->head;

			//while we haven't reached the end of the list
			while(currentNode != NULL)
			{
				//stop looking for the insert location if it has been found
				if(currentNode->data > t || currentNode->data == t)
				{
					break;
				}
				else //iterate
				{
					lastNode = currentNode;
					currentNode = currentNode->next;
				}
			}

			//If we are inserting the new node at the end of the list
			if(currentNode == NULL)
			{
				node *newNode = new node;

				newNode->data = t;
				if(head == NULL)//special case for empty list
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
				if(currentNode == head)//special case for insert at front
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

			//increment list size
			listSize++;
		}

		/**
		 * Removes an element from the list
		 * @param t the element to remove
		 * @return true if the element was removed. false if not removed
		 */
		bool remove(T t)
		{
			node *currentNode = new node;
			node *lastNode = new node;

			currentNode = this->head;
			lastNode = this->head;

			while(currentNode != NULL)
			{
				if(currentNode->data < t)
				{
					lastNode = currentNode;
					currentNode = currentNode->next;
				}
				else
				{
					break;
				}
			}

			//If the end of the list was not reached
			if(currentNode != NULL)
			{
				node *throwaway = new node;

				//was the element found?
				if(currentNode->data == t)
				{
					if(currentNode == head)
					{
						throwaway = head;
						head = head->next;
					}
					else
					{
						throwaway = currentNode;
						lastNode->next = currentNode->next;
					}
					listSize--;

					delete throwaway; //Free the deleted node from memory

					return true;
				}
			}
			return false;
		}

		/**
		 * Gets the value at the specified position in the list
		 * @param position the position to get from the list
		 * @return the element in the list. NULL if OOB
		 */
		T& get(int position)
		{
			int i = 0;
			node *currentNode = new node;
			currentNode = head;

			while(currentNode != NULL)
			{
				if(i == position)
				{
					break;
				}

				currentNode = currentNode->next;
				++i;
			}

			if(currentNode != NULL)
			{
				return currentNode->data;
			}

			std::cout << i << std::endl;

			throw("LinkedList::get(): Index out of range");
		}

		T& search(T key)
		{
			node* currentNode = head;

			while(currentNode != NULL)
			{
				if(currentNode->data == key)
				{
					return currentNode->data;
				}

				currentNode = currentNode->next;
			}

			return NULL;
		}

		/**
		 * Checks to see if an element exists in the list
		 * @param t the element to look for
		 * @return true if found, false if not found
		 */
		bool doesValueExist(T t)
		{
			node *currentNode = new node;
			currentNode = head;

			//look for t until it is found or the end of the list is reached
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

			return false;
		}

		/**
		 * Converts the list into an array
		 * @return the resizable array created from the linked list
		 */
		ResizableArray<T> buildArray()
		{
			ResizableArray<T> array(listSize);

			node *currentNode = new node;
			currentNode = this->head;

			//go through the whole list
			while(currentNode != NULL)
			{
				array.add(currentNode->data);

				currentNode = currentNode->next;
			}

			return array;
		}

		/**
		 * Gives the size of the list
		 * @return
		 */
		int getSize()
		{
			return this->listSize;
		}

		/**
		 * Frees all the nodes from memory
		 */
		virtual ~LinkedList()
		{
			node* currentNode = head;
			while(currentNode != NULL)
			{
				head = currentNode->next;
				delete currentNode;
				currentNode = head;
			}
		}

	private:
		/**
		 * The head node of the list
		 */
		node *head;

		/**
		 * the size of the list
		 */
		int listSize;
};

#endif /* SRC_LINKEDLIST_H_ */
