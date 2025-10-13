//****************************************************************************
//	Driver File for Templated Treap.
//	Programmed by: Houston Brown.
//	Last Compiled Date: 10/12/2025
//
//	Copyright (c) 2022 Houston Brown.
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
#include "TestTreap.cpp"

void getExecChoice();
void printMainMenu();
void printMenu();

template <class T>
void choose(Treap<T>& myTreap);

template <class T>
T validateInput(T& value);

int main()
{
	srand(time(0));

	Treap<int> myTreap;
	printMainMenu();
	getExecChoice();

	return 0;
}

//****************************************************************************
//	NAME: getExecChoice.
//
//	DESCRIPTION: Retreive execution choice from the user.  
//
//	PARAMETERS: N/A.
//****************************************************************************
void getExecChoice()
{
	int userEntry = 0;

	while (userEntry != 4)
	{
		if (std::cin >> userEntry)
		{
			// Check if it's a valid input
			if (userEntry == 1)
			{
				WinUtils::clearScreen();
				Treap<int> myTreap;
				printMenu();
				choose(myTreap);
				return;
			}
			else if (userEntry == 2)
			{
				WinUtils::clearScreen();
				TestTreap<int> myTestTreap;
				myTestTreap.runTests();
				return;
			}
			else if (userEntry == 3)
			{
				std::cout << "Real World Scenario" << std::endl;
				WinUtils::pauseScreen();
			}
			else
			{
				std::cout << std::endl;
				std::cout << "Invalid entry, please try again." << std::endl;
			}
		}
		else
		{
			// Clear input buffer to handle invalid input.
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			std::cout << std::endl;
			std::cout << "Invalid entry, please try again." << std::endl;
		}

		WinUtils::clearScreen();
		printMainMenu();
		cout << endl;
	}
}

//****************************************************************************
//	NAME: printMainMenu.
//
//	DESCRIPTION: Print main menu of execution options to the user.
//
//	PARAMETERS: N/A.
//****************************************************************************
void printMainMenu()
{
	std::cout << " _______________________________________________________________________ ";
	std::cout << std::endl;

	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 47);

	std::cout << "|                                                                       |" << std::endl;
	std::cout << "|                         Treap Main Menu                               |" << std::endl;
	std::cout << "|_______________________________________________________________________|" << std::endl;

	SetConsoleTextAttribute(hConsole, 7);

	std::cout << "|                                                                       |" << std::endl;
	std::cout << "|      1.) Manual Exhibition.                                           |" << std::endl;
	std::cout << "|      2.) Automated Testing.                                           |" << std::endl;
	std::cout << "|      3.) Automated Integration.                                       |" << std::endl;
	std::cout << "|      4.) Quit                                                         |" << std::endl;
	std::cout << "|_______________________________________________________________________|" << std::endl;
	std::cout << "Please choose an execution option of the Treap." << std::endl;
}

//****************************************************************************
//  NAME: printMenu.
// 
//  DESCRIPTION: Function to display the available options of manual testing
//               to the user.
//
//	PARAMETERS: N/A.
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
//  NAME: choose
// 
//	DESCRIPTION: This function will prompt and accept the user's choice.  
//               If the choice is invalid, a message will be displayed.  
//               Otherwise, the action will be executed and the updated 
//               treap will be displayed along with the menu.  The user 
//               will continue to be prompted until they enter the 
//	             stopping condition.
//
//	PARAMETERS: myTreap: templated treap.
//****************************************************************************
template <class T>
void choose(Treap<T>& myTreap)
{
	T    key;
	char choice;
	bool hasInserted = false;

	cout << endl << ">> ";
	cin >> choice;

	while (choice != 'q' && choice != 'Q')
	{
		switch (choice)
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
//  NAME: validateInput
// 
//	DESCRIPTION: This function will validate the input from the user.  
//               If the user enters an invalid option for the value, then 
//               a message will be displayed and the user will be asked to 
//               try again.  Otherwise, the function will return the value to 
//               the caller.
//
//	PARAMETERS: value: the value entered by the user.
//****************************************************************************
template <class T>
T validateInput(T& value)
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