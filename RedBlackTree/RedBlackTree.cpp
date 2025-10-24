//*************************************************************************** 
//	Implementation File for Templated Red-Black Tree
//	Programmed by: Houston Brown
//	Last Compiled Date: 10/24/2025
//***************************************************************************

#include "RedBlackTree.h"

//***************************************************************************
//	NAME: getSibling.
//
//	DESCRIPTION: Method will return address of the sibling node of the 
//	             caller.  If the caller is the root, NULL will be returned.
//
//	PARAMETERS:	N/A.
//***************************************************************************
template <class K, class V>
RBNode<K, V>* RBNode<K, V>::getSibling()
{
	if (parent == NULL)
	{
		return NULL;
	}
	if (isOnLeft())
	{
		return parent->right;
	}
	return parent->left;
}

//***************************************************************************
//	NAME: insertKey.
//
//	DESCRIPTION: Method to insert key value pair as a new node into the 
//	             Red-Black tree.  If the given key is already in the tree, 
//	             an appropriate message will be displayed and the method 
//	             will return.  Once the new node has been inserted into the 
//	             tree, the tree will be checked to ensure that none of the 
//	             ordering properties have been violated.  If they have, 
//	             then they will be corrected.  The cursor pointer will be 
//				 set to point to the newly inserted node.
//
//	PARAMETERS: key  : the key to be inserted.
//		        value: the value to be inserted.
//***************************************************************************
template <class K, class V>
void RBTree<K, V>::insertKey(K key, V value)
{
	if (searchKey(key))
	{
		cerr << "No duplicates allowed." << endl;
		return;
	}
	else
	{
		RBNode<K, V>* newNode = new RBNode<K,V>(key, value);
		cursor = newNode;
	
	    RBNode<K, V>* temp    = NULL;
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
	    	
	    fixViolation(newNode);
	}
}

//***************************************************************************
//	NAME: rotateLeft.
//
//	DESCRIPTION: Method to rotate the arrangement of subtree and children to
//	             to the left.  
//
//	PARAMETERS: subtree: pointer to the root of subtree.
//***************************************************************************
template <class K, class V>
void RBTree<K, V>::rotateLeft(RBNode<K, V>*& subtree)
{
	RBNode<K, V>* rightPtr = subtree->right;
    subtree->right = rightPtr->left;

    if (subtree->right != NULL)
    {
        subtree->right->parent = subtree;
    }

    rightPtr->parent = subtree->parent;

    if (subtree->parent == NULL)
    {
        root = rightPtr;
    }
    else if (subtree == subtree->parent->left)
    {
        subtree->parent->left = rightPtr;
    }
    else
    {
        subtree->parent->right = rightPtr;
    }

    rightPtr->left = subtree;
    subtree->parent = rightPtr;
}

//***************************************************************************
//	NAME: rotateRight.
//
//		Method to rotate the arrangement of subtree and children to
//	the right.   
//
//	PARAMETERS:
//		subtree: pointer to the root of subtree.
//***************************************************************************
template <class K, class V>
void RBTree<K, V>::rotateRight(RBNode<K, V>*& subtree)
{
	RBNode<K, V>* leftPtr = subtree->left;

    subtree->left = leftPtr->right;

    if (subtree->left != NULL)
    {
        subtree->left->parent = subtree;
    }

    leftPtr->parent = subtree->parent;

    if (subtree->parent == NULL)
    {
        root = leftPtr;
    }
    else if (subtree == subtree->parent->left)
    {
        subtree->parent->left = leftPtr;
    }
    else
    {
        subtree->parent->right = leftPtr;
    }

    leftPtr->right = subtree;
    subtree->parent = leftPtr;
}

//***************************************************************************
//	NAME: fixViolation.
//
//	DESCRIPTION: Method to correct any violations to the Red-Black tree 
//	             ordering properties.  If any rotations, recolorings, or 
//	             swapping of values is needed, they will occur here.  
//	             Finally the root will be ensured to be colored black.    
//
//	PARAMETERS: subtree: pointer to the root of subtree.
//***************************************************************************
template <class K, class V>
void RBTree<K, V>::fixViolation(RBNode<K, V>* subtree)
{
	RBNode<K, V>* parentPtr = NULL;
    RBNode<K, V>* grandParentPtr = NULL;

    while ((subtree != root) && (subtree->color != BLACK) &&
          (subtree->parent->color == RED))
    {
        parentPtr = subtree->parent;
        grandParentPtr = subtree->parent->parent;

        //  Case: A
        //    Parent of subtree is left child
        //    of Grand-parent of subtree.
        if (parentPtr == grandParentPtr->left)
        {

            RBNode<K, V>* unclePtr = grandParentPtr->right;

            // Case: 1
            //   The uncle of subtree is also red
            //   Only Recoloring required.
            if (unclePtr != NULL && unclePtr->color == RED)
            {
                grandParentPtr->color = RED;
                parentPtr->color = BLACK;
                unclePtr->color = BLACK;
                subtree = grandParentPtr;
            }

            else
            {
                // Case: 2
                //   subtree is right child of its parent
                //   Left-rotation required.
                if (subtree == parentPtr->right)
                {
                    rotateLeft(parentPtr);
                    subtree = parentPtr;
                    parentPtr = subtree->parent;
                }

                // Case: 3
                //   subtree is left child of its parent
                //   Right-rotation required.
                rotateRight(grandParentPtr);
                swap(parentPtr->color, grandParentPtr->color);
                subtree = parentPtr;
            }
        }

        // Case: B
        //   Parent of subtree is right child
        //   of Grand-parent of subtree.
        else
        {
            RBNode<K, V>* unclePtr = grandParentPtr->left;

            //  Case: 1
            //    The uncle of subtree is also red
            //    Only Recoloring required.
            if ((unclePtr != NULL) && (unclePtr->color == RED))
            {
                grandParentPtr->color = RED;
                parentPtr->color = BLACK;
                unclePtr->color = BLACK;
                subtree = grandParentPtr;
            }
            else
            {
                // Case: 2
                //   subtree is left child of its parent
                //   Right-rotation required.
                if (subtree == parentPtr->left)
                {
                    rotateRight(parentPtr);
                    subtree = parentPtr;
                    parentPtr = subtree->parent;
                }

                // Case: 3
                //   subtree is right child of its parent
                //   Left-rotation required.
                rotateLeft(grandParentPtr);
                swap(parentPtr->color, grandParentPtr->color);
                subtree = parentPtr;
            }
        }
    }

    root->color = BLACK;
}	
/* End of fixViolation method */

//***************************************************************************
//	NAME: searchKey.
//
//	DESCRIPTION: Method to search for a given key within the tree.  If the 
//	             key is found, true will be returned.  Otherwise, false 
//				 will be returned.  
//
//	PARAMETERS: key: the key of the node to be found.
//***************************************************************************
template <class K, class V>
bool RBTree<K, V>::searchKey(const K key)
{
	RBNode<K, V>* temp = root;
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

//***************************************************************************
//	NAME: getNode.
//
//	DESCRIPTION: Method to return the address of a node that contains 
//				 the given key.  If the node cannot be found, NULL is 
//				 returned.
//
//	PARAMETERS: key: the key of the node to be found.
//***************************************************************************
template <class K, class V>
RBNode<K, V>* RBTree<K, V>::getNode(const K key)
{
	RBNode<K, V>* temp = root;
	
    while (temp != NULL) 
	{
        if (key < temp->data) 
		{
            if (temp->left == NULL)
            {
                break;
            }
            else
            {
                temp = temp->left;
            }
        }
        else if (key == temp->data) 
        {
            break;
        }
        else 
		{
            if (temp->right == NULL)
            {
                break;
            }
            else
            {
                temp = temp->right;
            }
        }
    }

    return temp;
}

//***************************************************************************
//	NAME: deleteKey.
//
//	DESCRIPTION: Method to delete node by the given key.  If the tree is 
//	             empty, a message will be displayed.  If there is not a 
//	             node with the given key,an appropriate message will be 
//	             displayed.  Otherwise, the position of the node will be 
//				 determined, and the node deleted.
//
//	PARAMETERS: key: the key of the node to be deleted.
//***************************************************************************
template <class K, class V>
void RBTree<K, V>::deleteKey(const K key)
{
	if (root == NULL)
	{
		cerr << "The tree is empty." << endl;
		return;
	}
	
	RBNode<K, V>* nodePtr = getNode(key);

    if (nodePtr->data != key)
    {
        cerr << "There is not a node with value: " << key << endl;
    }
    else
    {
		deleteHelper(nodePtr);
	}
		
	if (root == NULL)
	{
		cursor = NULL;
	}

}

//***************************************************************************
//	NAME: deleteHelper.
//
//	DESCRIPTION: Method to perform actual deletion of node and maintain 
//	             order properties of red-black tree.
//
//	PARAMETERS: delNode: address of the node to be deleted.
//***************************************************************************
template <class K, class V>
void RBTree<K, V>::deleteHelper(RBNode<K, V>*& delNode)
{	
	RBNode<K, V>* replNode = replaceNode(delNode);
    RBNode<K, V>* parent = delNode->parent;
    bool bothBlack = ((replNode == NULL || replNode->color == BLACK) && 
					  (delNode->color == BLACK));

    if (replNode == NULL) 
	{
        // node to be deleted is a leaf.
        if (delNode == root)    // node to be deleted is root.
        {
        	cursor = NULL;
            root = NULL;
        }
        else 
		{
            if (bothBlack) 
			{
                // node to be deleted is leaf, fix double black at delNode.
                fixDoubleBlack(delNode); 
            }
            else 
			{
                if (delNode->getSibling() != NULL)
                {
                    delNode->getSibling()->color = RED;
                }
            }

            // delete delNode from the tree.
            if (delNode->isOnLeft())
            {
                parent->left = NULL;
            }
            else
            {
                parent->right = NULL;
            }
        }
        
        cursor = delNode->parent;	
        delete delNode;
        return;
    }

    if (delNode->left == NULL || delNode->right == NULL)
	{
        // node to be deleted has 1 child.
        if (delNode == root) 
		{
            // node to be deleted is root, swap data replacement.
            delNode->data = replNode->data;
            delNode->left = delNode->right = NULL;
            
            if (delNode->left)
            {
        		cursor = delNode->left;
        	}
        	else if (delNode->right)
        	{
        		cursor = delNode->right;
        	}
        		
            delete replNode;
        }
        else 
		{
            // Detach node to be deleted from tree and move replacement up.
            if (delNode->isOnLeft())
            {
                parent->left = replNode;
            }
            else
            {
                parent->right = replNode;
            }
    
            delete delNode;
            cursor = replNode->parent;
            replNode->parent = parent;
            
            if (bothBlack)
            {
                fixDoubleBlack(replNode);
            }
            else
            {
                replNode->color = BLACK;
            }
        }
        return;
    }

    // node to be deleted has 2 children.
    swapValues(replNode, delNode);   // swap values with successor and recurse.
    deleteHelper(replNode);
}
/* End of deleteHelper method */

//***************************************************************************
//	NAME: fixDoubleBlack.
//
//	DESCRIPTION: Method to correct double black condition which would 
//	             violate the  depth property after deletion has been made.
//
//	PARAMETERS: subtree: pointer to the root of subtree.
//***************************************************************************
template <class K, class V>
void RBTree<K, V>::fixDoubleBlack(RBNode<K, V>* subtree)
{
	if (subtree == root)
	{
        return;
    }

    RBNode<K, V>* sibling = subtree->getSibling();
	RBNode<K, V>* parent = subtree->parent;
	
    if (sibling == NULL)   			// No sibiling, double black pushed up.
    {
        fixDoubleBlack(parent);
    }
    else 
	{
        if (sibling->color == RED)
		{
            parent->color = RED;
            sibling->color = BLACK;
            
            if (sibling->isOnLeft())   // left case.
            {
                rotateRight(parent);
            }
            else 
            {
                rotateLeft(parent);   // right case.
            }
                
            fixDoubleBlack(subtree);
        }
        else 
		{
            // Sibling black.
            if (sibling->hasRedChild()) 
			{
                // at least 1 red children.
                if (sibling->left != NULL && sibling->left->color == RED)
				{
                    if (sibling->isOnLeft()) 	// left left.
					{
                        sibling->left->color = sibling->color;
                        sibling->color = parent->color;
                        rotateRight(parent);
                    }
                    else  	// right left.
					{
                        sibling->left->color = parent->color;
                        rotateRight(sibling);
                        rotateLeft(parent);
                    }
                }
                else 
				{
                    if (sibling->isOnLeft()) 	// left right.
					{
                        sibling->right->color = parent->color;
                        rotateLeft(sibling);
                        rotateRight(parent);
                    }
                    else  	// right right.
					{
                        sibling->right->color = sibling->color;
                        sibling->color = parent->color;
                        rotateLeft(parent);
                    }
                }
                parent->color = BLACK;
            }
            else   // 2 black children.
			{
                sibling->color = RED;
                if (parent->color == BLACK)
                {
                    fixDoubleBlack(parent);
                }
                else
                {
                    parent->color = BLACK;
                }
            }
        }
    }
}
/* End of fixDoubleBlack method */

//***************************************************************************
//	NAME: getSuccessor.
//
//	DESCRIPTION: Method returns pointer to a node that does not have a 
//	             left child in the given subtree  
//
//	PARAMETERS: subtree: pointer to the root of subtree.
//***************************************************************************
template <class K, class V>
RBNode<K, V>* RBTree<K, V>::getSuccessor(RBNode<K, V>* subtree)
{
	RBNode<K, V>* temp = subtree;
    while (temp->left != NULL)
    {
        temp = temp->left;
    }
    return temp;
}

//***************************************************************************
//	NAME: replaceNode.
//
//	DESCRIPTION: Method returns pointer to a node that replaces the 
//	             deleted node in the tree.  
//
//	PARAMETERS: subtree: pointer to the root of subtree.
//***************************************************************************
template <class K, class V>
RBNode<K, V>* RBTree<K, V>::replaceNode(RBNode<K, V>* subtree)
{
    if (subtree->left != NULL && subtree->right != NULL)
    {
        return getSuccessor(subtree->right);
    }

    if (subtree->left == NULL && subtree->right == NULL)
    {
        return NULL;
    }

    // when single child
    if (subtree->left != NULL)
    {
        return subtree->left;
    }
    else
    {
        return subtree->right;
    }
}

//***************************************************************************
//	NAME: swapValues.
//
//	DESCRIPTION: Method to swap key and value of two given nodes.
//
//	PARAMETERS: firstNode: node pointer that will hold secNode's data.
//		        secNode  : node pointer that will hold firstNode's data.
//***************************************************************************
template <class K, class V>
void RBTree<K, V>::swapValues(RBNode<K, V>* firstNode, RBNode<K, V>* secNode)
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
//	NAME: clearTree.
//
//	DESCRIPTION: Method to delete current tree and free up allocated 
//	             storage.  Ends by setting the root and cursor pointers to 
//				 NULL.
//
//	PARAMETERS: N/A.
//***************************************************************************
template <class K, class V>
void RBTree<K, V>::clearTree()
{
	clearHelper(root);
	root   = NULL;
	cursor = NULL;
}

//***************************************************************************
//	NAME: clearHelper.
//
//	DESCRIPTION: Helper method to clear and free all dynamically allocated 
//				 storage allocated by current Red-Black tree.
//
//	PARAMETERS: tree: pointer to the root of the tree.
//***************************************************************************
template <class K, class V>
void RBTree<K, V>::clearHelper(RBNode<K, V>* tree)
{
	if (tree != NULL)
	{
    	clearHelper(tree->left);
		clearHelper(tree->right);
		delete tree;
	}
	tree = NULL;
}

//****************************************************************************
//	NAME: pruneHelper.
//
//	DESCRIPTION: Helper method to traverse the tree and check each node to 
//			     see if it is a leaf.  If it is, the deletion method will be 
//	             called on that node.  Otherwise, the traversal will continue
//	              until the entire tree has been pruned of leaves.  
//
//	PARAMETERS: subtree: pointer to the root of subtree.
//****************************************************************************
template <class K, class V>
void RBTree<K, V>::pruneHelper(RBNode<K, V>* subtree)
{
    if (subtree != NULL)
    {
        pruneHelper(subtree->left);
        if (isLeaf(subtree) && subtree != root)
        {
        	deleteKey(subtree->data);
		}
        pruneHelper(subtree->right);
    }	
}

//***************************************************************************
//	NAME: printTree.
//
//	DESCRIPTION: Method to print the tree in level order.
//
//	PARAMETERS:	N/A.
//***************************************************************************
template <class K, class V>
void RBTree<K, V>::printTree()
{
	if (!root)
	{
        return;
    }
    else
    {
        int ctr = 0;
        while (ctr <= getTreeHeight(root))
        {
            printLevel(ctr);
            ctr++;
            cout << endl << endl;
        }
    }
}

//***************************************************************************
//	NAME: getTreeHeight.
//
//	DESCRIPTION: Calculates the height of the tree.
//
//	PARAMETERS:	subtree: pointer to the root of subtree.
//***************************************************************************
template <class K, class V>
int RBTree<K, V>::getTreeHeight(RBNode<K, V>* subtree)
{
	if (subtree == NULL)
	{
		return 0;
	}
	else
	{
		int leftHeight = getTreeHeight(subtree->left);
		int rightHeight = getTreeHeight(subtree->right);
		
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

//***************************************************************************
//	NAME: printLevel.
//
//	DESCRIPTION: Calculates width to space out nodes and calls DispLevel to 
//				 print nodes on given level.
//
//	PARAMETERS: height: height of tree.
//***************************************************************************
template <class K, class V>
void RBTree<K, V>::printLevel(int height)
{
	RBNode<K, V>* temp = root;
	
	// leftmost point
	int value = pow(2, getTreeHeight(root) - height + 3);
	cout << setw(value - 4) << "";
	dispLevel(temp, height, value);
}

//***************************************************************************
//	NAME: dispLevel.
//
//	DESCRIPTION: Displays the nodes on given level and will display 'x' 
//	             where the pointers are NULL.
//
//	PARAMETERS: subtree : node to be displayed.
//		        level   : current level.
//		        displace: displacement.
//***************************************************************************
template <class K, class V>
void RBTree<K, V>::dispLevel(RBNode<K, V>* subtree, int level, int displace)
{
	int redColorCode   = 79;
	int blackColorCode = 112;
	int disp           = 2 * displace;
	
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
			printNodeAndColor(subtree);
			cout << setw(disp - result) << "";
		}
	}
	
	else
	{
		if (subtree == NULL && level >= 1)
		{
			dispLevel(NULL, level - 1, displace);
			dispLevel(NULL, level - 1, displace);
		}
		else
		{
			dispLevel(subtree->left, level - 1, displace);
			dispLevel(subtree->right, level - 1, displace);
		}
	}
}

//***************************************************************************
//	NAME: inOrder.
//
//	DESCRIPTION: In order print method.
//
//	PARAMETERS: N/A.
//***************************************************************************
template <class K, class V>
void RBTree<K, V>::inOrder() 
{
	cout << "{"; 
	inOrderHelper(root); 
	cout << "}";
}

//***************************************************************************
//	NAME: inOrderHelper.
//
//	DESCRIPTION: Helper method to print the contents of the tree in order.
//
//	PARAMETERS: subtree: pointer to the root of subtree.
//***************************************************************************
template <class K, class V>
void RBTree<K, V>::inOrderHelper(RBNode<K, V>* subtree)
{
    if (subtree != NULL)
    {
        inOrderHelper(subtree->left);
		printNodeAndColor(subtree);
        std::cout << ", ";
        inOrderHelper(subtree->right);
    }
}

//***************************************************************************
//	NAME: preOrder.
//
//	DESCRIPTION: Pre-order print method.
//
//	PARAMETERS: N/A.
//***************************************************************************
template <class K, class V>
void RBTree<K, V>::preOrder() 
{
	cout << "{"; 
	preOrderHelper(root);
	cout << "}"; 
}

//***************************************************************************
//	NAME: preOrderHelper.
//
//	DESCRIPTION: Helper method to print the contents of the tree in pre 
//				 order.
//
//	PARAMETERS: subtree: pointer to the root of subtree.
//***************************************************************************
template <class K, class V>
void RBTree<K, V>::preOrderHelper(RBNode<K, V>* subtree)
{
    if (subtree != NULL)
    {
		printNodeAndColor(subtree);
        std::cout << ", ";
        preOrderHelper(subtree->left);
        preOrderHelper(subtree->right);
    }
}

//***************************************************************************
//	NAME: postOrder.
//
//	DESCRIPTION: Post-order print method.
//
//	PARAMETERS: N/A.
//***************************************************************************
template <class K, class V>
void RBTree<K, V>::postOrder() 
{
	cout << "{";
	postOrderHelper(root);
	cout << "}";
}

//***************************************************************************
//	NAME: postOrderHelper.
//
//	DESCRIPTION: Helper method to print the contents of the tree in post 
//				 order.
//
//	PARAMETERS: subtree: pointer to the root of subtree.
//***************************************************************************
template <class K, class V>
void RBTree<K, V>::postOrderHelper(RBNode<K, V>* subtree)
{
    if (subtree != NULL)
    {
        postOrderHelper(subtree->left);
        postOrderHelper(subtree->right);
		printNodeAndColor(subtree);
        std::cout << ", ";
    }
}

//***************************************************************************
//	NAME: printCursor.
//
//	DESCRIPTION: Method to print the data of the node that the cursor 
//	             pointer references.  If cursor is NULL, then '[]' will 
//				 be displayed.
//
//	PARAMETERS: N/A.
//***************************************************************************
template <class K, class V>
void RBTree<K, V>::printCursor()
{
	if (cursor != NULL)
	{
		printNodeAndColor(cursor);
	}
	else
	{
		cout << "[]" << endl;
	}
}

//***************************************************************************
//	NAME: printRedNode.
//
//	DESCRIPTION: Print the current node with the appropriate highlighted
//				 colored output using the windows handlers.
//
//	PARAMETERS: subtree: pointer to the root of subtree.
//***************************************************************************
template <class K, class V>
void RBTree<K, V>::printNodeAndColor(RBNode<K, V>* subtree) const
{
	int colorCode = 0;
	if (subtree->color == RED)
	{
		colorCode = 79;
	}
	else
	{
		colorCode = 112;
	}
	
	if (subtree == cursor)
	{
		std::cout << " [<";
		
		// Coloring Output
		HANDLE hConsole;
		CONSOLE_SCREEN_BUFFER_INFO myBuffInfo;
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		GetConsoleScreenBufferInfo(hConsole, &myBuffInfo);
		SetConsoleTextAttribute(hConsole, colorCode);	
	
		std::cout << subtree->data;
		std::cout << ", ";
		std::cout << subtree->name;
		
		SetConsoleTextAttribute(hConsole, myBuffInfo.wAttributes);
		std::cout << ">]";
	}
	else
	{
		std::cout << "<";
		
		// Coloring Output
		HANDLE hConsole;
		CONSOLE_SCREEN_BUFFER_INFO myBuffInfo;
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		GetConsoleScreenBufferInfo(hConsole, &myBuffInfo);
		SetConsoleTextAttribute(hConsole, colorCode);	
	
		std::cout << subtree->data;
		std::cout << ", ";
		std::cout << subtree->name;
		
		SetConsoleTextAttribute(hConsole, myBuffInfo.wAttributes);
		std::cout << ">";
	}	
}

template class RBTree<int, string>;
