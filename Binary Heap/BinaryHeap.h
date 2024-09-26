//***************************************************************************
//	Header File for Templated Binary Heap
//	Programmed by: Houston Brown
//	Last Compiled Date: 7/31/2022
//***************************************************************************

#ifndef _BINARYHEAP_H
#define _BINARYHEAP_H

#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;




template <class T>
class BinaryHeap
{
public:
	BinaryHeap(): heap(new T[0]), size(0) {}
	
	void Insert(T key);
	bool Search(T key) const;
	void Delete();
	void Clear() { delete[] heap; heap = NULL; size = 0;}
	void Print() const;

	int GetSize() const { return size; }
	int GetMin() const { return heap[0]; }

private:
	T  *heap;
	int size;
	
	int left(int par) {	return (2 * par + 1); }
	int right(int par) { return (2 * par + 2); }
	int parent(int child) {	return (child - 1) / 2; }

	void HeapifyUp(int in);
	void HeapifyDown(int in);
};

#endif
