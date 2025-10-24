//***************************************************************************
//	Header File for Templated Stack
//	Programmed by: Houston Brown
//	Last Compiled Date: 10/24/2025
//***************************************************************************

#ifndef _STACK_H
#define _STACK_H

#include <iostream>
using namespace std;

template<class T>
class Stack;

template<class T>
class StackNode
{
	T data;
	StackNode* next;
	
	StackNode():next(NULL){};
	StackNode(T item):data(item), next(NULL){};
	StackNode(T item, StackNode* ptr):data(item), next(ptr){};

	friend class Stack<T>;
};

template<class T>
class Stack
{
public:
	Stack():head(NULL){}

	void Push(T item);
	void Pop();
	bool IsEmpty() const { return (head == NULL); }
	T Peek() const;
	int Size() const;
		
	StackNode<T>* Search(T item) const;	
	void Print() const;

    Stack(const Stack& myStack);                   
    Stack& operator=(const Stack& myStack);        
    ~Stack();
	
private:
	StackNode<T>* head;	                                 
};
#endif
