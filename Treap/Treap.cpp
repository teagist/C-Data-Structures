//****************************************************************************
//	Implementation File for Templated Treap
//	Programmed by: Houston Brown
//	Last Compiled Date: 7/17/2023
//****************************************************************************

#include "Treap.h"




//****************************************************************************
//	    Helper method to perform insertion.  If the heap order has been 
//	violated, then a rotation will be performed.
//
//	Parameters:
//		key: the element to be inserted.
//		subtree: pointer to the root of subtree.
//****************************************************************************
template <class T>
void Treap<T>::InsertHelper(T key, TreapNode<T> *&subtree)
{
    if (!subtree)
    {
        subtree = new TreapNode<T>(key);
        return;
    }

    if (key < subtree->data)
    {
        InsertHelper(key, subtree->left);
 
        if (subtree->left != NULL && subtree->left->priority >
				      subtree->priority)
	{
            RotateRight(subtree);
        }
    }
    else 
	{
        InsertHelper(key, subtree->right);
 
        if (subtree->right != NULL && subtree->right->priority >
				      subtree->priority) 
	{
            RotateLeft(subtree);
        }
    }
}


//****************************************************************************
//	Utility function to perform a left rotation of the tree.
//
//	Parameters:
//		subtree: pointer to the root of subtree.
//****************************************************************************
template <class T>
void Treap<T>::RotateLeft(TreapNode<T>* &subtree)
{
    TreapNode<T>* rightPtr = subtree->right;
    TreapNode<T>* temp = subtree->right->left;
	
    rightPtr->left = subtree;
    subtree->right = temp;
    subtree = rightPtr;
}


//****************************************************************************
//	Utility function to perform a right rotation of the tree.
//
//	Parameters:
//		subtree: pointer to the root of subtree.
//****************************************************************************
template <class T>
void Treap<T>::RotateRight(TreapNode<T>* &subtree)
{
    TreapNode<T>* leftPtr = subtree->left;
    TreapNode<T>* temp = subtree->left->right;
	
    leftPtr->right = subtree;
    subtree->left = temp;
    subtree = leftPtr;
}


//****************************************************************************
//	    Helper method to perform a search of the Treap.  The function will
//	return true if the item is found, and false otherwise.
//
//	Parameters:
//		key: the element to be searched for.
//		subtree: pointer to the root of subtree.
//****************************************************************************
template <class T>
bool Treap<T>::SearchHelper(T key, TreapNode<T> *subtree) const
{
    if (subtree == NULL)
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


//****************************************************************************
//		Helper method to delete a given key from the Treap.  If the key
//	is not in the Treap, then this function will return.
//
//	Parameters:
//		key: the element to be deleted.
//		subtree: pointer to the root of subtree.
//****************************************************************************

template <class T>
void Treap<T>::DeleteHelper(T key, TreapNode<T> *&subtree)
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
		
	else
	{
		if (subtree->left == NULL && subtree->right == NULL)
		{
			delete subtree;
			subtree = NULL;
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
			TreapNode<T> *child;
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
void Treap<T>::PruneHelper(TreapNode<T>* subtree)
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
//		Treap method to clear and deallocate all dynamic memory allocated
//	to the nodes of the treap.  
//
//	Parameters:
//		N/A.
//****************************************************************************

template <class T>
void Treap<T>::Clear()
{	
	ClearHelper(root);
	root = NULL;
}




//****************************************************************************
//		Helper method to deallocate all nodes of the tree.
//
//	Parameters:
//		subtree: pointer to the root of subtree.
//****************************************************************************

template <class T>
void Treap<T>::ClearHelper(TreapNode<T> *&subtree)
{
	if (subtree != NULL)
   {
      ClearHelper(subtree->left);
      ClearHelper(subtree->right);
      delete subtree;
   }
   subtree = NULL;
}




//****************************************************************************
//		Treap method to print the contents of the tree in level order.   
//
//	Parameters:
//		N/A.
//****************************************************************************

template <class T>
void Treap<T>::TreePrint() const
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




//****************************************************************************
//		Treap method to calculate the distance from the beginning of a new
//	line.    
//
//	Parameters:
//		level: current level that we are printing from.  
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
//		Treap method to print the data and priority of the nodes and 
//	calculates the distance between to points.     
//
//	Parameters:
//		subtree: pointer the root of the subtree.
//		level: current level that we are printing from.
//		dist: the calculated distance between two points.
//****************************************************************************

template <class T> 
void Treap<T>::DispLevel(TreapNode<T>* subtree, int level, int dist) const
{
	int disp = 2 * dist;
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
			int result = 0;
			if (subtree->priority <= 1)
				result = 1;
			else
				result = (log10(subtree->priority) + 1);
				
			cout << " " << subtree->data << " (" << subtree->priority << ") ";
			cout << setw(disp - result - 5) << "";
		}
	}
	
	else
	{
		if (subtree == NULL && level >= 1)
		{
			DispLevel(NULL, level - 1, dist);
			DispLevel(NULL, level - 1, dist);
		}
		else
		{
			DispLevel(subtree->left, level - 1, dist);
			DispLevel(subtree->right, level - 1, dist);
		}
	}
}




//****************************************************************************
//		Utility function to return the height of the Treap.
//
//	Parameters:
//		subtree: pointer to the root of subtree.
//****************************************************************************

template <class T>
int Treap<T>::GetHeight(TreapNode<T>* subtree) const
{
	if (subtree == NULL)
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
//		Helper method to print the contents of the Treap in order.
//
//	Parameters:
//		subtree: pointer to the root of subtree.
//****************************************************************************

template <class T>
void Treap<T>::InOrderHelper(TreapNode<T>* subtree) const
{
	if (subtree)
    {
		InOrderHelper(subtree->left);
        cout << subtree->data << " (" << subtree->priority << ")" << endl;
		InOrderHelper(subtree->right);	
    }
}




//****************************************************************************
//		Helper method to print the contents of the Treap in pre order
//	processing.
//
//	Parameters:
//		subtree: pointer to the root of subtree.
//****************************************************************************

template <class T>
void Treap<T>::PreOrderHelper(TreapNode<T>* subtree) const
{
	if (subtree)
    {
    	cout << subtree->data << " (" << subtree->priority << ")" << endl;
		PreOrderHelper(subtree->left);
		PreOrderHelper(subtree->right);	
    }
}




//****************************************************************************
//		Helper method to print the contents of the Treap in post order
//	processing.
//
//	Parameters:
//		subtree: pointer to the root of subtree.
//****************************************************************************

template <class T>
void Treap<T>::PostOrderHelper(TreapNode<T>* subtree) const
{
	if (subtree)
    {
		PostOrderHelper(subtree->left);
		PostOrderHelper(subtree->right);
		cout << subtree->data << " (" << subtree->priority << ")" << endl;	
    }
}



//****************************************************************************
//		Copy Constructor.
//****************************************************************************

template <class T>
Treap<T>::Treap(const Treap& myTreap)
{
    if(!myTreap.root)
    {
        root = NULL;
        return;
    }
    CopyHelper(root, myTreap.root);
}



//****************************************************************************
//		Helper method to recursively allocate memory for the new tree.
//****************************************************************************

template<class T>
void Treap<T>::CopyHelper(TreapNode<T>*& aRoot, TreapNode<T>* myRoot)
{
    if(!myRoot)
    {
        aRoot = NULL;
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
    root = NULL;
}



//****************************************************************************
//		Helper method to recursively deallocate the tree.
//****************************************************************************

template <class T>
void Treap<T>::DestroyHelper(TreapNode<T>*& Tree)
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
Treap<T>& Treap<T>::operator=(const Treap<T>& rightTree)
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



template class Treap<int>;
template class Treap<string>;
