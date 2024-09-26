//****************************************************************************
//	Header File for Templated Linked List
//	Programmed by: Houston Brown
//	Last Compiled Date: 1/15/2024
//****************************************************************************

#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H

#include <iostream>
using namespace std;



template <class T>
class LinkedList;




template <class T>
class Node
{
	T data; 
	Node* next;
	LinkedList<T> subList;
	
	Node():next(NULL){};
	Node(const T key): data(key), next(NULL){};
	Node(const T key, Node* n): data(key), next(n){};

	friend class LinkedList<T>;
};




template <class T>
class LinkedList
{
public:
    LinkedList(): head(NULL), cursor(NULL){}
	
    void Insert(const T key);
	void InsertAtHead(const T key);
    void InsertAtTail(const T key);
    
    void Remove(const T key);
	void RemoveAtHead();	
    void RemoveAtTail();

	bool Search(const T key);	
	void Sort();
	
	void Clear();
	
	void Print() const;
	void PrintCursor() const;
	
	T getHeadValue() const;// { return head->data; }
	T getTailValue() const;
	bool isEmpty() const { return (head == NULL); }

    LinkedList(const LinkedList& myList);                   
    LinkedList& operator=(const LinkedList& myList);        
    ~LinkedList();  

private:
	Node<T>* head;
	Node<T>* cursor;
};

#endif
