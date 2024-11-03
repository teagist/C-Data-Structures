//***************************************************************************
//		Driver to test the templated queue.  This program will open by 
//	displaying the available operations to the user and prompting them for
//	input.  Once the user enters the letter 'q' or 'Q', then the program
//	will terminate.
//
//	Programmed by: Houston Brown
//	Last Compiled Date: 11/3/2024
//***************************************************************************

#include "Queue.h"
#include "TestQueue.cpp"
#include <limits>
#include <sstream>



void getManualOrAuto();

void printMenu();

template<class T>
void choose(Queue<T>& myQueue);

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
            	TestQueue<int> theTest;
                theTest.runTests();
                return;
            }
            else if (userEntry == 'N')
            {
                Queue<int> myQueue;
                printMenu();
                choose(myQueue);
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
    cout << "| +Item  | Enqueue Item       | " << endl;
	cout << "|   -    | Dequeue Item       | " << endl;
    cout << "| ?Item  | Search Item        | " << endl;
    cout << "|   @    | Peek               | " << endl;
	cout << "|   D    | Destory the Queue  | " << endl;
    cout << "|________|____________________| " << endl << endl;
    cout << "Please choose an operation to perform on a queue." << endl;
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
//		myQueue: templated queue.
//***************************************************************************
template<class T>
void choose(Queue<T>& myQueue)
{
    T value;
    char choice;
    
    cout << endl << "Queue>> ";
    cin >> choice;
    
    while(choice != 'q' || choice != 'Q')
    {
        switch (choice)
        {
			case '+':
				cin >> value;
				myQueue.Enqueue(value);
				break;
			case '-':
			    myQueue.Dequeue();
				break;
			case '?':
                cin >> value;
                myQueue.Search(value);
                system("pause");
				break;
			case '@' :
				cout << endl;
				if (myQueue.Peek())
				{
					cout << "The top of the stack is: " << myQueue.Peek();
					cout << endl;
				}
				system("pause");
				break;
			case 'd': case 'D':
				myQueue.~Queue();
				break;
            case 'q': case 'Q':
                exit(1);
			default:
				cout << "\nInvalid choice. Please try again." << endl;
				cout << endl;
                system("pause");
		}
        system("cls");
        printMenu();
        cout << endl;
        myQueue.Print();
        cout << "Queue>> ";
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
			break;
		else
		{
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			system("cls");
			printMenu();
			cerr << endl << "Please enter a valid item for the queue." << endl;
        	cout << endl << ">> value: ";
		}
	}
	return val;
}
