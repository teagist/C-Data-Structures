//****************************************************************************
//	Implementation File for Templated Linked List
//	Programmed by: Houston Brown
//	Last Compiled Date: 1/15/2024
//****************************************************************************

#include "LinkedList.h"




//****************************************************************************
//		Method to insert a node in order of the list.  If memory cannot 
//	be allocated, an appropriate message will be displayed.  Otherwise,
//	the new key will be inserted.  The cursor will be updated to point to 
//	the new node.  
//
//	Parameters:
//		key: the value to be inserted into the list.
//****************************************************************************

template <class T>
void LinkedList<T>::Insert(const T key)
{	
	Node<T> *curr = head;
	if(head == NULL || head->data >= key)
	{
		try
		{
			curr = new Node<T>(key, head);
			head = curr;
			cursor = curr;
		}
		catch (bad_alloc& ex)
		{
			cerr << "Failed to insert " << key << " into the List." << endl;
		}
	}
	
	else 
	{
		while(curr->next != NULL && curr->next->data < key)                                                       
			curr = curr->next;
		
		try
		{
			curr->next = new Node<T>(key, curr->next);
			cursor = curr->next;
		}
		catch (bad_alloc& ex)
		{
			cerr << "Failed to insert " << key << " into the List." << endl;			
		}
	}
}




//****************************************************************************
//		Method to insert a node at the front of the list.  If memory cannot 
//	be allocated, an appropriate message will be displayed.  Otherwise,
//	the new key will be inserted.  The cursor will be updated to point to 
//	the new node.  
//
//	Parameters:
//		key: the value to be inserted into the list.
//****************************************************************************

template<class T>
void LinkedList<T>::InsertAtHead(const T key)
{
	try
	{
		head = new Node<T>(key, head);
		cursor = head;
	}
	catch (bad_alloc& ex)
	{
		cerr << "Failed to insert " << key << " into the List." << endl;
	}	
}




//****************************************************************************
//		Method to insert a node at the end of the list.  If memory cannot 
//	be allocated, an appropriate message will be displayed.  Otherwise,
//	the new key will be inserted at the end of the list.  The cursor will
//	be updated to point to the new node.  
//
//	Parameters:
//		key: the value to be inserted into the list.
//****************************************************************************

template <class T>
void LinkedList<T>::InsertAtTail(const T key)
{
	try
	{
		Node<T>* tail = new Node<T>(key, NULL);
		cursor = tail;
		
		if (head != NULL)
		{
			Node<T>* temp = head;
			while (temp->next != NULL)
				temp = temp->next;

			temp->next = tail;
		}
		else
		{
			head = tail;
		}
	}
	catch (bad_alloc& ex)
	{
		cerr << "Failed to insert " << key << " into the List." << endl;
	}
}




//****************************************************************************
//		Method to delete a node from the list.  If the list is empty, this
//	method will return.  Otherwise, the list will be searched for the given
//	key.  Once it has been found, it will be deleted and the cursor set
//	to the node before it.  If key cannot be found, an appropriate message 
//	will be displayed, and this method will return.  
//
//	Parameters:
//		key: the value to be deleted from the list.  
//****************************************************************************

template <class T>
void LinkedList<T>::Remove(const T key)
{
    Node<T> *curr = head;
    Node<T> *prev = NULL;

	if (head == NULL)
	{
		cerr << "The list is empty.  Please try again." << endl;
		return;
	}

    while(curr != NULL && curr->data != key)
	{
		prev = curr;
		cursor = prev;
		curr = curr->next;
	}
    
    if(curr == NULL)
	{
		cerr << key << " is not in the List.  Please try again." << endl;
		return;
	}

	if (prev == NULL)
    {
    	head = curr->next;
    }
    else
    {
    	prev->next = curr->next;
    	cursor = prev;
    }
    
    delete curr;
}




//****************************************************************************
//		Method to remove the node at the front of the list.  The cursor will
//	point to the new head of the list.  
//
//	Parameters:
//		N/A.
//****************************************************************************

template<class T>		
void LinkedList<T>::RemoveAtHead()
{
	Node<T> *curr = head;  
	
	if (head == NULL)
    {
		//cerr << "The list is empty.  Please try again." << endl;
        return;	
	}
	
	head = head->next;
	delete curr;
	
	if (head != NULL)
	{
		cursor = head;
	}
	else
	{
		cursor = NULL;
	}
}




//****************************************************************************
//		Method will remove the node at the end of the list.  The cursor
//	will point to the new tail of the list.
//
//	Parameters:
//		N/A.
//****************************************************************************

template <class T>
void LinkedList<T>::RemoveAtTail()
{
    Node<T> *curr = head;
    Node<T> *prev = NULL;
    
    if (head == NULL)
    {
		cerr << "The list is empty.  Please try again." << endl;
		return;    	
	}

    while(curr->next != NULL)
    {
        prev = curr;
        curr = curr->next;
    }
    
	if (prev == NULL)
    {
    	delete curr;
    	head = NULL;
    }
    
    else
    {    
    	delete curr;
    	prev->next = NULL;
		cursor = prev;    
	}
}




//****************************************************************************
//		Method to search the list for a given key.  If the key is found, a
//	message will be displayed and true returned.  Otherwise, an appropriate
//	message will be displayed, and false will be returned.  If the value is
//	found, the cursor will point to the node containing the key.  Otherwise
//	the cursor will point to the head.
//
//	Parameters:
//		key: the value to be searched for.
//****************************************************************************

template<class T>
bool LinkedList<T>::Search(const T key)
{
	Node<T> *curr = head; 
	bool success  = false;

	if (curr == NULL)
	{
		return false;
	}
		
	while(curr != NULL)
	{
		if(curr->data == key)
		{
			success = true;
			//cout << key << " is in the list!" << endl;
			cursor = curr;
		}
		curr = curr->next;
	}

	if(success == false)
	{
		//cout << key << " is not in the list" << endl;
		
		if (head)
		{
			cursor = head;
		}
			
        return false;
	}

    return true;
}




//****************************************************************************
//		Method will sort the contents of the Linked List using a Bubble Sort
//	algorithm.  At the end the cursor will point to the head of the list.
//
//	Parameters:
//		N/A.
//****************************************************************************

template <class T>
void LinkedList<T>::Sort()
{
	Node<T>* curr = head;
	Node<T>* index = NULL;
	T temp;
	
	if (head == NULL)
	{
		return;
	}
		
	while (curr != NULL)
	{
		index = curr->next;
		
		while (index != NULL)
		{
			if (curr->data > index->data)
			{
				temp = curr->data;
				curr->data = index->data;
				index->data = temp;
			}
			index = index->next;
		}
		curr = curr->next;
	}
	
	if (head)
	{
		cursor = head;
	}
}




//****************************************************************************
//		Clear method calls the linked list destructor  .
//
//	Parameters:
//		N/A.
//****************************************************************************

template<class T>
void LinkedList<T>::Clear()
{
	while (head != NULL)
	{
		Node<T>* temp = head;
		head = head->next;
		delete temp;
	}
	
	cursor = NULL;
	head   = NULL;
}




//****************************************************************************
//		Method to print the contents of the list, within square brackets,
//	and on one line.  Method will also print the square brackets around the
//	cursor value.  
//
//	Parameters:
//		N/A.
//****************************************************************************

template<class T>
void LinkedList<T>::Print() const
{
	Node<T> *temp = head;
	
	if(head == NULL)
	{
		return;
	}

	cout << "[";
	while(temp != NULL)
	{
		if (temp->next == NULL)
		{
			if (temp == cursor)
			{
				cout << "[" << temp->data << "]";
			}
			else
			{
				cout << temp->data;
			}
		}
		else
		{
			if (temp == cursor)
			{
				cout << "[" << temp->data << "], ";
			}
			else
			{
				cout << temp->data << ", ";
			}
		}
			
		temp = temp->next;
	}
	cout << "]";
}




//****************************************************************************
//		Method to print the data of the node that the cursor pointer 
//	references.  If cursor is NULL, then '[]' will be displayed.
//
//	Parameters:
//		N/A.
//****************************************************************************

template <class T>
void LinkedList<T>::PrintCursor() const
{
	if (cursor)
	{
		cout << "[" << cursor->data << "]" << endl;
	}
	else
	{
		cout << "[]" << endl;
	}
}



//****************************************************************************
//		Function to return the first value, or head, of the list.  
//
//	Parameters:
//		N/A.
//****************************************************************************
template <class T>
T LinkedList<T>::getHeadValue() const
{
	if (head)
	{
		return head->data;
	}
	else
	{
		return (T)NULL;
	}
}




//****************************************************************************
//		Function to return the last value, or tail, of the list.  
//
//	Parameters:
//		N/A.
//****************************************************************************

template <class T>
T LinkedList<T>::getTailValue() const
{
	Node<T>* temp = head; 
	
	while (temp != NULL)
	{
		if (temp->next == NULL)
		{
			return temp->data;
		}
		temp = temp->next;
	}
}
    



//****************************************************************************
//		Copy Constructor.
//****************************************************************************

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T>& myList)
{
	if (!myList.head)
	{
		head = NULL; 
		return;
	}
		
	head = new Node<T>(myList.head->data);

	Node<T>* oldtemp = myList.head->next;
	Node<T>* newtemp = head;
	
	while (oldtemp)
	{
		newtemp->next = new Node<T>(oldtemp->data);
		newtemp=newtemp->next;
		oldtemp=oldtemp->next;		
	}
}




//****************************************************************************
//		Assignment Operator.
//****************************************************************************

template<class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& myList)
{
	if (myList.head == head)
	{
		return *this;
	}
		
	this->~LinkedList();

	if (!myList.head)
	{ 
		head = NULL; 
		return *this;
	}
	
	head = new Node<T>(myList.head->data);

	Node<T> *oldtemp = myList.head->next;
	Node<T> *newtemp = head;
	
	while (oldtemp)
	{
		newtemp->next = new Node<T>(oldtemp->data);
		newtemp=newtemp->next;
		oldtemp=oldtemp->next;		
	}
	return *this;
}




//****************************************************************************
//		Destructor.
//****************************************************************************

template<class T>
LinkedList<T>::~LinkedList()
{
    while(head)
	{   
        Node<T>* temp = head->next;
        delete head;
        head = temp;
    }
    head = NULL;   
}




template class LinkedList<int>;
template class LinkedList<float>;
template class LinkedList<double>;
template class LinkedList<string>;
template class LinkedList<char>;
template class LinkedList<bool>;
