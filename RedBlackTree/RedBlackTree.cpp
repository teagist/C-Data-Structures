//*************************************************************************** 
//	Implementation File for Templated Red-Black Tree
//	Programmed by: Houston Brown
//	Last Compiled Date: 7/31/2022
//***************************************************************************

#include "RedBlackTree.h"




//***************************************************************************
//	    Method will return address of the sibling node of the caller.  If
//	the caller is the root, NULL will be returned.
//
//	Parameters:
//		N/A.
//***************************************************************************
template <class K, class V>
RBNode<K, V>* RBNode<K, V>::GetSibling()
{
    if (parent == NULL)
    {
	return NULL;
    }
    if (IsOnLeft())
    {
	return parent->right;
    }

    return parent->left;
}


//***************************************************************************
//	    Method to insert key value pair as a new node into the Red-Black 
//	tree.  If the given key is already in the tree, an appropriate message
//	will be displayed and the method will return.  Once the new node has 
//	been inserted into the tree, the tree will be checked to ensure that
//	none of the ordering properties have been violated.  If they have, then
//	they will be corrected.  The cursor pointer will be set to point to the
//	newly inserted node.
//
//	Parameters:
//		key  : the key to be inserted.
//		value: the value to be inserted.
//***************************************************************************
template <class K, class V>
void RBTree<K, V>::Insert(K key, V value)
{
    if (Search(key))
    {
	cerr << "No duplicates allowed." << endl;
	return;
    }
    else
    {
	RBNode<K, V>* newNode = new RBNode<K,V>(key, value);
        cursor = newNode;
	
	RBNode<K, V>* temp = NULL;
	RBNode<K, V>* rootPtr = root;
	
	while (rootPtr != NULL) 
	{
	    temp = rootPtr;
	    if (newNode->data < rootPtr->data)
	    {
	    	rootPtr = rootPtr->left;
	    }
	    else 
	    {
	    	rootPtr = rootPtr->right;
	    }
	}
	
        newNode->parent = temp;
	if (temp == NULL) 
	{
	    root = newNode;
	    root->color = BLACK;
	} 
	else if (newNode->data < temp->data) 
	{
	    temp->left = newNode;
	}
	else 
	{
	    temp->right = newNode;
	}
	
	if (newNode->parent == NULL) 
	{
	    newNode->color = BLACK;
	    return;
	}
	
	if (newNode->parent->parent == NULL)
	{
	    return;
	}
	    	
	FixViolation(newNode);
    }
}




//***************************************************************************
//		Method to rotate the arrangement of subtree and children to
//	the left.  
//
//	Parameters:
//		subtree: pointer to the root of subtree.
//***************************************************************************

template <class K, class V>
void RBTree<K, V>::RotateLeft(RBNode<K, V>*& subtree)
{
	RBNode<K, V>* rightPtr = subtree->right;

    subtree->right = rightPtr->left;

    if (subtree->right != NULL)
        subtree->right->parent = subtree;

    rightPtr->parent = subtree->parent;

    if (subtree->parent == NULL)
        root = rightPtr;

    else if (subtree == subtree->parent->left)
        subtree->parent->left = rightPtr;

    else
        subtree->parent->right = rightPtr;

    rightPtr->left = subtree;
    subtree->parent = rightPtr;
}




//***************************************************************************
//		Method to rotate the arrangement of subtree and children to
//	the right.   
//
//	Parameters:
//		subtree: pointer to the root of subtree.
//***************************************************************************

template <class K, class V>
void RBTree<K, V>::RotateRight(RBNode<K, V>*& subtree)
{
	RBNode<K, V>* leftPtr = subtree->left;

    subtree->left = leftPtr->right;

    if (subtree->left != NULL)
        subtree->left->parent = subtree;

    leftPtr->parent = subtree->parent;

    if (subtree->parent == NULL)
        root = leftPtr;

    else if (subtree == subtree->parent->left)
        subtree->parent->left = leftPtr;

    else
        subtree->parent->right = leftPtr;

    leftPtr->right = subtree;
    subtree->parent = leftPtr;
}




//***************************************************************************
//		Method to correct any violations to the Red-Black tree ordering
//	properties.  If any rotations, recolorings, or swapping of values is
//	needed, they will occur here.  Finally the root will be ensured to be
//	colored black.    
//
//	Parameters:
//		subtree: pointer to the root of subtree.
//***************************************************************************

template <class K, class V>
void RBTree<K, V>::FixViolation(RBNode<K, V>* subtree)
{
	RBNode<K, V>* parentPtr = NULL;
    RBNode<K, V>* grandParentPtr = NULL;

    while ((subtree != root) && (subtree->color != BLACK) &&
          (subtree->parent->color == RED))
    {
        parentPtr = subtree->parent;
        grandParentPtr = subtree->parent->parent;

        //  Case : A
        //    Parent of subtree is left child
        //    of Grand-parent of subtree 
        if (parentPtr == grandParentPtr->left)
        {

            RBNode<K, V>* unclePtr = grandParentPtr->right;

            // Case : 1
            //   The uncle of subtree is also red
            //   Only Recoloring required 
            if (unclePtr != NULL && unclePtr->color ==
                RED)
            {
                grandParentPtr->color = RED;
                parentPtr->color = BLACK;
                unclePtr->color = BLACK;
                subtree = grandParentPtr;
            }

            else
            {
                // Case : 2
                //   subtree is right child of its parent
                //   Left-rotation required 
                if (subtree == parentPtr->right)
                {
                    RotateLeft(parentPtr);
                    subtree = parentPtr;
                    parentPtr = subtree->parent;
                }

                // Case : 3
                //   subtree is left child of its parent
                //   Right-rotation required 
                RotateRight(grandParentPtr);
                swap(parentPtr->color,
                    grandParentPtr->color);
                subtree = parentPtr;
            }
        }

        // Case : B
        //   Parent of subtree is right child
        //   of Grand-parent of subtree 
        else
        {
            RBNode<K, V>* unclePtr = grandParentPtr->left;

            //  Case : 1
            //    The uncle of subtree is also red
            //    Only Recoloring required 
            if ((unclePtr != NULL) && (unclePtr->color ==
                RED))
            {
                grandParentPtr->color = RED;
                parentPtr->color = BLACK;
                unclePtr->color = BLACK;
                subtree = grandParentPtr;
            }
            else
            {
                // Case : 2
                //   subtree is left child of its parent
                //   Right-rotation required 
                if (subtree == parentPtr->left)
                {
                    RotateRight(parentPtr);
                    subtree = parentPtr;
                    parentPtr = subtree->parent;
                }

                // Case : 3
                //   subtree is right child of its parent
                //   Left-rotation required 
                RotateLeft(grandParentPtr);
                swap(parentPtr->color,
                    grandParentPtr->color);
                subtree = parentPtr;
            }
        }
    }

    root->color = BLACK;
}	
/* End of FixViolation method */




//***************************************************************************
//		Method to search for a given key within the tree.  If the key is 
//	found, true will be returned.  Otherwise, false will be returned.  
//
//	Parameters:
//		key: the key of the node to be found.
//***************************************************************************

template <class K, class V>
bool RBTree<K, V>::Search(const K key)
{
	RBNode<K, V>* temp = root;
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




//***************************************************************************
//		Method to return the address of a node that contains the given key.
//	If the node cannot be found, NULL is returned.
//
//	Parameters:
//		key: the key of the node to be found.
//***************************************************************************

template <class K, class V>
RBNode<K, V>* RBTree<K, V>::GetNode(const K key)
{
	RBNode<K, V>* temp = root;
	
    while (temp != NULL) 
	{
        if (key < temp->data) 
		{
            if (temp->left == NULL)
                break;
            else
                temp = temp->left;
        }
        else if (key == temp->data) 
            break;
        else 
		{
            if (temp->right == NULL)
                break;
            else
                temp = temp->right;
        }
    }

    return temp;
}




//***************************************************************************
//		Method to delete node by the given key.  If the tree is empty, a 
//	message will be displayed.  If there is not a node with the given key,
//	an appropriate message will be displayed.  Otherwise, the position of
//	the node will be determined, and the node deleted.
//
//	Parameters:
//		key: the key of the node to be deleted.
//***************************************************************************

template <class K, class V>
void RBTree<K, V>::Delete(const K key)
{
	if (root == NULL)
	{
		cerr << "The tree is empty." << endl;
		return;
	}
	
	RBNode<K, V>* nodePtr = GetNode(key);

    if (nodePtr->data != key)
        cerr << "There is not a node with value: " << key << endl;
    else
		Delete(nodePtr);
		
	if (root == NULL)
		cursor = NULL;

}




//***************************************************************************
//		Method to perform actual deletion of node and maintain order
//	properties of red-black tree.
//
//	Parameters:
//		delNode: address of the node to be deleted.
//***************************************************************************

template <class K, class V>
void RBTree<K, V>::Delete(RBNode<K, V>*& delNode)
{	
	RBNode<K, V>* replNode = Replace(delNode);
    RBNode<K, V>* parent = delNode->parent;
    bool bothBlack = ((replNode == NULL || replNode->color == BLACK) && 
					  (delNode->color == BLACK));

    if (replNode == NULL) 
	{
        // node to be deleted is a leaf
        if (delNode == root)    // node to be deleted is root
        {
        	cursor = NULL;
            root = NULL;
        }
        else 
		{
            if (bothBlack) 
			{
                // node to be deleted is leaf, fix double black at delNode
                FixDoubleBlack(delNode); 
            }
            else 
			{
                if (delNode->GetSibling() != NULL)
                    delNode->GetSibling()->color = RED;
            }

            // delete delNode from the tree
            if (delNode->IsOnLeft())
                parent->left = NULL;
            else
                parent->right = NULL;
        }
        
        cursor = delNode->parent;	
        delete delNode;
        return;
    }

    if (delNode->left == NULL || delNode->right == NULL)
	{
        // node to be deleted has 1 child
        if (delNode == root) 
		{
            // node to be deleted is root, swap data replacement
            delNode->data = replNode->data;
            delNode->left = delNode->right = NULL;
            
            if (delNode->left)
        		cursor = delNode->left;
        	else if (delNode->right)
        		cursor = delNode->right;
        		
            delete replNode;
        }
        else 
		{
            // Detach node to be deleted from tree and move replacement up
            if (delNode->IsOnLeft())
                parent->left = replNode;
            else 
                parent->right = replNode;
    
            delete delNode;
            cursor = replNode->parent;
            replNode->parent = parent;
            
            if (bothBlack)
                FixDoubleBlack(replNode);
            else
                replNode->color = BLACK;
        }
        return;
    }

    // node to be deleted has 2 children 
    SwapValues(replNode, delNode);   // swap values with successor and recurse
    Delete(replNode);
}
/* End of Delete method */




//***************************************************************************
//		Method to correct double black condition which would violate the 
//	  depth property after deletion has been made.
//
//	Parameters:
//		subtree: pointer to the root of subtree.
//***************************************************************************

template <class K, class V>
void RBTree<K, V>::FixDoubleBlack(RBNode<K, V>* subtree)
{
	if (subtree == root)
        return;

    RBNode<K, V>* sibling = subtree->GetSibling();
	RBNode<K, V>* parent = subtree->parent;
	
    if (sibling == NULL)   			// No sibiling, double black pushed up
        FixDoubleBlack(parent);
        
    else 
	{
        if (sibling->color == RED)
		{
            parent->color = RED;
            sibling->color = BLACK;
            
            if (sibling->IsOnLeft())   // left case
                RotateRight(parent);
            else  
                RotateLeft(parent);   // right case
                
            FixDoubleBlack(subtree);
        }
        else 
		{
            // Sibling black
            if (sibling->HasRedChild()) 
			{
                // at least 1 red children
                if (sibling->left != NULL && sibling->left->color == RED) 
				{
                    if (sibling->IsOnLeft()) 	// left left
					{
                        sibling->left->color = sibling->color;
                        sibling->color = parent->color;
                        RotateRight(parent);
                    }
                    else  	// right left
					{
                        sibling->left->color = parent->color;
                        RotateRight(sibling);
                        RotateLeft(parent);
                    }
                }
                else 
				{
                    if (sibling->IsOnLeft()) 	// left right
					{
                        sibling->right->color = parent->color;
                        RotateLeft(sibling);
                        RotateRight(parent);
                    }
                    else  	// right right
					{
                        sibling->right->color = sibling->color;
                        sibling->color = parent->color;
                        RotateLeft(parent);
                    }
                }
                parent->color = BLACK;
            }
            else   // 2 black children
			{
                sibling->color = RED;
                if (parent->color == BLACK)
                    FixDoubleBlack(parent);
                else
                    parent->color = BLACK;
            }
        }
    }
}
/* End of FixDoubleBlack method */




//***************************************************************************
//		Method returns pointer to a node that does not have a left child
//	in the given subtree  
//
//	Parameters:
//		subtree: pointer to the root of subtree.
//***************************************************************************

template <class K, class V>
RBNode<K, V>* RBTree<K, V>::Successor(RBNode<K, V>* subtree)
{
	RBNode<K, V>* temp = subtree;

    while (temp->left != NULL)
        temp = temp->left;

    return temp;
}




//***************************************************************************
//		Method returns pointer to a node that replaces the deleted node
//	in the tree.  
//
//	Parameters:
//		subtree: pointer to the root of subtree.
//***************************************************************************

template <class K, class V>
RBNode<K, V>* RBTree<K, V>::Replace(RBNode<K, V>* subtree)
{
    if (subtree->left != NULL && subtree->right != NULL)
        return Successor(subtree->right);

    if (subtree->left == NULL && subtree->right == NULL)
        return NULL;

    // when single child
    if (subtree->left != NULL)
        return subtree->left;
    else
        return subtree->right;
}




//***************************************************************************
//		Method to swap key and value of two given nodes.
//
//	Parameters:
//		firstNode: node pointer that will hold secNode's data.
//		secNode  : node pointer that will hold firstNode's data.
//***************************************************************************

template <class K, class V>
void RBTree<K, V>::SwapValues(RBNode<K, V>* firstNode, RBNode<K, V>* secNode)
{
	K key;
	V value;
	
    key = firstNode->data;
    value = firstNode->name;
    
    firstNode->data = secNode->data;
    firstNode->name = secNode->name;
    
    secNode->data = key;
    secNode->name = value;
}




//***************************************************************************
//		Method to delete current tree and free up allocated storage.  Ends
//	by setting the root and cursor pointers to NULL.
//
//	Parameters:
//		N/A.
//***************************************************************************

template <class K, class V>
void RBTree<K, V>::ClearTree()
{
	ClearHelper(root);
	root   = NULL;
	cursor = NULL;
}




//***************************************************************************
//		Helper method to clear and free all dynamically allocated storage
//	allocated by current Red-Black tree.
//
//	Parameters:
//		tree: pointer to the root of the tree.
//***************************************************************************

template <class K, class V>
void RBTree<K, V>::ClearHelper(RBNode<K, V>* tree)
{
	if (tree != NULL)
   {
      ClearHelper(tree->left);
      ClearHelper(tree->right);
      delete tree;
   }
   tree = NULL;
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

template <class K, class V>
void RBTree<K, V>::PruneHelper(RBNode<K, V>* subtree)
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





//***************************************************************************
//		Method to print the tree in level order.
//
//	Parameters:
//		N/A.
//***************************************************************************

template <class K, class V>
void RBTree<K, V>::PrintTree()
{
	if (!root)
        return;

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




//***************************************************************************
//		Calculates the height of the tree.
//
//	Parameters:
//		subtree: pointer to the root of subtree.
//***************************************************************************

template <class K, class V>
int RBTree<K, V>::TreeHeight(RBNode<K, V>* subtree)
{
	if (subtree == NULL)
		return 0;
	else
	{
		int leftHeight = TreeHeight(subtree->left);
		int rightHeight = TreeHeight(subtree->right);
		
		if (leftHeight >= rightHeight)
			return leftHeight + 1;
		else
			return rightHeight + 1;
	}
}




//***************************************************************************
//		Calculates width to space out nodes and calls DispLevel to print
//	nodes on given level.
//
//	Parameters:
//		height: height of tree.
//***************************************************************************

template <class K, class V>
void RBTree<K, V>::PrintLevel(int height)
{
	RBNode<K, V>* temp = root;
	
	// leftmost point
	int value = pow(2, TreeHeight(root) - height + 3);
	cout << setw(value - 4) << "";
	DispLevel(temp, height, value);
}




//***************************************************************************
//		Displays the nodes on given level and will display 'x' where the
//	pointers are NULL.
//
//	Parameters:
//		subtree: node to be displayed.
//		level: current level.
//		displace: displacement.
//***************************************************************************

template <class K, class V>
void RBTree<K, V>::DispLevel(RBNode<K, V>* subtree, int level, int displace)
{
	int disp = 2 * displace;
	if (level == 0)
	{
		if (subtree == NULL)
		{
			cout << " x ";
			cout << setw(disp + 4) << "";
			return;
		}
		else
		{
			int result = ((subtree->data <= 1) ? 1: log10(subtree->data) - 5);
			if (subtree->color == 0)
				if (subtree == cursor)
				{
					cout << " [<" << subtree->data << ", " << subtree->name;
					cout << ">(R)]";
				}
				else
				{
					cout << " <" << subtree->data << ", " << subtree->name;
					cout << ">(R)";
				}
			else
				if (subtree == cursor)
				{
					cout << " [<" << subtree->data << ", " << subtree->name;
					cout << ">(B)]";
				}
				else
				{
					cout << " <" << subtree->data << ", " << subtree->name;
					cout << ">(B)";
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




//***************************************************************************
//		In order print method.
//
//	Parameters:
//		N/A.
//***************************************************************************

template <class K, class V>
void RBTree<K, V>::InOrder() 
{
	cout << "[ "; 
	InOrder(root); 
	cout << "]";
}




//***************************************************************************
//		Helper method to print the contents of the tree in order.
//
//	Parameters:
//		subtree: pointer to the root of subtree.
//***************************************************************************

template <class K, class V>
void RBTree<K, V>::InOrder(RBNode<K, V>* subtree)
{
    if (subtree != NULL)
    {
        InOrder(subtree->left);
        if (subtree == cursor)
        	cout << "[" << subtree->data << "] ";
        else
			cout << subtree->data << " ";
        InOrder(subtree->right);
    }
}




//***************************************************************************
//		Pre-order print method.
//
//	Parameters:
//		N/A.
//***************************************************************************

template <class K, class V>
void RBTree<K, V>::PreOrder() 
{
	cout << "[ "; 
	PreOrder(root);
	cout << "]"; 
}




//***************************************************************************
//		Helper method to print the contents of the tree in pre order.
//
//	Parameters:
//		subtree: pointer to the root of subtree.
//***************************************************************************

template <class K, class V>
void RBTree<K, V>::PreOrder(RBNode<K, V>* subtree)
{
    if (subtree != NULL)
    {
    	if (subtree == cursor)
        	cout << "[" << subtree->data << "] ";
        else
			cout << subtree->data << " ";
        PreOrder(subtree->left);
        PreOrder(subtree->right);
    }
}




//***************************************************************************
//		Post-order print method.
//
//	Parameters:
//		N/A.
//***************************************************************************

template <class K, class V>
void RBTree<K, V>::PostOrder() 
{
	cout << "[ ";
	PostOrder(root);
	cout << "]";
}




//***************************************************************************
//		Helper method to print the contents of the tree in post order.
//
//	Parameters:
//		subtree: pointer to the root of subtree.
//***************************************************************************

template <class K, class V>
void RBTree<K, V>::PostOrder(RBNode<K, V>* subtree)
{
    if (subtree != NULL)
    {
        PostOrder(subtree->left);
        PostOrder(subtree->right);
        if (subtree == cursor)
        	cout << "[" << subtree->data << "] ";
        else
			cout << subtree->data << " ";
    }
}




//***************************************************************************
//		Method to print the data of the node that the cursor pointer 
//	references.  If cursor is NULL, then '[]' will be displayed.
//
//	Parameters:
//		N/A.
//***************************************************************************

template <class K, class V>
void RBTree<K, V>::PrintCursor()
{
	if (cursor != NULL)
	{
		if (cursor->color == 0)
			cout << " [<" << cursor->data << ", " << cursor->name << ">(R)]\n";
		else
			cout << " [<" << cursor->data << ", " << cursor->name << ">(B)]\n";
	}
	else
		cout << "[]" << endl;
}





template class RBTree<int, string>;
