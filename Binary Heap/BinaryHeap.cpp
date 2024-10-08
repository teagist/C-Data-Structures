//***************************************************************************
//	Implementation File for Templated Binary Heap
//	Programmed by: Houston Brown
//	Last Compiled Date: 7/31/2022
//***************************************************************************

#include "BinaryHeap.h"



//***************************************************************************
//		Method to perform insertion.  Helper function will be called at the
//	end to maintain the heap order property.
//
//	Parameters:
//		key: the element to be inserted.
//***************************************************************************

template <class T>
void BinaryHeap<T>::Insert(T key)
{
	T *temp = new T[size + 1];
	for (int i = 0; i< size; i++)
	{
		temp[i] = heap[i];
	}
	
	size = size + 1;
	delete[] heap;
	heap = temp;
	heap[size - 1] = key;
	
	HeapifyUp(size - 1);
}




//***************************************************************************
//		Method to perform search for given key.  If the element is found,
//	the method will return true, otherwise it will return false.
//
//	Parameters:
//		key: the element to be searched.
//***************************************************************************

template <class T>
bool BinaryHeap<T>::Search(T key) const
{
	for (int i = 0; i < size; i++)
	{
		if (key == heap[i])
		{
			return true;
		}
	}
	return false;
}




//***************************************************************************
//		Method to delete the value at the front of the array.  Or in other
//	words, the minimum value in the heap.
//
//	Parameters:
//		N/A.
//***************************************************************************

template <class T>
void BinaryHeap<T>::Delete()
{
	T *temp = new T[size - 1];
	for (int i = 1; i< size; i++)
	{
		temp[i-1] = heap[i];
	}
	
	size = size - 1;
	delete[] heap;
	heap = temp;

	HeapifyDown(0);
}
	



//***************************************************************************
//		Method to print the contents of the heap in line.  
//
//	Parameters:
//		N/A.
//***************************************************************************

template <class T>
void BinaryHeap<T>::Print() const
{
	cout << "Heap: ";
	for (int i = 0; i < size; i++)
	{
		cout << heap[i] << " ";
	}
	cout << endl;
}




//***************************************************************************
//		Method to maintain the heap order property.  
//
//	Parameters:
//		in: index of newly inserted value.
//***************************************************************************

template <class T>
void BinaryHeap<T>::HeapifyUp(int in)
{
    if (in && heap[parent(in)] > heap[in])
    {
    	T temp = heap[in];
    	heap[in] = heap[parent(in)];
    	heap[parent(in)] = temp;
    	
    	HeapifyUp(parent(in));
    }
}




//***************************************************************************
//		Method to maintain the heap order property.  
//
//	Parameters:
//		in: index of newly inserted value.
//***************************************************************************

template <class T>
void BinaryHeap<T>::HeapifyDown(int in)
{
	int leftChild = left(in);
	int rightChild = right(in);
	int smallest = in;
	
	if (leftChild < size && heap[leftChild] < heap[in])
	{
		smallest = leftChild;
	}
	if (rightChild < size && heap[rightChild] > heap[smallest])
	{
		smallest = rightChild;
	}
	if (smallest != in)
	{
		int temp = heap[in];
		heap[in] = heap[smallest];
		heap[smallest] = temp;
		HeapifyDown(smallest);
	}
}


template class BinaryHeap<int>;
