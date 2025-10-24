//****************************************************************************
//	Driver File for Templated Linked List
//	Programmed by: Houston Brown
//	Last Compiled Date: 10/17/2024
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



void printMainMenu();

void getExecChoice();

void printMenu();

template <class T> 
void choose(LinkedList<T> &myList);

template <class T>
T validateInput(T &value);




int main()
{
	//getManualOrAuto();
	printMainMenu();
	getExecChoice();

	return 0;
}




//****************************************************************************
//	NAME: printMainMenu.
//
//	DESCRIPTION: Print main menu of execution options to the user.
//
//	PARAMETERS:
//		N/A.
//****************************************************************************
void printMainMenu()
{
    std::cout << " _______________________________________________________________________ ";
    std::cout << std::endl;
    
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 47);    

    std::cout << "|                                                                       |" << std::endl;
    std::cout << "|                         Linked List Main Menu                         |" << std::endl;
    std::cout << "|_______________________________________________________________________|" << std::endl;

    SetConsoleTextAttribute(hConsole, 7);

    std::cout << "|                                                                       |" << std::endl;
    std::cout << "|      1.) Manual Exhibition.                                           |" << std::endl;
    std::cout << "|      2.) Automated Testing.                                           |" << std::endl;
    std::cout << "|      3.) Automated Integration.                                       |" << std::endl;
    std::cout << "|      4.) Quit                                                         |" << std::endl;
    std::cout << "|_______________________________________________________________________|" << std::endl;
    std::cout << "Please choose an execution option of the Linked List." << std::endl;
}


//****************************************************************************
//	NAME: getExecChoice.
//
//	DESCRIPTION: Retreive execution choice from the user.  
//
//	PARAMETERS:
//		N/A.
//****************************************************************************
void getExecChoice()
{
	int userEntry;
	
    while (userEntry != 4)
    {
        if (std::cin >> userEntry)
        {
            // Convert the input to uppercase
            //userEntry = std::toupper(userEntry);

            // Check if it's a valid input
            if (userEntry == 1)
            {
            	WinUtils::clearScreen();
            	LinkedList<int> myList;
                printMenu();
                choose(myList);
                return;
            }
            else if (userEntry == 2)
            {
            	WinUtils::clearScreen();
				TestLinkedList<int> theTest;
                theTest.runTests();
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
            // Clear input buffer to handle invalid input
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
//	NAME: printMenu.
//
//	DESCRIPTION: Function to display the available options to the user.
//
//	PARAMETERS:
//		N/A.
//****************************************************************************
void printMenu()
{
    std::cout << " ______________________________________________________________________";
    std::cout << std::endl;
    
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 47);

    std::cout << "|                 |                   |               |                |" << std::endl;
    std::cout << "|     INSERT      |       DELETE      |     PRINT     |     CURSOR     |" << std::endl;
    std::cout << "|_________________|___________________|_______________|________________|" << std::endl;
    
    SetConsoleTextAttribute(hConsole, 7);
    
    std::cout << "| +Key   In Order | -Key   Item       | F   to File   | @      Current |" << std::endl;
    std::cout << "| *Key   At Front | ~      At Front   | L   in Lines  | ?Key   Search  |" << std::endl;
    std::cout << "| #Key   At End   | `      At End     | B   Sort List | W      Up      |" << std::endl;
    std::cout << "|                 | C      Clear List | G   Size      | S      Down    |" << std::endl;
    std::cout << "|_________________|___________________|_______________|________________|" << std::endl;
    std::cout << "Please choose an operation to perform on the list." << std::endl;
    std::cout << "Enter E to exit." << std::endl;	
}


//****************************************************************************
//	NAME: choose.
//
//	DESCRIPTION: This function will prompt and accept the user's choice.  
//	             If the choice is invalid, a message will be displayed.  
//	             Otherwise, the action will be executed and the updated list 
//	             will be displayed along with the menu.  The user will 
//	             continue to be prompted until they enter the  stopping 
//				 condition.
//
//	PARAMETERS:
//		myList: a templated Linked List.
//****************************************************************************
template <class T> 
void choose(LinkedList<T> &myList)
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
			{
				
				validateInput(key);
				myList.Insert(key);
				
				hasInserted = true;
				break;
			}
			case '*':
			{
				validateInput(key);
				myList.InsertAtHead(key);
				
				hasInserted = true;
				break;
			}
			case '#':
			{
				validateInput(key);
				myList.InsertAtTail(key);
				
				hasInserted = true;
				break;
			}
			case '-':
			{
				if (hasInserted)
				{
					validateInput(key);
					myList.Remove(key);
				}
				else
				{
					cerr << "\nPlease insert data into the list." << endl;
					WinUtils::pauseScreen();
					system("pause");					
				}
				break;
			}
			case '~':
			{
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
			}
			case '?':
			{
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
			}
			case 'b': case 'B':
			{
				if (hasInserted)
				{
					myList.Sort();
				}
				else
				{
					cerr << "\nPlease insert data into the list." << endl;
					system("pause");
				}
				break;
			}
			case '@':
			{
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
			}
			case 'c': case 'C':
			{
				myList.~LinkedList();
				hasInserted = false;
				break;  
			}
			case 'f': case 'F':
			{
				if (hasInserted)
				{
					myList.PrintToFile();
				}
				else
				{
					std::cerr << "\nPlease insert data into the list.";
					std::cerr << std::endl;
					WinUtils::pauseScreen();
				}
				break; 
			}
			case 'l': case 'L':
			{
				if (hasInserted)
				{
					std::cout << std::endl;
					myList.PrintInLines();
					std::cout << std::endl;
				}
				else
				{
					std::cerr << "\nPlease insert data into the list.";
					std::cerr << std::endl;
				}
				WinUtils::pauseScreen();
				break; 
			}
			case 'g': case 'G':
			{
				if (hasInserted)
				{
					std::cout << "Current list size: " << myList.getSize();
					std::cout << std::endl;
				}
				else
				{
					std::cerr << "\nPlease insert data into the list.";
					std::cerr << std::endl;
				}
				WinUtils::pauseScreen();
				break; 
			}
			case 'w': case 'W':
			{
				if (hasInserted)
				{
					myList.moveCursorUp();
				}
				else
				{
					std::cerr << "\nPlease insert data into the list.";
					std::cerr << std::endl;
					WinUtils::pauseScreen();
				}
				break; 
			}
			case 's': case 'S':
			{
				if (hasInserted)
				{
					myList.moveCursorDown();
				}
				else
				{
					std::cerr << "\nPlease insert data into the list.";
					std::cerr << std::endl;
					WinUtils::pauseScreen();
				}
				break; 	
			}
			case 'e': case 'E':
			{
				exit(1);
			}
			default:
			{
				cerr << "Invalid option, please try again." << endl;
				system("pause");
				break;
			}
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
//	NAME: validateInput.
//
//	DESCRIPTION: This function will validate the input from the user.  If 
//				 the user enters an invalid option for the value, then a 
//				 message will be displayed and the user will be asked to try 
//				 again.  Otherwise, the function will return the value to 
//				 the caller.
//
//	PARAMETERS:
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
			cerr << endl << "Please enter a valid item for the list." << endl;
        	cout << endl << ">> value: ";
		}
	}
	return value;
}
