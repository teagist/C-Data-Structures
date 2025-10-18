//****************************************************************************
//	Implementation File for Templated Treap.
//	Programmed by: Houston Brown.
//	Last Compiled Date: 10/12/2025
//****************************************************************************

#include "Treap.h"

//****************************************************************************
//	NAME: InsertHelper.
//
//  DESCRIPTION: Helper method to perform insertion.  If the heap order has 
//               been violated, then a rotation will be performed.
//
//	PARAMETERS: key: the element to be inserted.
//		        subtree: pointer to the root of subtree.
//****************************************************************************
template <class T>
void Treap<T>::InsertHelper(T key, TreapNode<T>*& subtree)
{
	try
	{
		if (!subtree)
		{
			subtree = new TreapNode<T>(key);
			return;
		}

		if (key < subtree->data)
		{
			InsertHelper(key, subtree->left);

			if (subtree->left != nullptr && subtree->left->priority >
				subtree->priority)
			{
				RotateRight(subtree);
			}
		}
		else
		{
			InsertHelper(key, subtree->right);

			if (subtree->right != nullptr && subtree->right->priority >
				subtree->priority)
			{
				RotateLeft(subtree);
			}
		}
	}
	catch (...)
	{
		std::cerr << "Unexpected exception caught while attempting to insert "
			      << key << " into the treap." << std::endl;
	}
}

//****************************************************************************
//  NAME: RotateLeft.
// 
//	DESCRIPTION: Utility function to perform a left rotation of the tree.
//
//	PARAMETERS: subtree: pointer to the root of subtree.
//****************************************************************************
template <class T>
void Treap<T>::RotateLeft(TreapNode<T>*& subtree)
{
	try
	{
		TreapNode<T>* rightPtr = subtree->right;
		TreapNode<T>* temp = subtree->right->left;

		rightPtr->left = subtree;
		subtree->right = temp;
		subtree = rightPtr;
	}
	catch (...)
	{
		std::cerr << "Unexpected exception caught while attempting to " 
			      << "perform a left rotation." << std::endl;
	}
}

//****************************************************************************
//  NAME: RotateRight.
// 
// 	DESCRIPTION: Utility function to perform a right rotation of the tree.
//
//	PARAMETERS: subtree: pointer to the root of subtree.
//****************************************************************************
template <class T>
void Treap<T>::RotateRight(TreapNode<T>*& subtree)
{
	try
	{
		TreapNode<T>* leftPtr = subtree->left;
		TreapNode<T>* temp = subtree->left->right;

		leftPtr->right = subtree;
		subtree->left = temp;
		subtree = leftPtr;
	}
	catch (...)
	{
		std::cerr << "Unexpected exception caught while attempting to "
			      << "perform a right rotation." << std::endl;
	}
}

//****************************************************************************
//  NAME: SearchHelper.
// 
//	DESCRIPTION: Helper method to perform a search of the Treap.  The 
//               function will return true if the item is found, and false 
//               otherwise.
//
//	PARAMETERS: key: the element to be searched for.
//		        subtree: pointer to the root of subtree.
//****************************************************************************
template <class T>
bool Treap<T>::SearchHelper(T key, TreapNode<T>* subtree) const
{
	try
	{
		if (subtree == nullptr)
		{
			return false;
		}
		if (subtree->data == key)
		{
			return true;
		}
		if (key < subtree->data)
		{
			return SearchHelper(key, subtree->left);
		}
		return SearchHelper(key, subtree->right);
	}
	catch (...)
	{
		std::cerr << "Unexpected exception caught while attempting to "
			      << "search the treap for " << key << "." << std::endl;
		return false;
	}
}

//****************************************************************************
//  NAME: DeleteHelper.
// 
//	DESCRIPTION: Helper method to delete a given key from the Treap.  If 
//               the key is not in the Treap, then this function will return.
//
//	PARAMETERS: key: the element to be deleted.
//		        subtree: pointer to the root of subtree.
//****************************************************************************
template <class T>
void Treap<T>::DeleteHelper(T key, TreapNode<T>*& subtree)
{
	try
	{
		if (subtree == nullptr)
		{
			return;
		}
		else
		{
			if (key < subtree->data)
			{
				DeleteHelper(key, subtree->left);
			}
			else if (key > subtree->data)
			{
				DeleteHelper(key, subtree->right);
			}
			else
			{
				if (subtree->left == nullptr && subtree->right == nullptr)
				{
					delete subtree;
					subtree = nullptr;
				}
				else if (subtree->left && subtree->right)
				{
					if (subtree->left->priority < subtree->right->priority)
					{
						RotateLeft(subtree);
						DeleteHelper(key, subtree->left);
					}
					else
					{
						RotateRight(subtree);
						DeleteHelper(key, subtree->right);
					}
				}
				else
				{
					TreapNode<T>* child;
					if (subtree->left)
					{
						child = subtree->left;
					}
					else
					{
						child = subtree->right;
					}

					TreapNode<T>* curr = subtree;
					subtree = child;
					delete curr;
				}
			}
		}
	}
	catch (...)
	{
		std::cerr << "Unexpected exception caught while attempting to "
			      << "remove " << key << " from the treap." << std::endl;
	}
}

//****************************************************************************
//  NAME: PruneHelper.
// 
//	DESCRIPTION: Helper method to traverse the tree and check each node to 
//               see if it is a leaf.  If it is, the node will be deleted. 
//               Otherwise, the traversal will continue until the entire tree
//               has been pruned of leaves.
//
//	PARAMETERS: subtree: pointer to the root of subtree.
//****************************************************************************
template <class T>
void Treap<T>::PruneHelper(TreapNode<T>*& subtree)
{
	try
	{
		if (subtree == nullptr)
		{
			return;
		}
		else
		{
			PruneHelper(subtree->left);
			PruneHelper(subtree->right);

			if (isLeaf(subtree) && subtree != root)
			{
				delete subtree;
				subtree = nullptr;
			}
		}
	}
	catch (...)
	{
		std::cerr << "Unexpected exception caught while attempting to "
			      << "prune the treap." << std::endl;
	}
}

//****************************************************************************
//  NAME: Clear.
// 
//	DESCRIPTION: Treap method to clear and deallocate all dynamic memory 
//               allocated to the nodes of the treap.  
//
//	PARAMETERS: N/A.
//****************************************************************************
template <class T>
void Treap<T>::Clear()
{
	ClearHelper(root);
	root = nullptr;
}

//****************************************************************************
//  NAME: ClearHelper.
// 
//	DESCRIPTION: Helper method to deallocate all nodes of the tree.
//
//	PARAMETERS: subtree: pointer to the root of subtree.
//****************************************************************************
template <class T>
void Treap<T>::ClearHelper(TreapNode<T>*& subtree)
{
	try
	{
		if (subtree != nullptr)
		{
			ClearHelper(subtree->left);
			ClearHelper(subtree->right);
			delete subtree;
		}
		subtree = nullptr;
	}
	catch (...)
	{
		std::cerr << "Unexpected exception caught while attempting to "
			      << "clear the treap." << std::endl;
	}
}

//****************************************************************************
//  NAME: TreePrint.
// 
//	DESCRIPTION: Treap method to print the contents of the tree in level 
//               order.   
//
//	PARAMETERS: N/A.
//****************************************************************************
template <class T>
void Treap<T>::TreePrint() const
{
	try
	{
		if (!root)
		{
			cerr << endl << "The treap is empty." << endl;
			return;
		}
		else
		{
			for (int i = 0; i <= GetHeight(root); i++)
			{
				PrintLevel(i);
				cout << endl << endl;
			}
		}
	}
	catch (...)
	{
		std::cerr << "Unexpected exception caught while attempting to "
			      << "print the contents of the treap." << std::endl;
	}
}

//****************************************************************************
//  NAME: PrintLevel.
// 
//	DESCRIPTION: Treap method to calculate the distance from the beginning 
//               of a new line.    
//
//	PARAMETERS: level: current level that we are printing from.  
//****************************************************************************
template <class T>
void Treap<T>::PrintLevel(int level) const
{
	TreapNode<T>* temp = root;

	int value = pow(2, GetHeight(root) - level + 2);
	cout << setw(value) << "";
	DispLevel(temp, level, value);
}

//****************************************************************************
//  NAME: DispLevel.
// 
//	DESCRIPTION: Treap method to print the data and priority of the nodes and
//	             calculates the distance between to points.     
//
//	PARAMETERS: subtree: pointer the root of the subtree.
//		        level: current level that we are printing from.
//		        dist: the calculated distance between two points.
//****************************************************************************
template <class T>
void Treap<T>::DispLevel(TreapNode<T>* subtree, int level, int dist) const
{
	int disp = 2 * dist;
	if (level == 0)
	{
		if (subtree == nullptr)
		{
			cout << " x ";
			cout << setw(disp - 3) << "";
			return;
		}
		else
		{
			int result = 0;
			if (subtree->priority <= 1)
			{
				result = 1;
			}
			else
			{
				result = (log10(subtree->priority) + 1);
			}

			cout << " " << subtree->data << " (" << subtree->priority << ") ";
			cout << setw(disp - result - 5) << "";
		}
	}
	else
	{
		if (subtree == nullptr && level >= 1)
		{
			DispLevel(nullptr, level - 1, dist);
			DispLevel(nullptr, level - 1, dist);
		}
		else
		{
			DispLevel(subtree->left, level - 1, dist);
			DispLevel(subtree->right, level - 1, dist);
		}
	}
}

//****************************************************************************
//  NAME: GetHeight.
// 
//	DESCRIPTION: Utility function to return the height of the Treap.
//
//	PARAMETERS: subtree: pointer to the root of subtree.
//****************************************************************************
template <class T>
int Treap<T>::GetHeight(TreapNode<T>* subtree) const
{
	if (subtree == nullptr)
	{
		return 0;
	}
	else
	{
		int leftHeight = GetHeight(subtree->left);
		int rightHeight = GetHeight(subtree->right);
		if (leftHeight >= rightHeight)
		{
			return leftHeight + 1;
		}
		else
		{
			return rightHeight + 1;
		}
	}
}

//****************************************************************************
//  NAME: InOrderHelper.
// 
//	DESCRIPTION: Helper method to print the contents of the Treap in order.
//
//	PARAMETERS: subtree: pointer to the root of subtree.
//****************************************************************************
template <class T>
void Treap<T>::InOrderHelper(TreapNode<T>* subtree) const
{
	try
	{
		if (subtree)
		{
			InOrderHelper(subtree->left);
			cout << subtree->data << " (" << subtree->priority << ")" << endl;
			InOrderHelper(subtree->right);
		}
	}
	catch (...)
	{
		std::cerr << "Unexpected exception caught while attempting to "
			      << "print the contents of the treap in order." << std::endl;
	}
}

//****************************************************************************
//  NAME: PreOrderHelper.
// 
//	DESCRIPTION: Helper method to print the contents of the Treap in pre order
//	             processing.
//
//	PARAMETERS: subtree: pointer to the root of subtree.
//****************************************************************************
template <class T>
void Treap<T>::PreOrderHelper(TreapNode<T>* subtree) const
{
	try
	{
		if (subtree)
		{
			cout << subtree->data << " (" << subtree->priority << ")" << endl;
			PreOrderHelper(subtree->left);
			PreOrderHelper(subtree->right);
		}
	}
	catch (...)
	{
		std::cerr << "Unexpected exception caught while attempting to "
			      << "print the contents of the treap in pre-order." << std::endl;
	}
}

//****************************************************************************
//  NAME: PostOrderHelper.
// 
//	DESCRIPTION: Helper method to print the contents of the Treap in post order
//	             processing.
//
//	PARAMETERS: subtree: pointer to the root of subtree.
//****************************************************************************
template <class T>
void Treap<T>::PostOrderHelper(TreapNode<T>* subtree) const
{
	try
	{
		if (subtree)
		{
			PostOrderHelper(subtree->left);
			PostOrderHelper(subtree->right);
			cout << subtree->data << " (" << subtree->priority << ")" << endl;
		}
	}
	catch (...)
	{
		std::cerr << "Unexpected exception caught while attempting to "
			      << "print the contents of the treap in post-order." << std::endl;
	}
}

//****************************************************************************
//		Copy Constructor.
//****************************************************************************
template <class T>
Treap<T>::Treap(const Treap& myTreap)
{
	if (!myTreap.root)
	{
		root = nullptr;
		return;
	}
	CopyHelper(root, myTreap.root);
}

//****************************************************************************
//		Helper method for Copy Constructor.
//****************************************************************************
template<class T>
void Treap<T>::CopyHelper(TreapNode<T>*& aRoot, TreapNode<T>* myRoot)
{
	if (!myRoot)
	{
		aRoot = nullptr;
	}
	else
	{
		aRoot = new TreapNode<T>(myRoot->data);
		CopyHelper(aRoot->left, myRoot->left);
		CopyHelper(aRoot->right, myRoot->right);
	}
}

//****************************************************************************
//		Destructor.
//****************************************************************************
template<class T>
Treap<T>::~Treap()
{
	DestroyHelper(root);
	root = nullptr;
}

//****************************************************************************
//		Helper method to for Destructor.
//****************************************************************************
template <class T>
void Treap<T>::DestroyHelper(TreapNode<T>*& Tree)
{
	if (Tree != nullptr)
	{
		DestroyHelper(Tree->left);
		DestroyHelper(Tree->right);
		delete Tree;
	}
	Tree = nullptr;
}

//****************************************************************************
//		Assignment Operator.
//****************************************************************************
template <class T>
Treap<T>& Treap<T>::operator=(const Treap<T>& rightTree)
{
	if (this != &rightTree)
	{
		if (root != nullptr)
		{
			DestroyHelper(root);
		}
		if (rightTree.root == nullptr)
		{
			root = nullptr;
		}
		else
		{
			CopyHelper(root, rightTree.root);
		}
	}
	return *this;
}

template class Treap<int>;
template class Treap<string>;