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

template<typename T>
class LinkedList;

template<typename T>
std::ostream& operator<<(std::ostream& os, LinkedList<T> &list);

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
	friend std::ostream& operator<< <T>(std::ostream& os, LinkedList<T> &list);

	public:
		/**
		 * Constructor of the linked list. Sets the head pointer to NULL for later additions
		 */
		LinkedList();

		/**
		 * Copy assignment operator
		 * @param linkedList the linked list to copy
		 */
		void operator=(LinkedList<T> linkedList);

		/**
		 * Adds an element to the list
		 * @param t the element to add
		 */
		void add(T &t);

		/**
		 * Adds an item to the tail of the linked list
		 * @param t the item to add
		 */
		void append(T &t);

		/**
		 * Removes an element from the list
		 * @param t the element to remove
		 * @return true if the element was removed. false if not removed
		 */
		bool remove(T t);

		/**
		 * Gets the value at the specified position in the list
		 * @param position the position to get from the list
		 * @return the element in the list. NULL if OOB
		 */
		T& get(int position);

		/**
		 * Searches the linked list for a particular value and returns it
		 * @param id value to search for
		 * @return the item found
		 * @throws an exception if nothing is found
		 */
		T& search(T id);

		/**
		 * Checks to see if an element exists in the list
		 * @param t the element to look for
		 * @return true if found, false if not found
		 */
		bool doesValueExist(T t);

		/**
		 * Converts the list into an array
		 * @return the resizable array created from the linked list
		 */
		ResizableArray<T> buildArray();

		/**
		 * Gives the size of the list
		 * @return
		 */
		int getSize();

		/**
		 * Deletes all the nodes from the list
		 */
		void clearAll();

		/**
		 * Frees all the nodes from memory
		 */
		virtual ~LinkedList();

	private:
		/**
		 * The head node of the list
		 */
		node *head;

		/**
		 * The tail of the linked list
		 */
		node *tail;

		/**
		 * the size of the list
		 */
		int listSize;
};

template<typename T>
std::ostream& operator<<(std::ostream& os, LinkedList<T> &list)
{
	typename LinkedList<T>::node* currentNode = new typename LinkedList<T>::node;
	currentNode = list.head;

	while(currentNode != NULL)
	{
		os << currentNode->data << std::endl;
		currentNode = currentNode->next;
	}

	return os;
}

/**
 * PUBLIC FUNCTIONS
 */

template<class T>
LinkedList<T>::LinkedList()
{
	this->head = new node;
	head = NULL;

	this->tail = new node;
	tail = NULL;

	this->listSize = 0;
}

template<class T>
void LinkedList<T>::operator=(LinkedList<T> linkedList)
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
	this->tail = linkedList.tail;

	this->listSize = linkedList.listSize;
}

template<class T>
void LinkedList<T>::add(T &t)
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
		newNode->next = NULL;
		if(head == NULL)//special case for empty list
		{
			head = newNode;
			tail = newNode;
		}
		else
		{
			lastNode->next = newNode;
			tail = newNode;
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

template<class T>
void LinkedList<T>::append(T &t)
{
	node* newNode = new node;
	newNode->data = t;
	newNode->next = NULL;

	if(tail != NULL)
	{
		tail->next = newNode;
	}
	if(head == NULL)
	{
		head = newNode;
	}
	tail = newNode;

	listSize++;
}

template<class T>
bool LinkedList<T>::remove(T t)
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
			else if(currentNode == tail)
			{
				throwaway = tail;
				tail = lastNode;
			}
			else
			{
				throwaway = currentNode;
				lastNode->next = currentNode->next;
			}
			listSize--;

			delete throwaway; //Free the deleted node from memory
			throwaway = NULL;

			return true;
		}
	}
	return false;
}

template<class T>
T& LinkedList<T>::get(int position)
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

	throw("LinkedList::get(): Index out of range");
}

template<class T>
T& LinkedList<T>::search(T id)
{
	node* currentNode = head;

	while(currentNode != NULL)
	{
		if(currentNode->data == id)
		{
			return currentNode->data;
		}

		currentNode = currentNode->next;
	}

	throw("No value found.\n");
}

template<class T>
bool LinkedList<T>::doesValueExist(T t)
{
	node *currentNode = new node;
	currentNode = head;

	//look for t until it is found or the end of the list is reached
	while(currentNode != NULL)
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

template<class T>
ResizableArray<T> LinkedList<T>::buildArray()
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

template<class T>
int LinkedList<T>::getSize()
{
	return this->listSize;
}

template<class T>
void LinkedList<T>::clearAll()
{
	node *throwaway = new node;
	node *currentNode = new node;

	currentNode = head;

	while(currentNode != NULL)
	{
		throwaway = currentNode;
		currentNode = currentNode->next;
		delete throwaway;
		throwaway = NULL;
	}

	if(head != NULL)
	{
		head->next = NULL;
		this->head = NULL;
	}

	if(tail != NULL)
	{
		tail = NULL;
	}

}

template<class T>
LinkedList<T>::~LinkedList()
{
	node* currentNode = head;
	while(currentNode != NULL)
	{
		head = currentNode->next;
		currentNode = NULL;
		currentNode = head;
	}

	head = NULL;
}

#endif /* SRC_LINKEDLIST_H_ */
