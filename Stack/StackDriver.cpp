//***************************************************************************
//		Driver to test the templated stack.  This program will open by 
//	displaying the available operations to the user and prompting them for
//	input.  Once the user enters the letter 'q' or 'Q', then the program
//	will terminate.
//
//	Programmed by: Houston Brown
//	Last Compiled Date: 10/24/2025
//***************************************************************************

#include "Stack.h"
#include "TestStack.cpp"
#include <limits>
#include <sstream>

void getManualOrAuto();

void printMenu();

template <class T>
void choose(Stack<T>& myStack);

template <class T>
T validateInput(T &val);

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
            	TestStack<int> theTest;
                theTest.runTests();
                return;
            }
            else if (userEntry == 'N')
            {
                Stack<int> myStack;
                printMenu();
                choose(myStack);
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

//***************************************************************************
//	Function to display the available options to the user.
//
//	Parameters:
//		N/A
//***************************************************************************
void printMenu()
{
    cout << " _____________________________" << endl;
    cout << "| +Item  | Push Item          | " << endl;
	cout << "|   -    | Pop Item           | " << endl;
    cout << "| ?Item  | Search Item        | " << endl;
    cout << "|   @    | Peek               | " << endl;
	cout << "|   D    | Destory the Stack  | " << endl;
    cout << "|________|____________________| " << endl << endl;
    cout << "Please choose an operation to perform on a stack." << endl;
    cout << "Enter Q to quit." << endl;
}

//***************************************************************************
//		This function will prompt and accept the user's choice.  If the
//	choice is invalid, a message will be displayed.  Otherwise, the action
//	will be executed and the updated stack will be displayed along with the
//	menu.  The user will continue to be prompted until they enter the 
//	stopping condition.
//
//	Parameters:
//		myStack: templated stack.
//***************************************************************************

template<class T>
void choose(Stack<T>& myStack)
{
    T value;
    char choice;
    
    cout << endl << "Stack>> ";
    cin >> choice;
    
    while(choice != 'q' || choice != 'Q')
    {
        switch (choice)
        {
			case '+':
			{
				validateInput(value);
				myStack.Push(value);
				break;
			}
			case '-':
			{
			    myStack.Pop();
				break;
			}
			case '?':
			{
                validateInput(value);
                myStack.Search(value);
                system("pause");
				break;
			}
			case '@' :
			{
				cout << endl;
				if (myStack.Peek())
				{
					cout << "The top of the stack is: " << myStack.Peek();
					cout << endl;
				}
				system("pause");
				break;
			}
			case 'd': case 'D':
			{
				myStack.~Stack();
				break;
			}
            case 'q': case 'Q':
            {
                exit(1);
            }
			default:
			{
				cerr << "\nInvalid choice. Please try again." << endl;
				cout << endl;
                system("pause");
            }
		}
        system("cls");
        printMenu();
        cout << endl;
        myStack.Print();
        cout << "Stack>> ";
        cin >> choice;
    }
}

//***************************************************************************
//		This function will validate the input from the user.  If the user
//	enters an invalid option for the value, then a message will be displayed
//	and the user will be asked to try again.  Otherwise, the function will
//	return the value to the caller.
//
//	Parameters:
//		val: the value entered by the user
//***************************************************************************
template <class T>
T validateInput(T &val)
{
	while (true)
	{
		if (cin >> val)
		{
			break;
		}
		else
		{
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			system("cls");
			printMenu();
			cerr << endl << "Please enter a valid item for the stack." << endl;
        	cout << endl << ">> value: ";
		}
	}
	return val;
}
