//***************************************************************************
//	Header File for Templated Red-Black Tree
//	Programmed by: Houston Brown
//	Last Compiled Date: 7/31/2022
//***************************************************************************
 
#ifndef _RBTree_H
#define _RBTree_H

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>
#include <string>
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
	
	
	bool IsOnLeft() {  return this == parent->left;  }
	bool HasRedChild() { return (left != NULL && left->color == RED) ||
								(right != NULL && right->color == RED);	}
	RBNode<K, V> *GetSibling();
	
	friend class RBTree<K, V>;
};



template <class K, class V>
class RBTree
{
public:
	RBTree(): root(NULL), cursor(NULL){}
	
	void Insert(K key, V value);
    bool Search(const K key); 
    void Delete(const K key); 
    void ClearTree();
    
    void PrintTree();
    void InOrder();
    void PreOrder();
    void PostOrder();
	void PrintCursor(); 
	void Prune() { return PruneHelper(root); };
 
private:
	RBNode<K, V>* root;
	RBNode<K, V>* cursor;
	
	// Insertion Helper Methods
	void RotateLeft(RBNode<K, V>*& subtree);
	void RotateRight(RBNode<K, V>*& subtree);
	void FixViolation(RBNode<K, V>* subtree); 
	
	// Deletion Helper Methods
	void Delete(RBNode<K, V>*& delNode);
	RBNode<K, V>* GetNode(const K key); 
	void FixDoubleBlack(RBNode<K, V>* subtree); 
	RBNode<K, V>* Successor(RBNode<K, V>* subtree);
	RBNode<K, V>* Replace(RBNode<K, V>* subtree);
	void SwapValues(RBNode<K, V>* firstNode, RBNode<K, V>* secNode); 
	
	void ClearHelper(RBNode<K, V>* tree);
	void PruneHelper(RBNode<K, V>* subtree);
	bool isLeaf(RBNode<K, V>* subtree) const { return (subtree->left == NULL && 
												   subtree->right == NULL); }
	
	// Printing in Level Order Helper Methods
	int TreeHeight(RBNode<K, V>* subtree); 
	void PrintLevel(int treeHeight); 
	void DispLevel(RBNode<K, V>* subtree, int level, int displace);
	
	// Printing in Other Order Helper Methods
	void InOrder(RBNode<K, V>* subtree);
	void PreOrder(RBNode<K, V>* subtree);
	void PostOrder(RBNode<K, V>* subtree);
};

#endif
