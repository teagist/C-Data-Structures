//****************************************************************************
//	Driver File for Templated Linked List
//	Programmed by: Houston Brown
//	Last Compiled Date: 1/15/2024
//
//	Copyright (c) 2024 Houston Brown
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

#include "LinkedList.h"
#include "TestLinkedList.cpp"
#include <limits>
#include <sstream>


void getManualOrAuto();

void printMenu();

template <class T> 
void choose(LinkedList<T>& myList);

template <class T>
T validateInput(T &value);



int main()
{
	getManualOrAuto();

	return 0;
}





//****************************************************************************
//		Function to prompt the user to select automatic test or manaul.
//
//	Parameters:
//		N/A.
//****************************************************************************

void getManualOrAuto()
{
	char userEntry;
	
	std::cout << "Automatic testing? (Y/N)" << std::endl;
	std::cout << ">> ";
	
    while (true)
    {
        if (std::cin >> userEntry)
        {
            // Convert the input to uppercase
            userEntry = std::toupper(userEntry);

            // Check if it's a valid input
            if (userEntry == 'Y')
            {
            	TestLinkedList<int> theTest;
                theTest.runTests();
                return;
            }
            else if (userEntry == 'N')
            {
                LinkedList<int> myList;
                printMenu();
                choose(myList);
                return;
            }
            else
            {
            	std::cout << std::endl;
            	std::cout << "Invalid entry, please try again." << std::endl;
            }
        }
        else
        {
            // Clear input buffer to handle invalid input
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << std::endl;
            std::cout << "Invalid entry, please try again." << std::endl;
        }
    }
}




//****************************************************************************
//		Function to display the available options to the user.
//
//	Parameters:
//		N/A.
//****************************************************************************

void printMenu()
{
	cout << " ___________________________________" << endl;
	cout << "| +Key  | Insert Item In Order      |" << endl;
	cout << "| *Key  | Insert Item at the Front  |" << endl;
	cout << "| #Key  | Insert Item at the End    |" << endl;
	cout << "| -Key  | Remove Item               |" << endl;
	cout << "| ~     | Remove Item at the Front  |" << endl;
	cout << "| `     | Remove Item at the End    |" << endl;
	cout << "| ?Key  | Search Item               |" << endl;
	cout << "| S     | Sort the List             |" << endl;
	cout << "| @     | Print Cursor Value        |" << endl;
	cout << "| D     | Delete the List           |" << endl;
	cout << "|_______|___________________________|" << endl << endl;
    cout << "Please choose an operation to perform on the list." << endl;
    cout << "Enter Q to quit." << endl;	
}




//****************************************************************************
//		This function will prompt and accept the user's choice.  If the
//	choice is invalid, a message will be displayed.  Otherwise, the action
//	will be executed and the updated list will be displayed along with the
//	menu.  The user will continue to be prompted until they enter the 
//	stopping condition.
//
//	Parameters:
//		myList: a templated Linked List.
//****************************************************************************

template <class T> 
void choose(LinkedList<T>& myList)
{
	char   choice = 'A';
	bool   hasInserted = false;
	T      key;
	
	cout << "\nLinked List>> ";
	cin >> choice;
	
	while (choice != 'q' || choice != 'Q')
	{
		switch(choice)
		{
			case '+':
				validateInput(key);
				myList.Insert(key);
				
				hasInserted = true;
				break;
				
			case '*':
				validateInput(key);
				myList.InsertAtHead(key);
				
				hasInserted = true;
				break;
				
			case '#':
				validateInput(key);
				myList.InsertAtTail(key);
				
				hasInserted = true;
				break;

			case '-':
				if (hasInserted)
				{
					validateInput(key);
					myList.Remove(key);
				}
				else
				{
					cerr << "\nPlease insert data into the list." << endl;
					system("pause");					
				}
				break;
				
			case '~':
				if (hasInserted)
					myList.RemoveAtHead();
				else
				{
					cerr << "\nPlease insert data into the list." << endl;
					system("pause");					
				}
				break;
				
				
				case '`':
				if (hasInserted)
					myList.RemoveAtTail();
				else
				{
					cerr << "\nPlease insert data into the list." << endl;
					system("pause");					
				}
				break;

			case '?':
				if (hasInserted)
				{
					validateInput(key);
					myList.Search(key);
					system("pause");
				}
				else
				{
					cerr << "\nPlease insert data into the list." << endl;
					system("pause");					
				}
				break;
				
			case 's': case 'S':
				if (hasInserted)
					myList.Sort();
				else
				{
					cerr << "\nPlease insert data into the list." << endl;
					system("pause");
				}
				break;

			case '@':
				if (hasInserted)
				{
					myList.PrintCursor();
					cout << endl;
					system("pause");
				}
				else
				{
					cerr << "\nPlease insert data into the list." << endl;
					system("pause");					
				}
				break;

			case 'd': case 'D':
				myList.~LinkedList();
				hasInserted = false;
				break;  

			case 'q': case 'Q':
				exit(1);

			default:
				cerr << "Invalid option, please try again." << endl;
				system("pause");
				break;
		}
		system("cls");
		printMenu();
		cout << endl;
		
		if (hasInserted)
		{
			myList.Print();
			cout << endl << endl;
		}
			
		cout << "Linked List>> ";
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
			break;
		else
		{
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			
			system("cls");
			printMenu();
			cerr << endl << "Please enter a valid item for the list." << endl;
        	cout << endl << ">> value: ";
		}
	}
	return value;
}
