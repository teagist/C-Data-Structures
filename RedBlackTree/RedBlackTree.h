//***************************************************************************
//	Header File for Templated Red-Black Tree
//	Programmed by: Houston Brown
//	Last Compiled Date: 10/24/2025
//***************************************************************************
 
#ifndef _RBTree_H
#define _RBTree_H

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>
#include <string>
#include <windows.h>
using namespace std;

template <class K, class V>
class RBTree;

enum NodeColor {RED, BLACK};

template <class K, class V>
class RBNode
{
	K data;
	V name;
	NodeColor color;
	RBNode* left;
	RBNode* right;
	RBNode* parent;

  
	RBNode(K key): data(key), name(""), left(NULL), right(NULL), 
				   parent(NULL), color(RED){}
					  
	RBNode(K key, V value): data(key), name(value), left(NULL), 
							right(NULL), parent(NULL), color(RED){}
	
	
	bool isOnLeft() {  return this == parent->left;  }
	bool hasRedChild() { return (left != NULL && left->color == RED) ||
								(right != NULL && right->color == RED);	}
	RBNode<K, V> *getSibling();
	
	friend class RBTree<K, V>;
};

template <class K, class V>
class RBTree
{
public:
	RBTree(): root(NULL), cursor(NULL){}
	
	void insertKey(K key, V value);
    bool searchKey(const K key); 
    void deleteKey(const K key); 
    void clearTree();
    
    void printTree();
    void inOrder();
    void preOrder();
    void postOrder();
	void printCursor(); 
	void prune() { return pruneHelper(root); };
 
private:
	RBNode<K, V>* root;
	RBNode<K, V>* cursor;
	
	// Insertion Helper Methods.
	void rotateLeft(RBNode<K, V>*& subtree);
	void rotateRight(RBNode<K, V>*& subtree);
	void fixViolation(RBNode<K, V>* subtree); 
	
	// Deletion Helper Methods.
	void deleteHelper(RBNode<K, V>*& delNode);
	RBNode<K, V>* getNode(const K key); 
	void fixDoubleBlack(RBNode<K, V>* subtree); 
	RBNode<K, V>* getSuccessor(RBNode<K, V>* subtree);
	RBNode<K, V>* replaceNode(RBNode<K, V>* subtree);
	void swapValues(RBNode<K, V>* firstNode, RBNode<K, V>* secNode); 
	
	void clearHelper(RBNode<K, V>* tree);
	void pruneHelper(RBNode<K, V>* subtree);
	bool isLeaf(RBNode<K, V>* subtree) const { return (subtree->left == NULL && 
												   subtree->right == NULL); }
	
	// Printing in Level Order Helper Methods.
	int getTreeHeight(RBNode<K, V>* subtree); 
	void printLevel(int treeHeight); 
	void dispLevel(RBNode<K, V>* subtree, int level, int displace);
	
	// Printing in Other Order Helper Methods.
	void inOrderHelper(RBNode<K, V>* subtree);
	void preOrderHelper(RBNode<K, V>* subtree);
	void postOrderHelper(RBNode<K, V>* subtree);
	
	// Colored Output Method.
	void printNodeAndColor(RBNode<K, V>* subtree) const;
};

#endif
