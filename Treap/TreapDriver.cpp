//****************************************************************************
//	Driver File for Templated Treap
//	Programmed by: Houston Brown
//	Last Compiled Date: 7/17/2023
//
//	Copyright (c) 2022 Houston Brown
//
//	Permission is hereby granted to any person that obtains a copy of this
//	software and associated documentation files (the "Software"), to deal
//	within the Software for free and without restriction.  Including the
//	rights to use, copy, modify, merge, publish, redistribute, sublicense,
//	and/or sell copies of the Software.  Furthermore, to the people who the
//	Software is furnished to do so, subject to the following:
//
//	The above copyright notice and this permission notice shall be included
//	in all copies or substantial portions of the Software.
//
//	The Software is provided "as is", without any warranty of any kind,
//	express or implied, including but not limited to the warranties of 
//	merchantability, fitness for a particular purpose and noninfringement.
//	In not event shall the liability, whether in action of contract, tort or
//	otherwise, arising from, out of or in connection with the Software or the
//	use or other dealings in the Software.
//
//	DISCLAIMER: This program uses system calls that will only work on 
//				Windows operating system.
//****************************************************************************

#include "Treap.h"
#include <limits>
#include <sstream>



void printMenu();

template <class T>
void choose(Treap<T> &myTreap);

template <class T>
T validateInput(T &value);



int main()
{
	srand(time(0));
	
	Treap<int> myTreap;
	printMenu();
	choose(myTreap);
	
	return 0;
}




//****************************************************************************
//		Function to display the available options to the user.
//
//	Parameters:
//		N/A.
//****************************************************************************

void printMenu()
{
	cout << " ________________________________ " << endl;
    cout << "| +Item | Insert Item            |" << endl;
	cout << "| -Item | Delete Item            |" << endl;
    cout << "| ?Item | Search Item            |" << endl;
    cout << "|   R   | Prune Treap            |" << endl;
	cout << "|   I   | Print Items In Order   |" << endl;
	cout << "|   P   | Print Items Pre Order  |" << endl;
	cout << "|   T   | Print Items Post Order |" << endl;
	cout << "|   D   | Destory the Treap      |" << endl;
    cout << "|_______|________________________|" << endl << endl;
    cout << "Please choose an operation to perform on the treap." << endl;
    cout << "Enter Q to quit." << endl;
}




//****************************************************************************
//		This function will prompt and accept the user's choice.  If the
//	choice is invalid, a message will be displayed.  Otherwise, the action
//	will be executed and the updated treap will be displayed along with the
//	menu.  The user will continue to be prompted until they enter the 
//	stopping condition.
//
//	Parameters:
//		myTreap: templated treap.
//****************************************************************************

template <class T>
void choose(Treap<T> &myTreap)
{
	T    key;
	char choice;
	bool hasInserted = false;

	cout << endl << ">> ";
	cin >> choice;
	
	while (choice != 'q' || choice != 'Q')
	{
		switch(choice)
		{
			case '+':
				validateInput(key);
				myTreap.Insert(key);
				hasInserted = true;
				break;

			case '-':
				cin >> key;
				myTreap.Delete(key);
				break;

			case '?':
				validateInput(key);
				if (myTreap.Search(key))
				{
					cout << key << " is in the tree!" << endl;
				}
				else
				{
					cerr << key << " is not in the tree." << endl;
				}
				system("pause");
				break;

			case 'r': case 'R':
				if (hasInserted)
				{
					myTreap.Prune();
				}
				else
				{
					cerr << "\nPlease insert data into the tree." << endl;
					system("pause");					
				}
				break;

			case 'i': case 'I':
				if (hasInserted)
				{
					cout << endl;
					cout << "The contents of the tree in order are: " << endl;
					myTreap.InOrder();
					cout << endl << endl;
				}
				else
				{
					cerr << "The treap is empty." << endl;
				}
				system("pause");
				break;

			case 'p': case 'P':
				if (hasInserted)
				{
					cout << endl;
					cout << "The contents of the tree in pre order are: ";
					cout << endl;
					myTreap.PreOrder();
					cout << endl << endl;
				}
				else
				{
					cerr << "The treap is empty." << endl;
				}
				system("pause");
				break;

			case 't': case 'T':
				if (hasInserted)
				{
					cout << endl;
					cout << "The contents of the tree in post order are: ";
					cout << endl;
					myTreap.PostOrder();
					cout << endl << endl;
				}
				else
				{
					cerr << "The treap is empty." << endl;
				}
				system("pause");
				break;

			case 'd': case 'D':
				myTreap.Clear();
				break;

			case 'q': case 'Q':
				return;

			default:
				cerr << "Invalid option, please try again." << endl;
				system("pause");
				break;
		}
		
		system("cls");
		printMenu();
		cout << endl;
		myTreap.TreePrint();
		cout << ">> ";
		cin >> choice;
	}
}	
/* End of choose function */




//****************************************************************************
//		This function will validate the input from the user.  If the user
//	enters an invalid option for the value, then a message will be displayed
//	and the user will be asked to try again.  Otherwise, the function will
//	return the value to the caller.
//
//	Parameters:
//		value: the value entered by the user.
//****************************************************************************

template <class T>
T validateInput(T &value)
{
	while (true)
	{
		if (cin >> value)
		{
			break;
		}
		else
		{
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			system("cls");
			printMenu();
			cerr << endl << "Please enter a valid item for the treap." << endl;
        	cout << endl << ">> value: ";
		}
	}
	return value;
}
