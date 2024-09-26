//***************************************************************************
//	Implementation File for Templated AVL Tree
//	Programmed by: Houston Brown
//	Last Compiled Date: 6/25/2023
//***************************************************************************

#include "AvlTree.h"



//****************************************************************************
//		Method to insert key into the AVL Tree.  If the key is
//	already in the tree, a message will be displayed informing the user.
//	Otherwise, the method will try to allocate memory for a new node.  If
//	it is successful the insertion will proceed.  Otherwise the exception
//	will be caught and an appropriate message displayed.  The tree will also
//	be balanced after insertion.
//
//	Parameters:
//		key: the key to be inserted.
//		subtree: pointer to the root of subtree.
//****************************************************************************

template <class T>
void AvlTree<T>::InsertHelper(const T key, AvlNode<T>*& subtree)
{
	if (subtree == NULL)
	{
		try
		{
			subtree = new AvlNode<T>(key);
			cursor = subtree;
		}
		catch (bad_alloc & ex)
		{
			cerr << "Failed to insert " << key << " into the tree due to";
    		cerr << " bad memory allocation exception." << endl;
		}
		catch (...)
		{
			cerr << "Unregisterd exception." << endl;
		}
	}
	else if (key < subtree->data)
	{
		InsertHelper(key, subtree->left);
	}
	else if (key > subtree->data)
	{
		InsertHelper(key, subtree->right);
	}
	else
	{
		cerr << "No duplicates allowed, please try again." << endl;
	}
     
	BalanceTree(subtree);   
}



//****************************************************************************
//		Method to balance the tree after an insertion or deletion.  If the 
//	subtree passed is NULL, then this function will return.  Otherwise, if 
//	the difference in subtree height is greater than 1, then rotations will
//	be performed to maintain the balance of the tree.  
//
//	Parameters:
//		pointer to the root of subtree.
//****************************************************************************

template <class T>
void AvlTree<T>::BalanceTree(AvlNode<T>*& subtree)
{
	if (subtree == NULL)
	{
		return;
	}
	
	if (GetHeight(subtree->left) - GetHeight(subtree->right) > 1)
	{
		if (GetHeight(subtree->left->left) >= 
										GetHeight(subtree->left->right))
		{
			RotateLeft(subtree);
		}
		else
		{
			DoubleRotateLeft(subtree);
		}
	}
	else if (GetHeight(subtree->right) - GetHeight(subtree->left) > 1)
	{
		if (GetHeight(subtree->right->right) >= 
										GetHeight(subtree->right->left))
		{
			RotateRight(subtree);
		}
		else
		{
			DoubleRotateRight(subtree);
		}
	}
	
	if (GetHeight(subtree->left) > GetHeight(subtree->right))
	{
		subtree->height = GetHeight(subtree->left) + 1;
	}
	else
	{
		subtree->height = GetHeight(subtree->right) + 1;
	}
}



//****************************************************************************
//		Single Left Rotation Method.
//
//	Parameters:
//		pointer to the root of subtree.
//****************************************************************************

template <class T>
void AvlTree<T>::RotateLeft(AvlNode<T>*& subtree)
{
	AvlNode<T>* temp = subtree->left;
	subtree->left = temp->right;
	temp->right = subtree;
	
	subtree->height = max(GetHeight(subtree->left), 
											GetHeight(subtree->right)) + 1;
	temp->height = max(GetHeight(temp->left), subtree->height) + 1;
	subtree = temp;
}



//****************************************************************************
//		Double Left Rotation Method.
//
//	Parameters:
//		pointer to the root of subtree.
//****************************************************************************

template <class T>
void AvlTree<T>::DoubleRotateLeft(AvlNode<T>*& subtree)
{
	RotateRight(subtree->left);
	RotateLeft(subtree);
}



//****************************************************************************
//		Single Right Rotation Method.
//
//	Parameters:
//		pointer to the root of subtree.
//****************************************************************************

template <class T>
void AvlTree<T>::RotateRight(AvlNode<T>*& subtree)
{
	AvlNode<T>* temp = subtree->right;
	subtree->right = temp->left;
	temp->left = subtree;
	
	subtree->height = max(GetHeight(subtree->right), 
											GetHeight(subtree->left)) + 1;
	temp->height = max(GetHeight(temp->right), subtree->height) + 1;
	subtree = temp;	
}



//****************************************************************************
//		Double Right Rotation Method.
//
//	Parameters:
//		pointer to the root of subtree.
//****************************************************************************

template <class T>
void AvlTree<T>::DoubleRotateRight(AvlNode<T>*& subtree)
{
	RotateLeft(subtree->right);
	RotateRight(subtree);
}



//****************************************************************************
//		Method to search for a given key within the AVL Tree.
//	The method will traverse the tree based on the value of the key.  If it
//	is found, the method will return true.  Otherwise, the method will 
//	return false.
//
//	Parameters:
//		key: the key to be searched for.
//****************************************************************************

template <class T>
bool AvlTree<T>::Search(const T key)
{
	AvlNode<T>* temp = root;
	
	while (temp != NULL)
	{
		if (key < temp->data)
		{
			if (temp->left == NULL)
				return false;
			else
				temp = temp->left;
		}
		
		else if (key == temp->data)
		{
			cursor = temp;
			return true;
		}
		
		else
		{
			if (temp->right == NULL)
				return false;
			else
				temp = temp->right;
		}
	}	
}



//****************************************************************************
//		Method to delete a given key from the AVL Tree.  If this
//	method is called on an empty tree, it will return.  If the key cannot be
//	found within the tree, a message will be displayed to the user.  
//	Otherwise, the method will proceed with deletion in the helper function.
//
//	Parameters:
//		key: the key to be deleted.
//****************************************************************************

template <class T>
void AvlTree<T>::Delete(const T key)
{
	if (root == NULL)
	{
		return;
	}
	
	bool isFound = Search(key);
	
	if (isFound == false)
	{
		cerr << "There is not a node with value: " << key << endl;
	}
	else 
	{
		DeleteHelper(key, root);
	}
	
	if (root == NULL)
	{
		cursor = NULL;	
	}
}



//****************************************************************************
//		Helper method to delete a node with a given key.  After the 
//	deletion the tree will be rebalanced.  
//
//	Parameters:
//		key: the key to be deleted.
//		subtree: pointer to the root of subtree.
//****************************************************************************

template <class T>
void AvlTree<T>::DeleteHelper(const T key, AvlNode<T>*& subtree)
{
	if (subtree == NULL)
	{
		return;
	}
	if (key < subtree->data)
	{
		DeleteHelper(key, subtree->left);
	}
	else if (key > subtree->data)
	{
		DeleteHelper(key, subtree->right);
	}
	else if (subtree->left != NULL && subtree->right != NULL)
	{
		subtree->data = GetMin(subtree->right)->data;
		DeleteHelper(subtree->data, subtree->right);
	}
	else
	{
		AvlNode<T>* oldNode = subtree;
		
		if (subtree->left != NULL)
		{
			subtree = subtree->left;
			cursor = subtree;
		} 
		else
		{
			subtree = subtree->right;
			cursor = subtree;	
		}
		
		delete oldNode;
	}
	BalanceTree(subtree);
}



//****************************************************************************
//		Method to return the minimum value in the tree.
//
//	Parameters:
//		node: a root of a subtree
//****************************************************************************

template <class T>
AvlNode<T>* AvlTree<T>::GetMin(AvlNode<T>* subtree) const
{
	while(subtree->left != NULL) 
	{
		subtree = subtree->left;
	}
	return subtree;
}



//****************************************************************************
//		Helper method to traverse the tree and check each node to see if it
//	is a leaf.  If it is, the deletion method will be called on that node.
//	Otherwise, the traversal will continue until the entire tree has been
//	pruned of leaves.  
//
//	Parameters:
//		subtree: pointer to the root of subtree.
//****************************************************************************

template <class T>
void AvlTree<T>::PruneHelper(AvlNode<T>* subtree)
{
    if (subtree != NULL)
    {
        PruneHelper(subtree->left);
        if (isLeaf(subtree) && subtree != root)
        {
        	Delete(subtree->data);
		}
        PruneHelper(subtree->right);
    }	
}



//****************************************************************************
//		Method to print the tree in level order.
//
//	Parameters:
//		N/A.
//****************************************************************************

template <class T>
void AvlTree<T>::PrintTree() const
{
	if (!root)
        return;

    else
    {
        int ctr = 0;
        while (ctr <= GetHeight(root))
        {
            PrintLevel(ctr);
            ctr++;
            cout << endl << endl;
        }
    }
}



//****************************************************************************
//		Recursively calculates the height of the tree.
//
//	Parameters:
//		subtree: pointer to the root of subtree.
//****************************************************************************

template <class T>
int AvlTree<T>::GetHeight(AvlNode<T>* subtree) const
{
	if (subtree == NULL)
		return 0;
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
//		Calculates width to space out nodes and calls DispLevel to print
//	nodes on given level.
//
//	Parameters:
//		height: height of tree.
//****************************************************************************

template <class T>
void AvlTree<T>::PrintLevel(int height) const
{
	AvlNode<T>* temp = root;
	
	// leftmost point
	int value = pow(2, GetHeight(root) - height + 2);
	cout << setw(value) << "";
	DispLevel(temp, height, value);
}




//****************************************************************************
//		Displays the nodes on given level and will display 'x' where the
//	pointers are NULL.
//
//	Parameters:
//		subtree: node to be displayed.
//		level: current level.
//		displace: displacement.
//****************************************************************************

template <class T>
void AvlTree<T>::DispLevel(AvlNode<T>* subtree, int level, int displace) const
{
	int disp = 2 * displace;
	if (level == 0)
	{
		if (subtree == NULL)
		{
			cout << " x ";
			cout << setw(disp - 3) << "";
			return;
		}
		else
		{
			int result = ((subtree->data <= 1) ? 1: log10(subtree->data) + 1);
			if (subtree == cursor)
				cout << "[" << subtree->data << "]";
			else
				cout << subtree->data;

			cout << setw(disp - result) << "";
		}
	}
	
	else
	{
		if (subtree == NULL && level >= 1)
		{
			DispLevel(NULL, level - 1, displace);
			DispLevel(NULL, level - 1, displace);
		}
		else
		{
			DispLevel(subtree->left, level - 1, displace);
			DispLevel(subtree->right, level - 1, displace);
		}
	}
}



//****************************************************************************
//		Method to print the data of the node that the cursor pointer 
//	references.  If cursor is NULL, then '[]' will be displayed.
//
//	Parameters:
//		N/A.
//****************************************************************************

template <class T>
void AvlTree<T>::PrintCursor() const
{
	if (cursor != NULL)
	{
		cout << "[" << cursor->data << "]" << endl;
	}
	else
	{
		cout << "[]" << endl;
	}
}




//****************************************************************************
//		In order print method.
//
//	Parameters:
//		N/A.
//****************************************************************************

template <class T>
void AvlTree<T>::InOrder() const
{
	cout << "[ "; 
	InOrderHelper(root); 
	cout << "]";
}




//****************************************************************************
//		Helper method to print the contents of the tree in order.
//
//	Parameters:
//		subtree: pointer to the root of subtree.
//****************************************************************************

template <class T>
void AvlTree<T>::InOrderHelper(const AvlNode<T>* subtree) const
{
    if (subtree != NULL)
    {
        InOrderHelper(subtree->left);
        
        if (subtree == cursor)
        {
        	cout << "[" << subtree->data << "] ";
        }
        else
        {
			cout << subtree->data << " ";
		}
			
        InOrderHelper(subtree->right);
    }
}




//****************************************************************************
//		Pre-order print method.
//
//	Parameters:
//		N/A.
//****************************************************************************

template <class T>
void AvlTree<T>::PreOrder() const
{
	cout << "[ "; 
	PreOrderHelper(root); 
	cout << "]";
}




//****************************************************************************
//		Helper method to print the contents of the tree in pre order.
//
//	Parameters:
//		subtree: pointer to the root of subtree.
//****************************************************************************

template <class T>
void AvlTree<T>::PreOrderHelper(const AvlNode<T>* subtree) const
{
    if (subtree != NULL)
    {
    	if (subtree == cursor)
    	{
        	cout << "[" << subtree->data << "] ";
        }
        else
        {
			cout << subtree->data << " ";
		}
			
        PreOrderHelper(subtree->left);
        PreOrderHelper(subtree->right);
    }
}




//****************************************************************************
//		Post-order print method.
//
//	Parameters:
//		N/A.
//****************************************************************************

template <class T>
void AvlTree<T>::PostOrder() const
{
	cout << "[ "; 
	PostOrderHelper(root); 
	cout << "]";
}




//****************************************************************************
//		Helper method to print the contents of the tree in post order.
//
//	Parameters:
//		subtree: pointer to the root of subtree.
//****************************************************************************

template <class T>
void AvlTree<T>::PostOrderHelper(const AvlNode<T>* subtree) const
{
    if (subtree != NULL)
    {
        PostOrderHelper(subtree->left);
        PostOrderHelper(subtree->right);
        
        if (subtree == cursor)
        {
        	cout << "[" << subtree->data << "] ";
        }
        else
        {
			cout << subtree->data << " ";
		}
    }
}



//****************************************************************************
//		Copy Constructor.
//****************************************************************************

template <class T>
AvlTree<T>::AvlTree(const AvlTree& myAvl)
{
    if(!myAvl.root)
    {
        root = NULL;
        return;
    }
    CopyHelper(root, myAvl.root);
}



//****************************************************************************
//		Helper method to recursively allocate memory for the new tree.
//****************************************************************************

template<class T>
void AvlTree<T>::CopyHelper(AvlNode<T>*& aRoot, AvlNode<T>* myRoot)
{
    if(!myRoot)
    {
        aRoot = NULL;
    }
    else
    {
        aRoot = new AvlNode<T>(myRoot->data);
        CopyHelper(aRoot->left, myRoot->left);
        CopyHelper(aRoot->right, myRoot->right);
    }
}




//****************************************************************************
//		Destructor.
//****************************************************************************

template<class T>
AvlTree<T>::~AvlTree()
{
    DestroyHelper(root);
    root = NULL;
}



//****************************************************************************
//		Helper method to recursively deallocate the tree.
//****************************************************************************

template <class T>
void AvlTree<T>::DestroyHelper(AvlNode<T>*& Tree)
{
   if (Tree != NULL)
   {
      DestroyHelper(Tree->left);
      DestroyHelper(Tree->right);
      delete Tree;
   }
   Tree = NULL;
}




//****************************************************************************
//		Assignment Operator.
//****************************************************************************

template <class T>
AvlTree<T>& AvlTree<T>::operator=(const AvlTree<T>& rightTree)
{
    if(this != &rightTree)
    {
        if(root != NULL)
        {
			DestroyHelper(root);
		}
		if(rightTree.root == NULL)
		{
			root = NULL;
		}
		else
		{
			CopyHelper(root, rightTree.root);
		}
    }
    return *this;
}



template class AvlTree<int>;
template class AvlTree<double>;
template class AvlTree<float>;
template class AvlTree<char>;
