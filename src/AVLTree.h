/*
 * AVLTree.h
 *
 *  Created on: Nov 20, 2017
 *      Author: justin
 */

#ifndef SRC_AVLTREE_H_
#define SRC_AVLTREE_H_

#include <iostream>

template<class T>
class AVLTree
{
	struct treeNode
	{
		T data;
		treeNode* left;
		treeNode* right;
		int balance;
	};

	friend std::ostream& operator<<(std::ostream& os, AVLTree<T> &tree)
	{
		return os;
	}

	public:
		AVLTree()
		{
			this->numElements = 0;
			this->root = new treeNode;
			this->root = NULL;
		}

		void insert(T& t, int key)
		{
			treeNode* leaf = new treeNode;
			leaf->data = t;
			leaf->left = NULL;
			leaf->right = NULL;
			leaf->balance = 0;

			recursiveInsert(leaf, root, NULL);
		}

		T& search(int key)
		{
			treeNode* resultNode = findLocation(key);

			if(resultNode->data == key)
			{
				return resultNode->data;
			}

			throw("Value not found in the AVL Tree!");
		}

	private:
		int numElements;

		treeNode* root;

		treeNode*& findLocation(int key)
		{
			treeNode* currentNode = new treeNode;
			treeNode* lastNode = new treeNode;
			currentNode = root;
			lastNode = root;

			while(currentNode != NULL)
			{
				if(currentNode->data == key)
				{
					return currentNode;
				}
				else if(currentNode->data < key)
				{
					lastNode = currentNode;
					currentNode = currentNode->left;
				}
				else
				{
					lastNode = currentNode;
					currentNode = currentNode->right;
				}
			}

			return lastNode;
		}

		void balanceTree(int key)
		{
			treeNode* currentNode = new treeNode;
			currentNode = root;

			treeNode* rotationPoint = new treeNode;
			rotationPoint = NULL;

			treeNode* parentRotateNode = new treeNode;

			while(currentNode != NULL)
			{
				parentRotateNode = currentNode;
				if(currentNode->data == key)
				{
					//We found the insertion point, so everything is up to date.
					break;
				}
				//If the node was added to the left, subtract from balance factor
				else if(currentNode->data < key)
				{
					currentNode->balance--;
					currentNode = currentNode->left;
				}
				//Otherwise, the node was put on the right side, so add to the balance factor
				else
				{
					currentNode->balance++;
					currentNode = currentNode->right;
				}

				if(currentNode->balance >= 2 || currentNode->balance <= -2)
				{
					rotationPoint = currentNode;
				}
			}

			if(rotationPoint != NULL)
			{
				rotateAt(parentRotateNode, rotationPoint);
			}
		}

		void recursiveInsert(treeNode*& insertNode, treeNode*& currentNode, treeNode*& parentNode)
		{
			if(currentNode == NULL)
			{
				if(insertNode->data < parentNode->data)
				{
					parentNode->left = insertNode;
				}
				else
				{
					parentNode->right = insertNode;
				}
			}
			else if(insertNode->data < currentNode->data)
			{
				currentNode->balance--;
				recursiveInsert(insertNode, currentNode->left, currentNode);
			}
			else if(insertNode->data > currentNode->data)
			{
				currentNode->balance++;
				recursiveInsert(insertNode, currentNode->right, currentNode);
			}
			else
			{
				currentNode->data = insertNode->data;
			}

			//If we need to rotate, do that.
			int stepTwo = 0;

			if(currentNode->balance < -1)
			{
				stepTwo = currentNode->left->balance;

				//Left-Left violation (Right Rotation)
				if(stepTwo < 0)
				{


				}
				//Left-Right violation
				else
				{

				}
			}
			else if(currentNode->balance > 1)
			{
				stepTwo = currentNode->right->balance;

				//Right-Right violation (Left Rotation)
				if(stepTwo > 0)
				{

				}
				//Right-Left violation
				else
				{

				}
			}
		}
};



#endif /* SRC_AVLTREE_H_ */
