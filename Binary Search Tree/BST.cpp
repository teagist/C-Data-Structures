//****************************************************************************
//	Implementation File for Templated Binary Search Tree
//	Programmed by: Houston Brown
//	Last Compiled Date: 10/2/2025
//****************************************************************************

#include "BST.h"

//****************************************************************************
//		Method to insert key into the Binary Search Tree.  If the key is
//	already in the tree, a message will be displayed informing the user.
//	Otherwise, the method will try to allocate memory for a new node.  If
//	it is successful the insertion will proceed, otherwise the exception
//	will be caught and an appropriate message displayed.
//
//	Parameters:
//		key: the key to be inserted.
//		subtree: pointer to the root of subtree.
//****************************************************************************
template <class T>
void BST<T>::InsertHelper(const T key, BNode<T>*& subtree)
{
	if (subtree)
    {
        if (key < subtree->data)
        {
		    return InsertHelper(key, subtree->left);
		}
		    
        else if (key > subtree->data)
        {
		    return InsertHelper(key, subtree->right);
		}
        else
        {
		    cerr << "No duplicates allowed, please try again." << endl;
		}
    }
    
    else
    {
    	try
    	{
    		subtree = new BNode<T>(key);
    	}
    	catch (bad_alloc & ex)
    	{
    		cerr << "Failed to insert " << key << " into the tree due to";
    		cerr << " bad memory allocation." << endl;
		}
	}
    
	cursor = subtree;
}

//****************************************************************************
//		Method to search for a given key within the Binary Search Tree.
//	The method will traverse the tree based on the value of the key.  If it
//	is found, the method will return true.  Otherwise, the method will 
//	return false.
//
//	Parameters:
//		key: the key to be searched for.
//****************************************************************************
template <class T>
bool BST<T>::Search(const T key)
{
	BNode<T>* temp = root;
	
	while (temp != NULL)
	{
		if (key < temp->data)
		{
			if (temp->left == NULL)
			{
				return false;
			}
			else
			{
				temp = temp->left;
			}
		}
		
		else if (key == temp->data)
		{
			cursor = temp;
			return true;
		}
		
		else
		{
			if (temp->right == NULL)
			{
				return false;
			}
			else
			{
				temp = temp->right;
			}
		}
	}
}

//****************************************************************************
//		Method to delete a given key into the Binary Search Tree.  If this
//	method is called on an empty tree, it will return.  If the key cannot be
//	found within the tree, a message will be displayed to the user.  
//	Otherwise, the method will proceed with deletion in the helper function.
//
//	Parameters:
//		key: the key to be deleted.
//****************************************************************************
template <class T>
void BST<T>::Delete(const T key)
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
//		Helper method to delete a node with a given key.  This method will
//	traverse the tree until it has found the node with the key to be 
//	deleted.  If the node has no children, it will simply be deleted.  If
//	the node has one child, the data from the child will take its place
//	and the child deleted.  If the node has both children, then the node
//	will swap data values with the value that is returned from the 
//	GetMin function.  
//
//	Parameters:
//		key: the key to be deleted.
//		subtree: pointer to the root of subtree.
//****************************************************************************
template <class T>
BNode<T>* BST<T>::DeleteHelper(const T key, BNode<T>*& subtree)
{
	if (subtree == NULL)
	{
		return subtree;
	}
	
	if (key < subtree->data)
	{
		subtree->left = DeleteHelper(key, subtree->left);
	}
	else if (key > subtree->data)
	{
		subtree->right = DeleteHelper(key, subtree->right);
	}
	else
	{
		if (subtree->left == NULL && subtree->right == NULL)
		{
			BNode<T>* parent = NULL;
			if (parent = GetParent(subtree))
			{
				cursor = parent;
			}

			delete subtree;
			subtree = NULL;
		}
			
		else if (subtree->left == NULL)
		{
			BNode<T>* temp = subtree;
			subtree = subtree->right;
			cursor = subtree;
			delete temp;
		}
		else if (subtree->right == NULL)
		{
			BNode<T>* temp = subtree;
			subtree = subtree->left;
			cursor = subtree;
			delete temp;
		}
		else
		{
			BNode<T>* temp = GetMin(subtree->right);
			subtree->data = temp->data;
			
			if (subtree->left)
			{
				cursor = subtree->left;
			}
			else if (subtree->right)
			{
				cursor = subtree->right;
			}
				
			subtree->right = DeleteHelper(temp->data, subtree->right);
		}
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
void BST<T>::PruneHelper(BNode<T>* subtree)
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
//		Method to return a pointer to the left most value in the tree.
//
//	Parameters:
//		subtree: pointer to the root of subtree.
//****************************************************************************
template <class T>
BNode<T>* BST<T>::GetMin(BNode<T>* subtree) const
{
	while(subtree->left != NULL) 
	{
		subtree = subtree->left;
	}
	return subtree;
}

//****************************************************************************
//		Method to traverse the tree and return the address of the parent
//	of the caller.  
//
//	Parameters:
//		subtree: pointer to the root of subtree.
//****************************************************************************
template <class T>
BNode<T>* BST<T>::GetParent(BNode<T>* subtree) const
{
	BNode<T>* parent = NULL;
	BNode<T>* top = root;

	while (top != NULL && top != subtree)
	{
		if (top != subtree)
		{
			parent = top;
		}
		
		if (top->data > subtree->data)
		{
			top = top->left;
		}
		else
		{
			top = top->right;
		}
	}
	return parent;
}

//****************************************************************************
//		Method to print the tree in level order.
//
//	Parameters:
//		N/A.
//****************************************************************************
template <class T>
void BST<T>::PrintTree() const
{
	if (!root)
	{
        return;
    }

    else
    {
        int ctr = 0;
        while (ctr <= TreeHeight(root))
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
int BST<T>::TreeHeight(BNode<T>* subtree) const
{
	if (subtree == NULL)
	{
		return 0;
	}
	else
	{
		int leftHeight = TreeHeight(subtree->left);
		int rightHeight = TreeHeight(subtree->right);
		
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
void BST<T>::PrintLevel(int height) const
{
	BNode<T>* temp = root;
	
	// leftmost point
	int value = pow(2, TreeHeight(root) - height + 2);
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
void BST<T>::DispLevel(BNode<T>* subtree, int level, int displace) const
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
			{
				cout << "[" << subtree->data << "]";
			}
			else
			{
				cout << subtree->data;
			}

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
void BST<T>::PrintCursor() const
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
void BST<T>::InOrder() const
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
void BST<T>::InOrderHelper(const BNode<T>* subtree) const
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
void BST<T>::PreOrder() const
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
void BST<T>::PreOrderHelper(const BNode<T>* subtree) const
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
void BST<T>::PostOrder() const
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
void BST<T>::PostOrderHelper(const BNode<T>* subtree) const
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
BST<T>::BST(const BST& myBST)
{
    if(!myBST.root)
    {
        root = NULL;
        return;
    }
    CopyHelper(root, myBST.root);
}

//****************************************************************************
//		Helper method to recursively allocate memory for the new tree.
//****************************************************************************
template<class T>
void BST<T>::CopyHelper(BNode<T>*& aRoot, BNode<T>* myRoot)
{
    if(!myRoot)
    {
        aRoot = NULL;
    }
    else
    {
        aRoot = new BNode<T>(myRoot->data);
        CopyHelper(aRoot->left, myRoot->left);
        CopyHelper(aRoot->right, myRoot->right);
    }
}

//****************************************************************************
//		Destructor.
//****************************************************************************
template<class T>
BST<T>::~BST()
{
    DestroyHelper(root);
    root = NULL;
}

//****************************************************************************
//		Helper method to recursively deallocate the tree.
//****************************************************************************
template <class T>
void BST<T>::DestroyHelper(BNode<T>*& Tree)
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
BST<T>& BST<T>::operator=(const BST<T>& rightTree)
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



template class BST<int>;
template class BST<float>;
template class BST<double>;
template class BST<bool>;
template class BST<char>;
