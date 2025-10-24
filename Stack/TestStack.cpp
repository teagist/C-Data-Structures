//****************************************************************************
//	Implementation File for Queue Test
//	Programmed by: Houston Brown
//	Last Compiled Date: 10/24/2025
//****************************************************************************

#include "TestStack.h"

//****************************************************************************
//	CONSTRUCTOR.   
//****************************************************************************
template <class U>
TestStack<U>::TestStack()
{
	testLogger.setTest("Stack Test");
	testLogger.setVersion("1.00.00.01");
	testLogger.setTitlebar();
}

//****************************************************************************
//	NAME: getMaxPossibleListNodes.
//
//	DESCRIPTION: Return the max number of possible nodes that can be 
//				 allocated.   
//****************************************************************************
template <class U>
int TestStack<U>::getMaxPossibleNodes()
{
	try
	{
		MEMORYSTATUSEX status;
	    status.dwLength = sizeof(status);
	    GlobalMemoryStatusEx(&status);
	
	    /*std::cout << "Total physical memory: " << status.ullTotalPhys;
		std::cout << " bytes" << std::endl;	
	    std::cout << "The size of a Queue Node is: ";
		std::cout << sizeof(QNode<U>) << std::endl;*/
		size_t maxObjs = status.ullTotalPhys / sizeof(StackNode<U>);
		//std::cout << "The total number of Queue Nodes is: " << maxObjs << std::endl;
		
		return maxObjs;		
	}
	catch(...)
	{
		std::cerr << "Unexpected error when retreiving max number of ";
		std::cerr << "objects." << std::endl;
	}
	return 0;
}

//****************************************************************************
//	NAME: printTestInfoHeader.
//
//	DESCRIPTION: Print the preliminary information about the test.  
//****************************************************************************
template <class U>
void TestStack<U>::printTestInfoHeader()
{
	try
	{
		std::string stars = "****************************************";
		std::cout << stars << stars << std::endl;
		testLogger.printLineHeader();
		std::cout << "Testing Validity of Stack Class." << std::endl;
		
		testLogger.printLineHeader();
		std::cout << "Test Started." << std::endl;
		
		testLogger.printLineHeader();
		std::cout << "Test Name: " << testLogger.getTest() << std::endl;
		
		std::cout << "\t\t Group: 1" << std::endl;
		std::cout << "\t\t Tester: Houston Brown" << std::endl;
		
		std::cout << "\t\t Hardware Information: " << std::endl;
		WinUtils::printHardwareDetails();
		std::cout << std::endl;
		
		std::cout << "\t\t Operating System: ";
		WinUtils::printOSDetails();
		std::cout << std::endl << stars << stars;
	}
	catch(...)
	{
		std::cerr << "Error retrieving test info." << std::endl;
	}
}

//****************************************************************************
//	NAME: runTests.
//
//	DESCRIPTION: This method will run all of the subtests for the test case. 
//****************************************************************************
template <class U>
void TestStack<U>::runTests()
{
	WinUtils::clearScreen();
	printTestInfoHeader();
	std::cout << std::endl;
	
	int maxNodes = getMaxPossibleNodes();
	bool testStatus = false;
	try
	{
		if (bulkPush())
		{			
			testPop();
			
			bulkPop();
			
			testPeek();
			
			testEmptyStackSearch();
			
			testNotFoundSearch();
			
			testSearch();
		}
		else
		{
			std::cerr << "Unable to bulk load the stack." << std::endl;
		}	
	}
	catch(...)
	{
		std::cerr << "Unexpected exception caught when running test.";
		std::cerr << " sequence." << std::endl;
	}
	
	testLogger.printResult();
}
//****************************************************************************

//****************************************************************************
//	NAME: bulkPush.
//
//	DESCRIPTION: The purpose of this function is to load the stack with 100
//				 items.  
//****************************************************************************
template <class U>
bool TestStack<U>::bulkPush()
{
	int status = OK;
	
	testLogger.logEvent("***** Begin Bulk Push Test *****", INFO);
	testLogger.logEvent("Attempting to Push 100 items into the Stack", INFO);
	WinUtils::wait(5);
	try
	{
		U   value;
		int numOfNodes = 0;
		int stackMax   = 100;
		
		while (numOfNodes < stackMax)
		{
			testStack.Push(value);
			numOfNodes = numOfNodes + 1;
		}
	}
	catch(...)
	{
		std::string errMsg = "Unexcpected error occurred while bulk "
		                     "inserting values into the stack.";
		testLogger.logEvent(errMsg, FAIL);
		status = FAIL;
	}

	if (status == OK)
	{
		testLogger.logEvent("Successfully added all items to the stack", OK);
		WinUtils::wait(5);
	}
	
	if (status == OK && testStack.Size() == 100)
	{
		testLogger.logEvent("Printing Queue of 100 items", INFO);
		testStack.Print();
		testLogger.printStatusMessage("Bulk Push Test Passed.", OK);
	}
	else
	{
		testLogger.printStatusMessage("Bulk Push Test Failed.", FAIL);
	}

	
	testLogger.logEvent("***** Bulk Push Test complete *****", INFO);
	testLogger.setPassingStatus(status);
	std::cout << std::endl;
	return status;
}

//****************************************************************************
//	NAME: testPop.
//
//	DESCRIPTION: This test will add items to the stack and test the pop
//				 functionality.  
//****************************************************************************
template <class U>
bool TestStack<U>::testPop()
{
	testLogger.logEvent("***** Begin Pop Test *****", INFO);
	int status = OK;
	
	try
	{
		testLogger.logEvent("Clearing the queue before further testing.", 
		                                                           INFO);
		testStack.~Stack();
		if (testStack.Size() == 0)
		{
			testLogger.logEvent("Successfully cleared the stack.", OK);
		}
		else
		{
			testLogger.logEvent("Failed to destroy the stack.", FAIL);
			status = FAIL;
		}
	}
	catch(...)
	{
		std::string exMsg = "Unexpected exception occurred when attempting"
		                    " to destroy the stack.";
		testLogger.logEvent(exMsg, FAIL);
		status = FAIL;
		testLogger.setPassingStatus(status);
	}
	
	try
	{
		testLogger.logEvent("Adding 3 values to the queue.", INFO);
		WinUtils::wait(5);
		
		U value1;
		U value2;
		U value3;
		testStack.Push(value1);
		testStack.Push(value2);
		testStack.Push(value3);
		
		testLogger.logEvent("Printing the stack.", INFO);
		std::cout << "\nStack before pop" << std::endl;
		testStack.Print();
		std::cout << std::endl;
		
		testLogger.logEvent("Removing the first value.", INFO);
		testStack.Pop();
		WinUtils::wait(5);
		
		testLogger.logEvent("Printing the stack after pop.", INFO);
		std::cout << "\nStack after pop" << std::endl;
		testStack.Print();
		std::cout << std::endl;
		
		if (testStack.Size() == 2)
		{
			testLogger.logEvent("Successfully popped.", OK);
		}
		else
		{
			testLogger.logEvent("Failed to pop.", FAIL);
			status = FAIL;
		}
	}
	catch(...)
	{
		std::string errMsg = "Unexpected exception caught while testing "
		                     "pop.";
		testLogger.logEvent(errMsg, FAIL);
		status = FAIL;
		testLogger.setPassingStatus(status);
	}
	
	if (status == OK)
	{
		testLogger.printStatusMessage("Pop Passed.", OK);
	}
	else
	{
		testLogger.printStatusMessage("Pop Failed.", FAIL);
		testLogger.setPassingStatus(status);
	}
	
	testLogger.logEvent("***** End Dequeue Test *****", INFO);
	std::cout << std::endl;
	return status;
}

//****************************************************************************
//	NAME: bulkDequeue.
//
//	DESCRIPTION: Push 100 items into the stack and then pop all items 
//				 from the stack. 
//****************************************************************************
template <class U>
bool TestStack<U>::bulkPop()
{
	testLogger.logEvent("***** Begin Bulk Pop Test *****", INFO);
	int status = OK;
	
	try
	{
		testLogger.logEvent("Clearing the stack before further testing.", 
		                                                           INFO);
		testStack.~Stack();
		if (testStack.Size() == 0)
		{
			testLogger.logEvent("Successfully cleared the stack.", OK);
		}
		else
		{
			testLogger.logEvent("Failed to destroy the stack.", FAIL);
			status = FAIL;
		}
	}
	catch(...)
	{
		std::string exMsg = "Unexpected exception occurred when attempting"
		                    " to destroy the stack.";
		testLogger.logEvent(exMsg, FAIL);
		status = FAIL;
		testLogger.setPassingStatus(status);
	}
	
	try
	{
		U   value;
		int ctr      = 0;  
		int stackMax = 100;
		
		testLogger.logEvent("Pushing 100 items to the stack.", INFO);
		WinUtils::wait(5);
		while (ctr < stackMax)
		{
			testStack.Push(value);
			ctr = ctr + 1;
		}
		
		testLogger.logEvent("Pop 100 items from the stack.", INFO);
		ctr = 0;
		while (ctr < stackMax)
		{
			testStack.Pop();
			ctr = ctr + 1;
		}
		
		if (testStack.Size() == 0)
		{
			testLogger.logEvent("Successfully popped 100 items.", OK);
		}
		else
		{
			testLogger.logEvent("Failed to popped 100 items", FAIL);
		}
	}
	catch(...)	
	{
		std::string errMsg = "Unexpected exception caught while testing "
		                     "bulk pop.";
		testLogger.logEvent(errMsg, FAIL);
		status = FAIL;
		testLogger.setPassingStatus(status);
	}
	
	if (status == OK)
	{
		testLogger.printStatusMessage("Bulk Pop Passed.", OK);
	}
	else
	{
		testLogger.printStatusMessage("Bulk Pop Failed.", FAIL);
		testLogger.setPassingStatus(status);
	}
	
	testLogger.logEvent("***** End Bulk Pop Test *****", INFO);
	std::cout << std::endl;
	return status;	
}

//****************************************************************************
//	NAME: testPeek.
//
//	DESCRIPTION: Push several items into the stack and test that the peek
//				 function returns the correct values.    
//****************************************************************************
template <class U>
bool TestStack<U>::testPeek()
{
	testLogger.logEvent("***** Begin Peek Test *****", INFO);
	int status = OK;
	
	try
	{
		testLogger.logEvent("Clearing the stack before further testing.", 
		                                                           INFO);
		testStack.~Stack();
		if (testStack.Size() == 0)
		{
			testLogger.logEvent("Successfully cleared the stack.", OK);
		}
		else
		{
			testLogger.logEvent("Failed to destroy the stack.", FAIL);
			status = FAIL;
		}
	}
	catch(...)
	{
		std::string exMsg = "Unexpected exception occurred when attempting"
		                    " to destroy the stack.";
		testLogger.logEvent(exMsg, FAIL);
		status = FAIL;
		testLogger.setPassingStatus(status);
	}
	
	try
	{
		testLogger.logEvent("Adding 3 values to the stack.", OK);
		U value1;
		U value2;
		U value3;
		
		testStack.Push(value1);
		testStack.Push(value2);
		testStack.Push(value3);
		
		testLogger.logEvent("Peeking the stack...", INFO);
		if (testStack.Peek() == value3)
		{
			std::string passMsg = "Peek was equal to the front of the stack.";
			testLogger.logEvent(passMsg, OK);
		}
		else
		{
			std::string failMsg = "Peek did not return the expected value.";
			testLogger.logEvent(failMsg, FAIL);
			status = FAIL;
		}
	}
	catch(...)	
	{
		std::string errMsg = "Unexpected exception caught while testing "
		                     "peek.";
		testLogger.logEvent(errMsg, FAIL);
		status = FAIL;
		testLogger.setPassingStatus(status);
	}
	
	if (status == OK)
	{
		testLogger.printStatusMessage("Peek Passed.", OK);
	}
	else
	{
		testLogger.printStatusMessage("Peek Failed.", FAIL);
		testLogger.setPassingStatus(status);
	}
	
	testLogger.logEvent("***** End Peek Test *****", INFO);
	std::cout << std::endl;
	return status;
}

//****************************************************************************
//	NAME: testEmptyStackSearch.
//
//	DESCRIPTION: Clear the stack and attempt to search for values in the
//				 stack. 
//****************************************************************************
template <class U>
bool TestStack<U>::testEmptyStackSearch()
{
	testLogger.logEvent("***** Begin Empty Stack Search Test *****", INFO);
	int status = OK;
	
	try
	{
		testLogger.logEvent("Clearing the stack before further testing.", 
		                                                           INFO);
		testStack.~Stack();
		if (testStack.Size() == 0)
		{
			testLogger.logEvent("Successfully cleared the stack.", OK);
		}
		else
		{
			testLogger.logEvent("Failed to destroy the stack.", FAIL);
			status = FAIL;
		}
	}
	catch(...)
	{
		std::string exMsg = "Unexpected exception occurred when attempting"
		                    " to destroy the stack.";
		testLogger.logEvent(exMsg, FAIL);
		status = FAIL;
		testLogger.setPassingStatus(status);
	}
	
	try
	{
		if (status == OK && testStack.Size() == 0)
		{
			testLogger.logEvent("Attempting to search empty stack...", INFO);
			WinUtils::wait(5);
			
			U value;
			if (testStack.Search(value))
			{
				testLogger.logEvent("Unexpectedly found the item", FAIL);
				status = FAIL;
			}
			else
			{
				testLogger.logEvent("Successfully did not find the item", OK);
			}
		}
		else
		{
			std::string failMsg = "Unable to test due to issues destroying"
			                      " the stack.";
			testLogger.logEvent(failMsg, FAIL);
			status = FAIL;
		}
	}
	catch(...)
	{
		std::string errMsg = "Unexpected exception caught while testing"
		                     " search of an empty stack.";
		testLogger.logEvent(errMsg, FAIL);
		status = FAIL;
		testLogger.setPassingStatus(status);
	}
	
	if (status == OK)
	{
		testLogger.printStatusMessage("Empty Stack Search Passed.", OK);
	}
	else
	{
		testLogger.printStatusMessage("Empty Stack Search Failed.", FAIL);
		testLogger.setPassingStatus(status);
	}
	
	testLogger.logEvent("***** End Empty Stack Search Test *****", INFO);
	std::cout << std::endl;
	return status;	
}

//****************************************************************************
//	NAME: testNotFoundSearch.
//
//	DESCRIPTION: Push several items into the stack and search for values
//				 not in the stack.  
//****************************************************************************
template <class U>
bool TestStack<U>::testNotFoundSearch()
{
	testLogger.logEvent("***** Begin Not Found Search Test *****", INFO);
	int status = OK;
	
	try
	{
		testLogger.logEvent("Clearing the stack before further testing.", 
		                                                           INFO);
		testStack.~Stack();
		if (testStack.Size() == 0)
		{
			testLogger.logEvent("Successfully cleared the stack.", OK);
		}
		else
		{
			testLogger.logEvent("Failed to destroy the stack.", FAIL);
			status = FAIL;
		}
	}
	catch(...)
	{
		std::string exMsg = "Unexpected exception occurred when attempting"
		                    " to destroy the stack.";
		testLogger.logEvent(exMsg, FAIL);
		status = FAIL;
		testLogger.setPassingStatus(status);
	}
	
	try
	{
		U value1;
		U value2;
		
		testLogger.logEvent("Adding value to the stack.", INFO);
		testStack.Push(value1);
		
		testLogger.logEvent("Searching for item not in stack...", INFO);
		WinUtils::wait(5);
		
		if (testStack.Search(value2))
		{
			testLogger.logEvent("Unexpectedly found the item", FAIL);
		}
		else
		{
			testLogger.logEvent("Successfully did not find the item", OK);
		}
		
	}
	catch(...)
	{
		std::string errMsg = "Unexpected exception caught while testing"
		                     " invalid search of a stack.";
		testLogger.logEvent(errMsg, FAIL);
		status = FAIL;
		testLogger.setPassingStatus(status);
	}
	
	if (status == OK)
	{
		testLogger.printStatusMessage("Not Found Search Passed.", OK);
	}
	else
	{
		testLogger.printStatusMessage("Not Found Search Failed.", FAIL);
		testLogger.setPassingStatus(status);
	}
	
	testLogger.logEvent("***** End Not Found Search Test *****", INFO);
	std::cout << std::endl;
	return status;		
}

//****************************************************************************
//	NAME: testSearch.
//
//	DESCRIPTION: Push items into the stack and seach for those same values
//				 to determine if the search function will return 
//				 successfully.  
//****************************************************************************
template <class U>
bool TestStack<U>::testSearch()
{
	testLogger.logEvent("***** Begin Successful Search Test *****", INFO);
	int status = OK;
	
	try
	{
		testLogger.logEvent("Clearing the stack before further testing.", 
		                                                           INFO);
		testStack.~Stack();
		if (testStack.Size() == 0)
		{
			testLogger.logEvent("Successfully cleared the stack.", OK);
		}
		else
		{
			testLogger.logEvent("Failed to destroy the stack.", FAIL);
			status = FAIL;
		}
	}
	catch(...)
	{
		std::string exMsg = "Unexpected exception occurred when attempting"
		                    " to destroy the stack.";
		testLogger.logEvent(exMsg, FAIL);
		status = FAIL;
		testLogger.setPassingStatus(status);
	}
	
	try
	{
		U value1;
		U value2;
		U value3;
		
		testLogger.logEvent("Adding 3 values to the stack.", INFO);
		WinUtils::wait(5);
		
		testStack.Push(value1);
		testStack.Push(value2);
		testStack.Push(value3);
		
		testLogger.logEvent("Searching queue for valid item...", INFO);
		WinUtils::wait(5);
		if (testStack.Search(value1))
		{
			testLogger.logEvent("Item was found in the stack!", OK);
		}
		else
		{
			testLogger.logEvent("Item was not found in the stack", FAIL);
		}
	}
	catch(...)
	{
		std::string errMsg = "Unexpected exception caught while testing"
		                     " search functionality.";
		testLogger.logEvent(errMsg, FAIL);
		status = FAIL;
		testLogger.setPassingStatus(status);
	}
	
	if (status == OK)
	{
		testLogger.printStatusMessage("Successful Search Passed.", OK);
	}
	else
	{
		testLogger.printStatusMessage("Successful Search Failed.", FAIL);
		testLogger.setPassingStatus(status);
	}	
	
	testLogger.logEvent("***** End Successful Search  Test *****", INFO);
	std::cout << std::endl;
	return status;
}
