//****************************************************************************
//	Header File for Templated AVL Tree
//	Programmed by: Houston Brown
//	Last Compiled Date: 6/25/2023
//****************************************************************************

#ifndef _AVLTREE_H
#define _AVLTREE_H

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <cmath>
using namespace std;

template<class T>
class AvlTree;

template <class T>
class AvlNode
{
	T data;
	AvlNode* left;
	AvlNode* right;
	int height;
	
	AvlNode(T newData): data(newData), left(NULL), right(NULL), height(0){};

    friend class AvlTree<T>;
};

template <class T>
class AvlTree
{
public:
    AvlTree(): root(NULL){};                 

    void Insert(const T key) { return InsertHelper(key, root); }
	bool Search(const T key);
	void Delete(const T key);

	void PrintTree() const;
    void InOrder() const;
    void PreOrder() const;
    void PostOrder() const;

    void PrintCursor() const;
    void Prune() { return PruneHelper(root); };

    AvlTree(const AvlTree& myAvl);
    ~AvlTree();
    AvlTree& operator=(const AvlTree& rightTree);

private:
    AvlNode<T>* root;
    AvlNode<T>* cursor;

    void InsertHelper(const T key, AvlNode<T>*& subtree);
    
    void BalanceTree(AvlNode<T>*& subtree);
    
	void RotateLeft(AvlNode<T>*& subtree);
    void DoubleRotateLeft(AvlNode<T>*& subtree);
    
    void RotateRight(AvlNode<T>*& subtree);
    void DoubleRotateRight(AvlNode<T>*& subtree);
    
	void DeleteHelper(const T key, AvlNode<T>*& subtree);   
	AvlNode<T>* GetMin(AvlNode<T>* subtree) const;
	
	void PruneHelper(AvlNode<T>* subtree);
	bool isLeaf(AvlNode<T>* subtree) const { return (subtree->left == NULL && 
												   subtree->right == NULL); }	

	// Printing in Level Order Helper Methods.	
	int GetHeight(AvlNode<T>* subtree) const;
	void PrintLevel(int height) const;
	void DispLevel(AvlNode<T>* subtree, int level, int displace) const;
	
	// Printing in Other Order Helper Methods.	
    void PreOrderHelper(const AvlNode<T>* subtree) const; 
    void InOrderHelper(const AvlNode<T>* subtree) const;
    void PostOrderHelper(const AvlNode<T>* subtree) const;

    void CopyHelper(AvlNode<T>*& root, AvlNode<T>* myRoot);
    void DestroyHelper(AvlNode<T>*& Tree);
};

#endif
