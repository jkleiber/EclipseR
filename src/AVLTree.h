/*
 * AVLTree.h
 *
 *  Created on: Nov 20, 2017
 *      Author: justin
 */

#ifndef SRC_AVLTREE_H_
#define SRC_AVLTREE_H_

#include <iostream>

#include "ResizableArray.h"

template<typename T>
class AVLTree;

template<typename T>
std::ostream& operator<<(std::ostream& os, AVLTree<T> &tree);

template<class T>
class AVLTree
{
	struct treeNode
	{
		T data;
		treeNode* left;
		treeNode* right;
		int balance;
		int key;
	};

	//In-order printing
	friend std::ostream& operator<< <T>(std::ostream& os, AVLTree<T> &tree);

	public:

		AVLTree();

		void insert(T& t, int key);

		void remove(int key);

		T& search(int key);

		void printPreOrder();

		void printPostOrder();

		int getSize();

		ResizableArray<T> buildArray();

	private:
		int numElements;

		treeNode* root;

		treeNode* findLocation(int key);

		void rotateTree(treeNode*& currentNode, treeNode*& parentNode);


		void recursiveInsert(treeNode* insertNode, treeNode*& currentNode);

		void recursiveRemove(int key, treeNode*& currentNode, treeNode*& parentNode, int leftOrRight);


		treeNode* findReplaceNode(treeNode* currentNode, int mode = 0);

		void updateBalanceFactors(treeNode*& currentNode, treeNode*& parentNode);

		int getHeight(treeNode* currentNode, int height=1);


		void buildInOrderArray(ResizableArray<T>& array, treeNode*& currentNode);


		void streamInOrder(std::ostream& os, treeNode* currentNode);

		void streamPreOrder(treeNode* currentNode);

		void streamPostOrder(treeNode* currentNode);

		void printKeysTreeStyle(treeNode* currentNode, int depth=0);


		void rotateRight(treeNode*& currentNode);

		void rotateLeft(treeNode*& currentNode);
};


//------------------
// PUBLIC FUNCTIONS
//------------------
template<class T>
AVLTree<T>::AVLTree()
{
	this->numElements = 0;
	this->root = new treeNode;
	this->root = NULL;
}

template<class T>
void AVLTree<T>::insert(T& t, int key)
{
	treeNode* leaf = new treeNode;
	leaf->data = t;
	leaf->left = NULL;
	leaf->right = NULL;
	leaf->balance = 0;
	leaf->key = key;

	recursiveInsert(leaf, root);

	updateBalanceFactors(root, root);

	this->numElements++;
}

template<class T>
void AVLTree<T>::remove(int key)
{
	try
	{
		recursiveRemove(key, root, root, 0);

		if(root != NULL)
		{
			updateBalanceFactors(root, root);
		}

		this->numElements--;
	}
	catch(const char* message)
	{
		std::cout << message;
		std::cout << std::endl;
	}
}

template<class T>
T& AVLTree<T>::search(int key)
{
	treeNode* resultNode = findLocation(key);

	if(resultNode != NULL)
	{
		if(resultNode->key == key)
		{
			return resultNode->data;
		}
	}
	throw("Value not found in the AVL Tree!");
}


template<class T>
void AVLTree<T>::printPreOrder()
{
	streamPreOrder(root);
}

template<class T>
void AVLTree<T>::printPostOrder()
{
	streamPostOrder(root);
}

template<class T>
int AVLTree<T>::getSize()
{
	return this->numElements;
}

template<class T>
ResizableArray<T> AVLTree<T>::buildArray()
{
	ResizableArray<T> array;

	//Recursively build array
	buildInOrderArray(array, root);

	return array;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, AVLTree<T> &tree)
{
	tree.streamInOrder(os, tree.root);
	return os;
}

//-------------------
// PRIVATE FUNCTIONS
//-------------------

template<class T>
typename AVLTree<T>::treeNode* AVLTree<T>::findLocation(int key)
{
	treeNode* currentNode = new treeNode;
	treeNode* lastNode = new treeNode;
	currentNode = root;
	lastNode = root;

	while(currentNode != NULL)
	{
		if(currentNode->key == key)
		{
			return currentNode;
		}
		else if(currentNode->key < key)
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

template<class T>
void AVLTree<T>::rotateTree(treeNode*& currentNode, treeNode*& parentNode)
{
	//If we need to rotate, do that.
	int stepTwo = 0;

	/**
	 * Rotation cases found in zyBooks chapter 20, section 10, Figure 20.10.1
	 * I used this figure to create the logic for rotating the tree
	 */

	//If the left side is unbalanced
	if(currentNode->balance > 1)
	{
		if(currentNode->left != NULL)
		{
			stepTwo = currentNode->left->balance;
		}
		else
		{
			stepTwo = 0;
		}

		//Left-Left violation (Right Rotation)
		if(stepTwo > 0)
		{
			rotateRight(currentNode);
		}
		//Left-Right violation
		else
		{
			//Special case left rotation
			treeNode* t2 = currentNode->left->right->left;
			treeNode* B = currentNode->left;
			currentNode->left->right->left = B;
			currentNode->left = currentNode->left->right;
			B->right = t2;

			//Right Rotation
			rotateRight(currentNode);
		}
	}
	//If the right side is unbalanced
	else if(currentNode->balance < -1)
	{
		if(currentNode->right != NULL)
		{
			stepTwo = currentNode->right->balance;
		}
		else
		{
			stepTwo = 0;
		}

		//Right-Right violation (Left Rotation)
		if(stepTwo < 0)
		{
			rotateLeft(currentNode);
		}
		//Right-Left violation
		else
		{
			//Special Case Right rotation
			treeNode* t3 = currentNode->right->left->right;
			treeNode* B = currentNode->right;
			currentNode->right->left->right = B;
			currentNode->right = currentNode->right->left;
			B->left = t3;

			//Left Rotation
			rotateLeft(currentNode);
		}
	}
}

template<class T>
void AVLTree<T>::recursiveInsert(treeNode* insertNode, treeNode*& currentNode)
{
	//If this is the first insertion into the tree, setup the tree!
	if(this->root == NULL)
	{
		this->root = insertNode;
	}
	else if(currentNode->left == NULL && (insertNode->data < currentNode->data))
	{
		currentNode->left = insertNode;
	}
	else if(currentNode->right == NULL && (insertNode->data > currentNode->data))
	{
		currentNode->right = insertNode;
	}
	//Insert to the left if appropriate
	else if(insertNode->data < currentNode->data)
	{
		recursiveInsert(insertNode, currentNode->left);
	}
	//Insert to the right if appropriate
	else if(insertNode->data > currentNode->data)
	{
		recursiveInsert(insertNode, currentNode->right);
	}
	//If the nodes are identical, replace the old one
	else
	{
		currentNode->data = insertNode->data;
	}
}

template<class T>
void AVLTree<T>::recursiveRemove(int key, treeNode*& currentNode, treeNode*& parentNode, int leftOrRight)
{
	if(currentNode != NULL)
	{
		//If the key has been found
		if(key == currentNode->key)
		{
			//Start the removal process...

			//If this node has no children, this is easy
			if(currentNode->left == NULL && currentNode->right == NULL)
			{
				//Not the root node, so set the parent's left or right to NULL
				if(parentNode != root)
				{
					//Figure out which child node to set to NULL
					if(leftOrRight == 0)
					{
						parentNode->left = NULL;
					}
					else
					{
						parentNode->right = NULL;
					}

					//Delete the node to be removed
					delete currentNode;
				}
				else
				{
					//This must be the root node
					root = NULL;
				}
			}
			//If this node has one child, it's still pretty easy
			else if((currentNode->left == NULL) != (currentNode->right == NULL))
			{
				//Find the child node and set it as a placeholder
				treeNode* node = new treeNode;
				if(currentNode->left == NULL)
				{
					node = currentNode->right;
				}
				else
				{
					node = currentNode->left;
				}

				delete currentNode;

				if(parentNode != NULL)
				{
					//Figure out which child node to set to the current child
					if(leftOrRight == 0)
					{
						parentNode->left = node;
					}
					else
					{
						parentNode->right = node;
					}
				}
				else
				{
					//Removing the root node means replacing it with its child
					root = node;
				}
			}
			//The node has two children
			else
			{
				treeNode* replaceNode = new treeNode;

				replaceNode = findReplaceNode(currentNode->left);

				//Perform a replacement
				currentNode->data = replaceNode->data;
				currentNode->key = replaceNode->key;

				//Remove the replaced node
				recursiveRemove(replaceNode->key, currentNode->left, currentNode, 0);
			}
		}
		else if(key < currentNode->key)
		{
			if(currentNode->left != NULL)
			{
				recursiveRemove(key, currentNode->left, currentNode, 0);
			}
			else
			{
				throw("Value not found in the AVL Tree!");
			}
		}
		else
		{
			if(currentNode->right != NULL)
			{
				recursiveRemove(key, currentNode->right, currentNode, 1);
			}
			else
			{
				throw("Value not found in the AVL Tree!");
			}
		}
	}
}

template<class T>
typename AVLTree<T>::treeNode* AVLTree<T>::findReplaceNode(treeNode* currentNode, int mode)
{
	while(currentNode->right != NULL)
	{
		currentNode = currentNode->right;
	}

	return currentNode;
}

template<class T>
void AVLTree<T>::updateBalanceFactors(treeNode*& currentNode, treeNode*& parentNode)
{
	//Keep track of subtree heights
	int left = 0, right = 0;

	//Go to the lowest possible nodes on the left first
	if(currentNode->left != NULL)
	{
		updateBalanceFactors(currentNode->left, currentNode);
		left = getHeight(currentNode->left);
	}

	//Go to the lowest possible nodes on the right
	if(currentNode->right != NULL)
	{
		updateBalanceFactors(currentNode->right, currentNode);
		right = getHeight(currentNode->right);
	}

	//Update the balances
	currentNode->balance = left - right;

	//Rotate if necessary
	if(currentNode->balance < -1 || currentNode->balance > 1)
	{
		rotateTree(currentNode, parentNode);
	}

}

template<class T>
int AVLTree<T>::getHeight(treeNode* currentNode, int height)
{
	if(currentNode->left == NULL && currentNode->right == NULL)
	{
		return height;
	}
	else
	{
		int h1 = 0, h2 = 0;

		if(currentNode->left != NULL)
		{
			h1 = getHeight(currentNode->left, height + 1);
		}

		if(currentNode->right != NULL)
		{
			h2 = getHeight(currentNode->right, height +1);
		}

		int height = h1 > h2 ? h1 : h2;

		return height;
	}
}

template<class T>
void AVLTree<T>::buildInOrderArray(ResizableArray<T>& array, treeNode*& currentNode)
{
	if(currentNode != NULL)
	{
		if(currentNode->left != NULL)
		{
			buildInOrderArray(array, currentNode->left);
		}

		array.add(currentNode->data);

		if(currentNode->right != NULL)
		{
			buildInOrderArray(array, currentNode->right);
		}
	}
}


template<class T>
void AVLTree<T>::streamInOrder(std::ostream& os, treeNode* currentNode)
{
	if(currentNode != NULL)
	{
		if(currentNode->left != NULL)
		{
			streamInOrder(os, currentNode->left);
		}

		os << currentNode->data;
		os << std::endl;

		if(currentNode->right != NULL)
		{
			streamInOrder(os, currentNode->right);
		}
	}
}

template<class T>
void AVLTree<T>::streamPreOrder(treeNode* currentNode)
{
	if(currentNode != NULL)
	{
		std::cout << currentNode->data;
		std::cout << std::endl;

		if(currentNode->left != NULL)
		{
			streamPreOrder(currentNode->left);
		}

		if(currentNode->right != NULL)
		{
			streamPreOrder(currentNode->right);
		}
	}
}

template<class T>
void AVLTree<T>::streamPostOrder(treeNode* currentNode)
{
	if(currentNode != NULL)
	{
		if(currentNode->left != NULL)
		{
			streamPostOrder(currentNode->left);
		}

		if(currentNode->right != NULL)
		{
			streamPostOrder(currentNode->right);
		}

		std::cout << currentNode->data;
		std::cout << std::endl;
	}
}

template<class T>
void AVLTree<T>::printKeysTreeStyle(treeNode* currentNode, int depth)
{
	if(currentNode != NULL)
	{
		if(currentNode == root)
		{
			std::cout << "ROOT: ";
		}

		std::cout << currentNode->key << " " << depth << " B: " << currentNode->balance;
		std::cout << std::endl;

		depth++;

		if(currentNode->left != NULL)
		{
			std::cout << "L: ";
			printKeysTreeStyle(currentNode->left, depth);
		}

		if(currentNode->right != NULL)
		{
			std::cout << "R: ";
			printKeysTreeStyle(currentNode->right, depth);
		}
	}
}

template<class T>
void AVLTree<T>::rotateRight(treeNode*& currentNode)
{
	//Update balances
	currentNode->balance = 0;

	treeNode* t2 = currentNode->left->right;
	treeNode* A = currentNode;

	currentNode->left->right = currentNode;

	treeNode* p = new treeNode;
	p = currentNode->left;
	p->balance = 0;
	p->right = A;

	A->left = t2;

	//Update parent node and root if necessary
	if(currentNode == this->root)
	{
		this->root = p;
	}
	else
	{
		currentNode = p;
	}
}

template<class T>
void AVLTree<T>::rotateLeft(treeNode*& currentNode)
{
	//Update balances
	currentNode->balance = 0;

	treeNode* t2 = currentNode->right->left;
	treeNode* A = currentNode;

	currentNode->right->left = currentNode;

	treeNode* p = new treeNode;
	p = currentNode->right;
	p->balance = 0;
	p->left = A;

	A->right = t2;

	//Update parent node and root if necessary
	if(currentNode == this->root)
	{
		this->root = p;
	}
	else
	{
		currentNode = p;
	}
}
#endif /* SRC_AVLTREE_H_ */
