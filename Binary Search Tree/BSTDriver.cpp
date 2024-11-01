//****************************************************************************
//	Driver File for Templated Binary Search Tree
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

#include "BST.h"
#include <limits>
#include <sstream>



void printMenu();

template <class T> 
void choose(BST<T>& myTree);

template <class T>
T validateInput(T &value);



int main()
{
	BST<int> myTree;
	printMenu();
	choose(myTree);
	
	return 0;
}




//****************************************************************************
//	NAME: printMenu.
//
//	DESCRIPTION: Function to display the available options to the user.
//
//	PARAMETERS: N/A.
//****************************************************************************
void printMenu()
{
	cout << " ________________________________ " << endl;
	cout << "| +Key  | Insert Item            |" << endl;
	cout << "| -Key  | Remove Item            |" << endl;
	cout << "| ?Key  | Search Item            |" << endl;
	cout << "| R     | Prune Tree             |" << endl;
	cout << "| I     | Print Items In Order   |" << endl;
	cout << "| P     | Print Items Pre Order  |" << endl;
	cout << "| T     | Print Items Post Order |" << endl;
	cout << "| @     | Print Cursor Value     |" << endl;
	cout << "| D     | Delete the Tree        |" << endl;
	cout << "|_______|________________________|" << endl << endl;
    cout << "Please choose an operation to perform on the tree." << endl;
    cout << "Enter Q to quit." << endl;	
}


//****************************************************************************
//	NAME: choose.
//
//	DESCRIPTION: This function will prompt and accept the user's choice.  
//	             If the choice is invalid, a message will be displayed.  
//	             Otherwise, the action will be executed and the updated 
//	             tree will be displayed along with the menu.  The user will 
//	             continue to be prompted until they enter the stopping 
//			     condition.
//
//	PARAMETERS: myTree: templated Binary Search Tree.
//****************************************************************************
template <class T> 
void choose(BST<T>& myTree)
{
	char choice      = 'A';
	bool hasInserted = false;
	T    key;
	
	cout << "\nBST>> ";
	cin >> choice;
	
	while (choice != 'q' || choice != 'Q')
	{
		switch (choice)
		{
			case '+':
				validateInput(key);
				myTree.Insert(key);
				
				hasInserted = true;
				break;

			case '-':
				if (hasInserted)
				{
					validateInput(key);
					myTree.Delete(key);
				}
				else
				{
					cerr << "\nPlease insert data into the tree." << endl;				
					system("pause");
				}
				break;

			case '?':
				if (hasInserted)
				{
					validateInput(key);
					if (myTree.Search(key))
						cout << endl << key << " is in the tree!" << endl;
					else
						cerr << endl << key << " is not in the tree." << endl;
					system("pause");
				}
				else
				{
					cerr << "\nPlease insert data into the tree." << endl;
					system("pause");					
				}
				break;
				
			case 'r': case 'R':
				if (hasInserted)
				{
					myTree.Prune();
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
					cout << "The contents of the tree in order are: ";
					myTree.InOrder();
					cout << endl << endl;
					system("pause");
				}
				else
				{
					cerr << "\nPlease insert data into the tree." << endl;
					system("pause");					
				}
				break;

			case 'p': case 'P':
				if (hasInserted)
				{
					cout << "The contents of the tree in pre order are: ";
					myTree.PreOrder();
					cout << endl << endl;
					system("pause");
				}
				else
				{
					cerr << "\nPlease insert data into the tree." << endl;
					system("pause");					
				}
				break;

			case 't': case 'T':
				if (hasInserted)
				{
					cout << "The contents of the tree in post order are: ";
					myTree.PostOrder();
					cout << endl << endl;
					system("pause");
				}
				else
				{
					cerr << "\nPlease insert data into the tree." << endl;
					system("pause");					
				}
				break;

			case 'd': case 'D':
				myTree.~BST();
				hasInserted = false;
				break;  
				
			case'@':
				if (hasInserted)
				{
					myTree.PrintCursor();
					cout << endl;
					system("pause");
				}
				else
				{
					cerr << "\nPlease insert data into the tree." << endl;
					system("pause");					
				}
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
			myTree.PrintTree();
			
		cout << "BST>> ";
		cin >> choice;
	}	
}
/* End of choose function */


//****************************************************************************
//	NAME: validateInput.
//
//	DESCRIPTION: This function will validate the input from the user.  If 
//	             the user enters an invalid option for the value, then a 
//	             message will be displayed and the user will be asked to  
//	             try again.  Otherwise, the function will return the value 
//               to the caller.
//
//	PARAMETERS: value: the value entered by the user.
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
			cerr << endl << "Please enter a valid item for the tree." << endl;
        	cout << endl << ">> value: ";
		}
	}
	return value;
}

