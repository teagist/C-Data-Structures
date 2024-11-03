//***************************************************************************
//	Implementation File for Templated Queue
//	Programmed by: Houston Brown
//	Last Compiled Date: 11/3/2024
//***************************************************************************

#include "Queue.h"




//***************************************************************************
//		Method to insert a new item at the end of the queue.  If the new 
//	node cannot be created due to a bad allocation error, a message will
//	be displayed.   
//
//	Parameters:
//		N/A.
//***************************************************************************

template<class T>
void Queue<T>::Enqueue(T item)
{
	try
	{
		QNode<T>* tail = new QNode<T>(item, NULL);
		if (head != NULL)
		{
			QNode<T>* temp = head;
			while (temp->next != NULL)
			{
				temp = temp->next;
			}
			temp->next = tail;
		}
		else
		{
			head = tail;
		}
	}
	catch (bad_alloc & ex)
	{
		cerr << "Failed to enqueue " << item << " into the Queue." << endl;
	}
}




//***************************************************************************
//		Method to remove the item at the front of the queue.   
//
//	Parameters:
//		N/A.
//***************************************************************************

template<class T>
void Queue<T>::Dequeue()
{
	if (head != NULL)
	{
		QNode<T>* temp = head;
		head = head->next;
		delete[] temp;
	}
}




//***************************************************************************
//		Method to return the item at the front of the queue.    
//
//	Parameters:
//		N/A.
//***************************************************************************

template<class T>
T Queue<T>::Peek() const
{
	if (head != NULL)
	{
		return head->data;
	}
	else
	{
		return T(NULL);
	}
}



//***************************************************************************
//		Method to return the size of the queue.      
//
//	Parameters:
//		N/A.
//***************************************************************************

template<class T>
int Queue<T>::Size() const
{
	int size = 0;
	
	if (head == NULL)
	{
		return 0;
	}
		
	else
	{
		QNode<T>* temp = head;
		while (temp != NULL)
		{
			temp = temp->next;
			size = size + 1;
		}
		return size;
	}
}




//***************************************************************************
//		Method to search the queue for a given element and return a 
//	pointer to the item if it is found.  Otherwise it will return NULL.    
//
//	Parameters:
//		item: the element to be searched for.
//***************************************************************************

template<class T>
QNode<T>* Queue<T>::Search(T item) const
{
	bool success = false;
	QNode<T>* temp = head;
	
	if (temp == NULL)
	{
		return NULL;
	}
		
	while(temp != NULL)
	{
		if(temp->data == item)
		{
			success = true;
			cout << item << " was found." << endl;
		}
		temp = temp -> next;
	}

	if(success == false)
	{
		cerr << item << " was not found." << endl;
        return NULL;
	}

    return temp;
}




//***************************************************************************
//		Method that will print the contents of the queue.  The front 
//	element will be enclosed in square brackets to denote the start of the
//	queue.     
//
//	Parameters:
//		N/A.
//***************************************************************************

template<class T>
void Queue<T>::Print() const
{
	if (head == NULL)
	{
		return;
	}
		
	else
	{
		QNode<T>* temp = head;
		cout << "-------------" << endl;
		cout << "[" << temp->data << "]," << endl;
		temp = temp->next;
		
		while (temp != NULL)
		{
			cout << temp->data << "," << endl;	
        	temp= temp->next;
		}
		cout << "-------------" << endl;
	}
}





//***************************************************************************
//		Destructor.
//***************************************************************************
template<class T>
Queue<T>::~Queue()
{
    while(head != NULL)
	{
        QNode<T>* temp = head->next;
        delete head;
        head = temp;
    }
    head = NULL;   
}





template class Queue<int>;
