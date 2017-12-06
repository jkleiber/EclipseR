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
		int key;
	};

	friend std::ostream& operator<<(std::ostream& os, AVLTree<T> &tree);

	public:

		AVLTree();

		void insert(T& t, int key);

		void remove(int key);

		T& search(int key);

		void printInOrder();

		void printPreOrder();

		void printPostOrder();

	private:
		int numElements;

		treeNode* root;

		treeNode*& findLocation(int key);

		void rotateTree(treeNode*& currentNode, treeNode*& parentNode);

		int recursiveInsert(treeNode*& insertNode, treeNode*& currentNode, treeNode*& parentNode);

		int recursiveRemove(int key, treeNode*& currentNode, treeNode*& parentNode, int leftOrRight);

		treeNode*& findReplaceNode(treeNode*& currentNode);

		int updateSubtreeBalance(treeNode*& currentNode, treeNode*& parentNode, treeNode*& replaceNode);
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

	this->root->left = NULL;
	this->root->right = NULL;
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

	recursiveInsert(leaf, root, NULL);
}

template<class T>
void AVLTree<T>::remove(int key)
{
	recursiveRemove(key, root, NULL);
}

template<class T>
T& AVLTree<T>::search(int key)
{
	treeNode* resultNode = findLocation(key);

	if(resultNode->key == key)
	{
		return resultNode->data;
	}

	throw("Value not found in the AVL Tree!");
}

template<class T>
friend std::ostream& operator<<(std::ostream& os, AVLTree<T> &tree)
{
	return os;
}

//-------------------
// PRIVATE FUNCTIONS
//-------------------

template<class T>
AVLTree::treeNode*& AVLTree<T>::findLocation(int key)
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
	if(currentNode->balance < -1)
	{
		stepTwo = currentNode->left->balance;

		//Left-Left violation (Right Rotation)
		if(stepTwo < 0)
		{
			treeNode* temp = currentNode->left->right;
			currentNode->left->right = currentNode;

			//Update parent node and root if necessary
			if(currentNode == this->root)
			{
				this->root = currentNode->left;
			}
			parentNode = currentNode->left;

			//finish Rotation
			currentNode->left = temp;

			//Update balance factors of rotated nodes
			currentNode->balance = 0;
			parentNode->balance = 0;
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
			treeNode* temp = currentNode->left->right;
			currentNode->left->right = currentNode;

			//Update parent node and root if necessary
			if(currentNode == this->root)
			{
				this->root = currentNode->left;
			}
			parentNode = currentNode->left;

			//Finish Rotation
			currentNode->left = temp;

			//Update balances
			currentNode->balance = 0;
			B->balance = 0;
			parentNode->balance = 0;
		}
	}
	else if(currentNode->balance > 1)
	{
		stepTwo = currentNode->right->balance;

		//Right-Right violation (Left Rotation)
		if(stepTwo > 0)
		{
			treeNode* temp = currentNode->right->left;
			currentNode->right->left = currentNode;

			//Update parent node and root if necessary
			if(currentNode == this->root)
			{
				this->root = currentNode->right;
			}
			parentNode = currentNode->right;

			//Finish Rotation
			currentNode->right = temp;

			//Update balances
			currentNode->balance = 0;
			parentNode->balance = 0;
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
			treeNode* temp = currentNode->right->left;
			currentNode->right->left = currentNode;

			//Update parent node and root if necessary
			if(currentNode == this->root)
			{
				this->root = currentNode->right;
			}
			parentNode = currentNode->right;

			//Finish rotation
			currentNode->right = temp;

			//Update balances
			B->balance = 0;
			parentNode->balance = 0;
			currentNode->balance = 0;
		}
	}
}

template<class T>
int AVLTree<T>::recursiveInsert(treeNode*& insertNode, treeNode*& currentNode, treeNode*& parentNode)
{
	//Keep track of how much the balance changes
	int balanceDelta = 0;

	if(currentNode == NULL)
	{
		if(insertNode->data < parentNode->data)
		{
			parentNode->left = insertNode;

			//If there has been height added, update the balances
			if(parentNode->right == NULL)
			{
				return 1; //New level created, subtract 1
			}
			else
			{
				return 0;
			}
		}
		else
		{
			parentNode->right = insertNode;

			//If there has been height added, update the balances
			if(parentNode->left == NULL)
			{
				return 1; //New level created, add one
			}
			else
			{
				return 0;
			}
		}
	}
	//Insert to the left if appropriate
	else if(insertNode->data < currentNode->data)
	{
		balanceDelta = recursiveInsert(insertNode, currentNode->left, currentNode);
		currentNode->balance += balanceDelta;
	}
	//Insert to the left if appropriate
	else if(insertNode->data > currentNode->data)
	{
		balanceDelta = recursiveInsert(insertNode, currentNode->right, currentNode);
		currentNode->balance -= balanceDelta;
	}
	//If the nodes are identical, replace the old one
	else
	{
		currentNode->data = insertNode->data;
	}

	//If the tree is out of balance at this node, rotate it
	if(currentNode->balance > 1 || currentNode->balance < -1)
	{
		rotateTree(currentNode, parentNode);
		balanceDelta = 0;
	}

	/**
	 * The balance change should be propagated up
	 * the tree until rotation is required
	 */
	return balanceDelta;
}

template<class T>
int AVLTree<T>::recursiveRemove(int key, treeNode*& currentNode, treeNode*& parentNode, int leftOrRight)
{
	//Keep track of the changes in balance
	int balanceDelta = 0;

	//If the key has been found
	if(key == currentNode->key)
	{
		//Start the removal process...

		//If this node has no children, this is easy
		if(currentNode->left == NULL && currentNode->right == NULL)
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

			//Return the change in height (absolute value)
			if(parentNode->left == NULL && parentNode->right == NULL)
			{
				return 1;
			}
			else
			{
				return 0;
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

			//Figure out which child node to set to the current child
			if(leftOrRight == 0)
			{
				parentNode->left = node;
			}
			else
			{
				parentNode->right = node;
			}

			//Return the change in height (absolute value)
			return 1; //Note: since this has one child, the height of this sub tree is always subtracted by 1.
		}
		//The node has two children, and now it is difficult
		else
		{
			treeNode* replaceNode = new treeNode;

			replaceNode = findReplaceNode(currentNode->left);

			//Perform a replacement
			currentNode->data = replaceNode->data;
			currentNode->key = replaceNode->key;

			balanceDelta = updateSubtreeBalance(currentNode->left, currentNode, replaceNode);

			currentNode->balance += balanceDelta;
		}
	}
	else if(key < currentNode->key)
	{
		if(currentNode->left != NULL)
		{
			balanceDelta = recursiveRemove(key, currentNode->left);

			currentNode->balance -= balanceDelta;
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
			balanceDelta = recursiveRemove(key, currentNode->right);

			currentNode->balance += balanceDelta;
		}
		else
		{
			throw("Value not found in the AVL Tree!");
		}
	}

	//If the tree is out of balance at this node, rotate it
	if(currentNode->balance > 1 || currentNode->balance < -1)
	{
		rotateTree(currentNode, parentNode);
		balanceDelta = 0;
	}

	return balanceDelta;
}

template<class T>
AVLTree::treeNode*& AVLTree<T>::findReplaceNode(treeNode*& currentNode)
{
	while(currentNode->right != NULL)
	{
		currentNode = currentNode->right;
	}

	return currentNode;
}

template<class T>
int AVLTree<T>::updateSubtreeBalance(treeNode*& currentNode, treeNode*& parentNode, treeNode*& replaceNode)
{
	if(currentNode->right == NULL)
	{
		parentNode->left = currentNode->left;
		delete currentNode;

		//The height has to have changed by 1 in this case
		return 1;
	}
	else if(currentNode->right == replaceNode)
	{
		//No matter what, we need to update this node's balance factor
		currentNode->balance++;

		//If the replacement node has no children, we can simply delete it
		if(replaceNode->left == NULL)
		{
			currentNode->right = NULL;
			delete replaceNode;

			//Check if the height above the current node changed
			if(currentNode->left == NULL)
			{
				//In this configuration, the current node is now a leaf, -1 height
				return 1;
			}
			else
			{
				//Otherwise, the current node is still an inner node
				return 0;
			}
		}
		//Otherwise the left node below the replacement needs to be shifted up
		else
		{
			currentNode->right = replaceNode->left;
			delete replaceNode;

			//There is only one AVL configuration where this is possible,
			//and the height always will be reduced by 1 on removal
			return 1;
		}
	}
	else
	{
		int balanceDelta = updateSubtreeBalance(currentNode->right, currentNode, replaceNode);

		currentNode->balance += balanceDelta;

		//If we rotate, then the height decreases 1. If we do not rotate, it might. See discrete notebook

		//If the tree is out of balance at this node, rotate it
		if(currentNode->balance > 1 || currentNode->balance < -1)
		{
			rotateTree(currentNode, parentNode);
			balanceDelta = 0;
		}

		return balanceDelta;
	}
}

#endif /* SRC_AVLTREE_H_ */
