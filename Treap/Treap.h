//****************************************************************************
//	Header File for Templated Treap
//	Programmed by: Houston Brown
//	Last Compiled Date: 7/17/2023
//****************************************************************************

#ifndef _TREAP_H
#define _TREAP_H

#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>
#include <cmath>
#include <cstdlib>
using namespace std;



template <class T>
class Treap;


template <class T>
class TreapNode
{
    T          data;
    TreapNode* left;
    TreapNode* right;
    int        priority;

    TreapNode(T key): data(key), left(NULL), right(NULL), 
		      priority(rand() % 100){}

    friend class Treap<T>;
};




template <class T>
class Treap
{
public:
    Treap(): root(NULL){}
	
    void Insert(T key) { return InsertHelper(key, root); }
    bool Search(T key) const {return SearchHelper(key, root); }
    void Delete(T key) { return DeleteHelper(key, root); }
    void Clear();
	
    void Prune() { return PruneHelper(root); }; 
	
    void TreePrint() const;
    void InOrder() const { return InOrderHelper(root); }
    void PreOrder() const { return PreOrderHelper(root); }
    void PostOrder() const { return InOrderHelper(root); }

    Treap(const Treap& myTreap);
    ~Treap();
    Treap& operator=(const Treap& rightTree);
    
private:
    TreapNode<T>* root;
	
    void InsertHelper(T key, TreapNode<T> *&subtree);
    void RotateLeft(TreapNode<T>* &subtree);
    void RotateRight(TreapNode<T>* &subtree);
	
    bool SearchHelper(T key, TreapNode<T> *subtree) const;
    void DeleteHelper(T key, TreapNode<T> *&subtree);
    void ClearHelper(TreapNode<T> *&subtree);
	
    void PruneHelper(TreapNode<T>* subtree);
    bool isLeaf(TreapNode<T>* subtree) const { return(subtree->left == NULL && 
						      subtree->right == NULL); }
	
    // Print Helper Functions
    int GetHeight(TreapNode<T>* subtree) const;
    void PrintLevel(int height) const;
    void DispLevel(TreapNode<T>* subtree, int level, int dist) const;
  
    void InOrderHelper(TreapNode<T>* subtree) const;
    void PreOrderHelper(TreapNode<T>* subtree) const;
    void PostOrderHelper(TreapNode<T>* subtree) const;
	
    void CopyHelper(TreapNode<T>*& root, TreapNode<T>* myRoot);
    void DestroyHelper(TreapNode<T>*& Tree);
};

#endif
