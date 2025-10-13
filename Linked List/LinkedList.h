//****************************************************************************
//	Header File for Templated Linked List
//	Programmed by: Houston Brown
//	Last Compiled Date: 10/17/2024
//****************************************************************************

#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H

#include <iostream>
#include <fstream>
#include <windows.h>
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
    LinkedList(): head(NULL), cursor(NULL), size(0){}
	
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
	void PrintInLines() const;
	void PrintToFile() const;
	void PrintCursor() const;
	
	void moveCursorUp();
	void moveCursorDown();
	
	T getHeadValue() const;
	T getTailValue() const;
	int getSize() const { return size; }	
	bool isEmpty() const { return (head == NULL); }

    LinkedList(const LinkedList& myList);                   
    LinkedList& operator=(const LinkedList& myList);        
    ~LinkedList();  

private:
	Node<T>* head;
	Node<T>* cursor;
	int size;
};
#endif
