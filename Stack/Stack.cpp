//***************************************************************************
//	Implementation File for Templated Stack
//	Programmed by: Houston Brown
//	Last Compiled Date: 5/3/2022
//***************************************************************************

#include "Stack.h"




//***************************************************************************
//	    Stack method will attempt to push the new item onto the stack.  If
//	a bad memory allocation exception is detected, then an appropritate
//	message will be displayed to the user, and the item will not be pushed.
//
//	Parameters:
//		item: the element to be pushed.
//***************************************************************************

template<class T>
void Stack<T>::Push(T item)
{
    try
    {
	head = new StackNode<T>(item, head);
    }
    catch (bad_alloc & ex)
    {
	cerr << "Failed to push " << item << " onto the stack." << endl;
    }
}




//***************************************************************************
//		Stack method will pop the top most item off the stack, unless the 
//	stack is empty.  If the stack is empty, then a message will be displayed
//	to the user.  
//
//	Parameters:
//		N/A
//***************************************************************************

template<class T>		
void Stack<T>::Pop()
{
	if (head == NULL)
		cerr << "The stack is empty." << endl;	

	else
    {
		StackNode<T>* ptr = head;
		head = head->next;
		delete[] ptr;
	}  
}




//***************************************************************************
//		Stack method will return the top most value off the stack.  If the
//	stack is empty, then an appropriate message will be displayed to the 
//	user.    
//
//	Parameters:
//		N/A
//***************************************************************************

template<class T>
T Stack<T>::Peek()const
{
    StackNode<T>* temp = head;	
    if(head == NULL)
    {
        cerr << "The stack is empty." <<endl;
		return T(NULL);
	}
	
    else
        return temp->data;
}




//***************************************************************************
//		Stack method to return the size of the stack.     
//
//	Parameters:
//		N/A
//***************************************************************************

template<class T>
int Stack<T>::Size() const
{
	int size = 0;
	
	if (head == NULL)
		return 0;
		
	else
	{
		StackNode<T>* temp = head;
		while (temp != NULL)
		{
			temp = temp->next;
			size = size + 1;
		}
		return size;
	}
}




//***************************************************************************
//		Stack method that will return NULL if the stack is empty, or if the
//	item is not found, after displaying a message to the user.  If the item 
//	is found, then a message will be displayed and the pointer to the 
//	location returned.    
//
//	Parameters:
//		item: the element to be searched for
//***************************************************************************

template<class T>
StackNode<T>* Stack<T>::Search(T item)const
{
	bool success = false;
	StackNode<T>* temp = head;
	
	if (temp == NULL)
		return NULL;
		
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
//		Stack method that will print the contents of the stack.  The top 
//	element will be enclosed in square brackets to denote the top.     
//
//	Parameters:
//		N/A
//***************************************************************************

template<class T>
void Stack<T>::Print()const
{
	if (head == NULL)
		return;
		
	else
	{
		StackNode<T>* temp = head;
		cout << "-------------" << endl;
		cout << "[" << temp->data << "]" << endl;
		temp = temp->next;
		
		while (temp != NULL)
		{
			cout << temp->data << endl;	
        	temp= temp->next;
		}
		cout << "-------------" << endl;
	}
}




//***************************************************************************
//		Copy Constructor
//***************************************************************************

template<class T>
Stack<T>::Stack(const Stack<T>& myStack)
{
	if (!myStack.head)
		head = NULL; return;

	head = new StackNode<T>(myStack.head->data);

	StackNode<T> *oldtemp = myStack.head->next;
	StackNode<T> *newtemp = head;
	while (oldtemp)
	{
		newtemp->next = new StackNode<T>(oldtemp->data);
		newtemp=newtemp->next;
		oldtemp=oldtemp->next;		
	}
}




//***************************************************************************
//		Assignment Operator
//***************************************************************************

template<class T>
Stack<T>& Stack<T>::operator=(const Stack<T>& myStack)
{
	if (myStack.head == head)
		return *this;
	this->~Stack();

	if (!myStack.head)
	{ 
		head = NULL; 
		return *this;
	}
	head = new StackNode<T>(myStack.head->data);

	StackNode<T> *oldtemp = myStack.head->next;
	StackNode<T> *newtemp = head;
	
	while (oldtemp)
	{
		newtemp->next = new StackNode<T>(oldtemp->data);
		newtemp=newtemp->next;
		oldtemp=oldtemp->next;		
	}
	return *this;
}




//***************************************************************************
//		Destructor
//***************************************************************************

template<class T>
Stack<T>::~Stack()
{
    while(head != NULL)
	{
        StackNode<T>* temp = head->next;
        delete head;
        head = temp;
    }
    head = NULL;   
}





template class Stack<int>;
template class Stack<double>;
template class Stack<float>;
template class Stack<char>;
template class Stack<bool>;
template class Stack<string>;
