//****************************************************************************
//	Header File for Templated Binary Search Tree
//	Programmed by: Houston Brown
//	Last Compiled Date: 7/17/2023
//****************************************************************************

#ifndef _BST_H
#define _BST_H

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <cmath>
using namespace std;



template<class T>
class BST;



template <class T>
class BNode
{
    T data;
    BNode* left;
    BNode* right;

    BNode(T newData): data(newData), left(NULL), right(NULL){};

    friend class BST<T>;
};



template <class T>
class BST
{
public:
    BST(): root(NULL){};                 

    void Insert(const T key) { return InsertHelper(key, root); }
	bool Search(const T key);
	void Delete(const T key);

	void PrintTree() const;
    void InOrder() const;
    void PreOrder() const;
    void PostOrder() const;

    void PrintCursor() const;
    void Prune() { return PruneHelper(root); };

    BST(const BST& myBST);
    ~BST();
    BST& operator=(const BST& rightTree);

private:
    BNode<T>* root;
    BNode<T>* cursor;

    void InsertHelper(const T key, BNode<T>*& subtree);
	BNode<T>* DeleteHelper(const T key, BNode<T>*& subtree); 
	
	BNode<T>* GetMin(BNode<T>* subtree) const;  
	BNode<T>* GetParent(BNode<T>* subtree) const;
	void PruneHelper(BNode<T>* subtree);
	bool isLeaf(BNode<T>* subtree) const { return (subtree->left == NULL && 
												   subtree->right == NULL); }

	// Printing in Level Order Helper Methods
	int TreeHeight(BNode<T>* subtree) const;
	void PrintLevel(int height) const;
	void DispLevel(BNode<T>* subtree, int level, int displace) const;
	
	// Printing in Other Order Helper Methods	
    void PreOrderHelper(const BNode<T>* subtree) const; 
    void InOrderHelper(const BNode<T>* subtree) const;
    void PostOrderHelper(const BNode<T>* subtree) const;

    void CopyHelper(BNode<T>*& root, BNode<T>* myRoot);
    void DestroyHelper(BNode<T>*& Tree);
};


#endif
