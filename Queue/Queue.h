//***************************************************************************
//	Header File for Templated Queue
//	Programmed by: Houston Brown
//	Last Compiled Date: 10/12/2024
//***************************************************************************

#ifndef _QUEUE_H
#define _QUEUE_H

#include <iostream>
using namespace std;

template<class T>
class Queue;



template<class T>
class QNode
{
	T data;
	QNode* next;
	
	QNode():next(NULL){};
	QNode(T item):data(item), next(NULL){};
	QNode(T item, QNode* ptr):data(item), next(ptr){};

	friend class Queue<T>;
};



template<class T>
class Queue
{
public:
	Queue():head(NULL){}
	
	void Enqueue(T item);
	void Dequeue();
	T Peek() const;
	bool IsEmpty() const { return (head == NULL); }
	int Size() const;
	
	QNode<T>* Search(T item) const;	
	void Print() const;
	
	~Queue();

private:	                                  
	QNode<T>* head;
};
#endifs
