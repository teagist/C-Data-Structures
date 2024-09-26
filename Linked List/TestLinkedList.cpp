//****************************************************************************
//	Implementation File for Linked List Test
//	Programmed by: Houston Brown
//	Last Compiled Date: 1/15/2024
//****************************************************************************

#include "TestLinkedList.h"
#include <string>


//****************************************************************************
//	CONSTRUCTOR.   
//****************************************************************************

template <class U>
TestLinkedList<U>::TestLinkedList()
{
	testLogger.setTest("Linked List Test");
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
int TestLinkedList<U>::getMaxPossibleListNodes()
{
	try
	{
		MEMORYSTATUSEX status;
	    status.dwLength = sizeof(status);
	    GlobalMemoryStatusEx(&status);
	
	    //std::cout << "Total physical memory: " << status.ullTotalPhys;
		//std::cout << " bytes" << std::endl;	
	    //std::cout << "The size of a Linked List Node is: ";
		//std::cout << sizeof(Node<U>) << std::endl;
		size_t maxObjs = status.ullTotalPhys / sizeof(Node<U>);
		//std::cout << "The total number of Linked List Nodes is: " << maxObjs << std::endl;
		
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
void TestLinkedList<U>::printTestInfoHeader()
{
	try
	{
		std::string stars = "****************************************";
		std::cout << stars << stars << std::endl;
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
//	NAME: bulkInsert.
//
//	DESCRIPTION: The purpose of this function is to load the lsit with 100
//				 items.  
//****************************************************************************

template <class U>
bool TestLinkedList<U>::bulkInsert()
{
	int status = OK;
	
	try
	{
		U value;
		int numOfNodes = 0;
		int listMax    = 100;
		
		while (numOfNodes < listMax)
		{
			testList.Insert(value);
			numOfNodes = numOfNodes + 1;
		}
	}
	catch(...)
	{
		std::cerr << "Unexcpected error occurred while bulk inserting values";
		std::cerr << " into the list.";
		status = FAIL;
	}

	return status;
}



//****************************************************************************
//	NAME: runTests.
//
//	DESCRIPTION: This method will run all of the subtests for the test case. 
//****************************************************************************

template <class U>
void TestLinkedList<U>::runTests()
{
	printTestInfoHeader();
	std::cout << std::endl;
	
	int maxNodes = getMaxPossibleListNodes();
	bool testStatus = false;
	try
	{
		if (bulkInsert())
		{
			testInOrderInsert();
			std::cout << std::endl;
			
			testInsertAtHead();
			std::cout << std::endl;
			
			testInsertAtTail();
			std::cout << std::endl;
			
			testRemove();
			std::cout << std::endl;
			
			testRemoveFromHead();
			std::cout << std::endl;
			
			testRemoveFromTail();
			std::cout << std::endl;
			
			testEmptyListSearch();
			std::cout << std::endl;
			
			testNotFoundSearch();
			std::cout << std::endl;
			
			testAtHeadSearch();
			std::cout << std::endl;
			
			testAtTailSearch();
			std::cout << std::endl;
			
			testSearch();
		}
		else
		{
			std::cerr << "Unable to bulk load the list." << std::endl;
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
//	NAME: testInOrderInsert.
//
//	DESCRIPTION: Test method that will fill the list, and attempt to insert
//				 a value "in-order".  
//****************************************************************************

template <class U>
bool TestLinkedList<U>::testInOrderInsert()
{
	testLogger.logEvent("******* Begin In-Order-Insert Test *******", INFO);
	int subTestStatus = -1;
	
	try
	{
		std::ostringstream oss;
		
		// Clearing the list if its populated.
		testLogger.logEvent("Clearing the list.", INFO);
		testList.Clear();
		
		oss << "Inserting 10, 20, 30, 40, and 50 as default values in the";
		oss << " list.";
		testLogger.logEvent(oss.str(), INFO);
		oss.str("");
		oss.clear();
		
		U firstValue   = U(10);
		U secValue     = U(20);
		U thirdValue   = U(30);
		U fourthValue  = U(40);
		U fifthValue   = U(50);
		U testValue    = U(15);

		testList.Insert(firstValue);
		testList.Insert(secValue);
		testList.Insert(thirdValue);
		testList.Insert(fourthValue);
		testList.Insert(fifthValue);
		
		oss << "Attempting to insert the value " << testValue;
		oss << " into the list.";
		testLogger.logEvent(oss.str(), INFO);
		oss.str("");
		oss.clear();

		testList.Insert(testValue);
		
		if (testList.Search(testValue))
		{	
			oss << testValue << " is in the list!";
			testLogger.logEvent(oss.str(), OK);

			testLogger.printStatusMessage("In-Order-Insert Test Passed.", OK);
			testLogger.logEvent("******* End In-Order-Insert Test *******", 
			                    INFO);
		}
		else
		{
			oss << testValue << "is NOT in the list.";
			testLogger.logEvent(oss.str(), FAIL);

			testLogger.printStatusMessage("In-Order-Insert Test Failed.", 
			                              FAIL);
			testLogger.logEvent("******* End In-Order-Insert Test *******", 
			                    INFO);
			testLogger.setPassingStatus(FAIL);			                    
		}
	}
	catch(...)
	{
		std::string errorMsg = "Unexpected exception occurred testing item"
					            " removal functionality.";
		testLogger.logEvent(errorMsg, FAIL);
		
		testLogger.printStatusMessage("In-Order-Insert Test Failed.", FAIL);
		testLogger.logEvent("******* End In-Order-Insert Test *******", INFO);
		
		testLogger.setPassingStatus(FAIL);
	}	
		
	return subTestStatus;	
}



//****************************************************************************
//	NAME: testInsertAtHead.
//
//	DESCRIPTION: This subtest will attempt to insert a new item to the front
//				 of the list.  If the item becomes the new head of the list,
//				 then the test will pass.  Otherwise, it will fail.
//****************************************************************************

template <class U>
bool TestLinkedList<U>::testInsertAtHead()
{
	testLogger.logEvent("******* Begin Insert-At-Head Test *******", INFO);
	
	int subTestStatus = -1;	
	try
	{
		U newHeadValue;
		std::ostringstream oss;
		
		oss << "Attempting to insert " << newHeadValue << " at the head.";
		testLogger.logEvent(oss.str(), INFO);
		
		testList.InsertAtHead(newHeadValue);
		
		if (newHeadValue == testList.getHeadValue())
		{
			oss.str("");
			oss.clear();
			oss << newHeadValue << " is at the head of the list.";
			testLogger.logEvent(oss.str(), INFO);
			
			subTestStatus = OK;

			testLogger.printStatusMessage("Insert-At-Head Test Passed.", OK);
			testLogger.logEvent("******* End Insert-At-Head Test *******", 
			                    INFO);
		}
		else
		{
			oss.str("");
			oss.clear();
			
			oss << newHeadValue << " is NOT at the head of the list.";
			testLogger.logEvent(oss.str(), INFO);
			
			subTestStatus = FAIL;

			testLogger.printStatusMessage("Insert-At-Head test Failed.", 
			                              FAIL);
			testLogger.logEvent("******* End Insert-At-Head Test *******", 
			                    INFO);
			
			testLogger.setPassingStatus(FAIL);			
		}
	}
	catch(...)
	{
		std::string errorMsg = "Unexpected exception occurred testing insert"
					           " at the head functionality.";
		testLogger.logEvent(errorMsg, FAIL);

		testLogger.printStatusMessage("Insert-At-Head Test Failed.", FAIL);
		testLogger.logEvent("******* End Insert-At-Head Test *******", INFO);
		
		testLogger.setPassingStatus(FAIL);		
	}	
		
	return subTestStatus;  
}



//****************************************************************************
//	NAME: testInsertAtTail.
//
//	DESCRIPTION: This subtest will attempt to insert a new item to the back
//				 of the list.  If the item becomes the new tail of the list,
//				 then the test will pass.  Otherwise, it will fail. 
//****************************************************************************

template <class U>
bool TestLinkedList<U>::testInsertAtTail()
{
	testLogger.logEvent("******* Begin Insert-At-Tail Test *******", INFO);
	
	int subTestStatus = -1;	
	try
	{
		U newTailValue = U(-100);
		std::ostringstream oss;
		
		oss << "Attempting to insert " << newTailValue << " at the tail.";
		testLogger.logEvent(oss.str(), INFO);
		
		testList.InsertAtTail(newTailValue);
		
		if (newTailValue == testList.getTailValue())
		{
			oss.str("");
			oss.clear();
			
			oss << newTailValue << " is at the tail of the list.";
			testLogger.logEvent(oss.str(), INFO);

			testLogger.printStatusMessage("Insert-At-Tail Test Passed.", OK);
			testLogger.logEvent("******* End Insert-At-Tail Test *******", 
			                    INFO);
		}
		else
		{
			oss.str("");
			oss.clear();
			
			oss << newTailValue << " is NOT at the tail of the list.";
			testLogger.logEvent(oss.str(), INFO);
			
			subTestStatus = FAIL;

			testLogger.printStatusMessage("Insert-At-Tail Test Failed.", 
			                              FAIL);
			testLogger.logEvent("******* End Insert-At-Tail Test *******", 
							    INFO);
			
			testLogger.setPassingStatus(FAIL);						
		}
	}
	catch(...)
	{
		std::string errorMsg = "Unexpected exception occurred testing insert"
					           " at the tail functionality.";
		testLogger.logEvent(errorMsg, FAIL);

		testLogger.printStatusMessage("Insert-At-Tail Test Failed.", FAIL);		
		testLogger.logEvent("******* End Insert-At-Tail Test *******", INFO);
		
		testLogger.setPassingStatus(FAIL);
	}	
	
	return subTestStatus;	
}



//****************************************************************************
//	NAME: testRemove.
//
//	DESCRIPTION: This subtest will begin by clearing the list.  Then default
//				 values will be loaded into the list and the test will 
//				 attempt to delete the middle value.  If this is successful,
//				 the test will pass, otherwise it will fail.  
//****************************************************************************

template <class U>
bool TestLinkedList<U>::testRemove()
{
	testLogger.logEvent("******* Begin Remove Test *******", INFO);
	int subTestStatus = -1;
	
	try
	{
		std::ostringstream oss;
		
		// Clearing the list if its populated.
		testLogger.logEvent("Clearing the list.", INFO);
		testList.Clear();
		
		oss << "Inserting 10, 20, 30, 40, and 50 as default values in the";
		oss << " list.";
		testLogger.logEvent(oss.str(), INFO);
		oss.str("");
		oss.clear();
		
		U firstValue   = U(10);
		U secValue     = U(20);
		U thirdValue   = U(30);
		U fourthValue  = U(40);
		U fifthValue   = U(50);

		testList.Insert(firstValue);
		testList.Insert(secValue);
		testList.Insert(thirdValue);
		testList.Insert(fourthValue);
		testList.Insert(fifthValue);
		
		oss << "Attempting to remove the middle value " << thirdValue;
		oss << " from the list.";
		testLogger.logEvent(oss.str(), INFO);
		oss.str("");
		oss.clear();
		
		if (testList.isEmpty())
		{
			testLogger.logEvent("Error: the list is empty.", FAIL);
			testLogger.printStatusMessage("Remove Test Failed.", FAIL);
			testLogger.logEvent("******* End Remove Test *******", INFO);			
			testLogger.setPassingStatus(FAIL);			
		}
		else
		{
			testList.Remove(thirdValue);
			
			if (testList.Search(thirdValue))
			{	
				oss << thirdValue << " is still in the list after calling";
				oss << " the Remove method.";
				testLogger.logEvent(oss.str(), FAIL);

				testLogger.printStatusMessage("Remove Test Failed.", FAIL);
				testLogger.logEvent("******* End Remove Test *******", INFO);			
				testLogger.setPassingStatus(FAIL);
			}
			else
			{
				oss << thirdValue << " was successfully removed from the";
				oss << " list.";
				testLogger.logEvent(oss.str(), OK);

				testLogger.printStatusMessage("Remove Test Passed.", OK);
				testLogger.logEvent("******* End Remove Test *******", INFO);
			}
		}
	}
	catch(...)
	{
		std::string errorMsg = "Unexpected exception occurred testing item"
					            " removal functionality.";
		testLogger.logEvent(errorMsg, FAIL);
		
		testLogger.printStatusMessage("Remove Test Failed.", FAIL);
		testLogger.logEvent("******* End Remove Test *******", INFO);
		
		testLogger.setPassingStatus(FAIL);
	}	
		
	return subTestStatus;		
}



//****************************************************************************
//	NAME: testRemoveFromHead.
//
//	DESCRIPTION: Test method that will attempt to remove items from the head
//				 of the list.  
//****************************************************************************

template <class U>
bool TestLinkedList<U>::testRemoveFromHead()
{
	testLogger.logEvent("******* Begin Remove-At-Head Test *******", INFO);
	
	int subTestStatus = -1;	
	try
	{
		U newHeadValue;
		std::ostringstream oss;
		
		oss << "Inserting " << newHeadValue << " at the head of the list.";
		testLogger.logEvent(oss.str(), INFO);
		oss.str("");
		oss.clear();
		
		testList.InsertAtHead(newHeadValue);
		if (newHeadValue == testList.getHeadValue())
		{
			oss << newHeadValue << " was successfully inserted at the head.";
			testLogger.logEvent(oss.str(), OK);
			oss.str("");
			oss.clear();
		}
		else
		{
			oss << newHeadValue << " was not inserted at the head.";
			testLogger.logEvent(oss.str(), FAIL);
			oss.str("");
			oss.clear();

			testLogger.printStatusMessage("Remove-At-Head Test Failed.", 
			                              FAIL);
			testLogger.logEvent("******* End Remove-At-Head Test *******", 
			                    INFO);	
			                    
			testLogger.setPassingStatus(FAIL);											
			return subTestStatus = FAIL;
		}
		
		oss << "Attempting to remove " << newHeadValue << " from the head.";
		testLogger.logEvent(oss.str(), INFO);
		
		testList.RemoveAtHead();

		if (newHeadValue != testList.getHeadValue())
		{
			oss.str("");
			oss.clear();
			oss << newHeadValue << " was removed from the head of the list.";
			testLogger.logEvent(oss.str(), INFO);

			testLogger.printStatusMessage("Remove-At-Head Test Passed.", OK);
			testLogger.logEvent("******* End Remove-At-Head Test *******", 
			                    INFO);
		}
		else
		{
			oss.str("");
			oss.clear();
			
			oss << newHeadValue << " is still at the head of the list.";
			testLogger.logEvent(oss.str(), INFO);
			
			subTestStatus = FAIL;
			
			testLogger.printStatusMessage("Remove-At-Head Test Failed.", 
			                              FAIL);
			testLogger.logEvent("******* End Remove-At-Head Test *******", 
			                    INFO);
			testLogger.setPassingStatus(FAIL);			
		}
	}
	catch(...)
	{
		std::string errorMsg = "Unexpected exception occurred testing remove"
					           " at the head functionality.";
		testLogger.logEvent(errorMsg, FAIL);
		
		testLogger.printStatusMessage("Remove-At-Head Test Failed.", FAIL);		
		testLogger.logEvent("******* End Remove-At-Head Test *******", INFO);
		
		testLogger.setPassingStatus(FAIL);
	}	
	
	return subTestStatus;  	
}



//****************************************************************************
//	NAME: testRemoveFromTail.
//
//	DESCRIPTION: Test method that will attempt to remove items from the tail
//				 of the list.   
//****************************************************************************

template <class U>
bool TestLinkedList<U>::testRemoveFromTail()
{
	testLogger.logEvent("******* Begin Remove-At-Tail Test *******", INFO);
	
	int subTestStatus = -1;	
	try
	{
		U newTailValue;
		std::ostringstream oss;
		
		oss << "Inserting " << newTailValue << " at the tail of the list.";
		testLogger.logEvent(oss.str(), INFO);
		oss.str("");
		oss.clear();
		
		testList.InsertAtTail(newTailValue);
		if (newTailValue == testList.getTailValue())
		{
			oss << newTailValue << " was successfully inserted at the tail.";
			testLogger.logEvent(oss.str(), OK);
			oss.str("");
			oss.clear();
		}
		else
		{
			oss << newTailValue << " was not inserted at the tail.";
			testLogger.logEvent(oss.str(), FAIL);
			oss.str("");
			oss.clear();

			testLogger.printStatusMessage("Remove-At-Tail Test Failed.", 
			                              FAIL);
			testLogger.logEvent("******* End Remove-At-Tail Test *******", 
			                    INFO);	
			                    
			testLogger.setPassingStatus(FAIL);											
			return subTestStatus = FAIL;
		}
		
		oss << "Attempting to remove " << newTailValue << " from the tail.";
		testLogger.logEvent(oss.str(), INFO);
		
		testList.RemoveAtTail();

		if (newTailValue != testList.getTailValue())
		{
			oss.str("");
			oss.clear();
			oss << newTailValue << " was removed from the tail of the list.";
			testLogger.logEvent(oss.str(), INFO);

			testLogger.printStatusMessage("Remove-At-Tail Test Passed.", OK);
			testLogger.logEvent("******* End Remove-At-Tail Test *******", 
			                    INFO);
		}
		else
		{
			oss.str("");
			oss.clear();
			
			oss << newTailValue << " is still at the tail of the list.";
			testLogger.logEvent(oss.str(), INFO);
			
			subTestStatus = FAIL;
			
			testLogger.printStatusMessage("Remove-At-Tail Test Failed.", 
			                              FAIL);
			testLogger.logEvent("******* End Remove-At-Tail Test *******", 
			                    INFO);
			testLogger.setPassingStatus(FAIL);			
		}
	}
	catch(...)
	{
		std::string errorMsg = "Unexpected exception occurred testing remove"
					           " at the tail functionality.";
		testLogger.logEvent(errorMsg, FAIL);
		
		testLogger.printStatusMessage("Remove-At-Tail Test Failed.", FAIL);		
		testLogger.logEvent("******* End Remove-At-Tail Test *******", INFO);
		
		testLogger.setPassingStatus(FAIL);
	}	
	
	return subTestStatus; 
}



//****************************************************************************
//	NAME: testEmptyListSearch.
//
//	DESCRIPTION: Test method that will attempt to search for a value in an
//				 empty list.  
//****************************************************************************

template <class U>
bool TestLinkedList<U>::testEmptyListSearch()
{
	testLogger.logEvent("******* Begin Empty List Search Test *******", INFO);
	try
	{
		std::ostringstream oss;
		U testValue;
		
		testLogger.logEvent("Clearing the list.", INFO);
		testList.Clear();
		
		oss << "Attempting to search the empty list for the value ";
		oss << testValue << ".";
		
		testLogger.logEvent(oss.str(), INFO);
		oss.str("");
		oss.clear();
		
		if (testList.Search(testValue))
		{
			testLogger.logEvent("Error, search method returned true.", FAIL);
			testLogger.printStatusMessage("Empty List Search Test Failed.", 
			                              FAIL);		
			testLogger.setPassingStatus(FAIL);	
		}
		else
		{
			oss << testValue << " was not found in the list.";
			testLogger.logEvent(oss.str(), FAIL);
			testLogger.printStatusMessage("Empty List Search Test Passed.",
			                              OK);		
		}
	}
	catch(...)
	{
		std::string errorMsg = "Unexpected exception occurred testing search"
					      " of an empty list.";
		testLogger.logEvent(errorMsg, FAIL);
		
		testLogger.printStatusMessage("Empty List Search Test Failed.", FAIL);
		testLogger.setPassingStatus(FAIL);			
	}
		
	testLogger.logEvent("******* End Empty List Search Test *******", INFO);
}



//****************************************************************************
//	NAME: testNotFoundSearch.
//
//	DESCRIPTION: Test method to search the list for a value that is not in
//				 the list.  
//****************************************************************************

template <class U>
bool TestLinkedList<U>::testNotFoundSearch()
{
	testLogger.logEvent("******* Begin Not Found in List Test *******", INFO);
	try
	{
		// Local Varaibles 
		U                  firstValue   = U(10);
		U                  secValue     = U(20);
		U                  thirdValue   = U(30);
		U                  fourthValue  = U(40);
		U                  fifthValue   = U(50);		
		U                  testValue    = U(100);
		std::ostringstream oss;		
		
		testLogger.logEvent("Clearing the list.", INFO);
		testList.Clear();
		
		testLogger.logEvent("Filling the list with default values.", INFO);
		testList.Insert(firstValue);
		testList.Insert(secValue);
		testList.Insert(thirdValue);
		testList.Insert(fourthValue);
		testList.Insert(fifthValue);
		
		oss << "Attempting to search the list for the value ";
		oss << testValue << ".";
		
		testLogger.logEvent(oss.str(), INFO);
		oss.str("");
		oss.clear();
		
		if (testList.Search(testValue))
		{
			testLogger.logEvent("Error, search method returned true.", FAIL);
			testLogger.printStatusMessage("Empty List Search Test Failed.", 
			                              FAIL);		
			testLogger.setPassingStatus(FAIL);	
		}
		else
		{
			oss << testValue << " was not found in the list.";
			testLogger.logEvent(oss.str(), FAIL);
			testLogger.printStatusMessage("Not Found in List Test Passed.",
			                              OK);		
		}
	}
	catch(...)
	{
		std::string errorMsg = "Unexpected exception occurred testing search"
					           " of a value that is not in the list.";
		testLogger.logEvent(errorMsg, FAIL);
		
		testLogger.printStatusMessage("Not Found in List Search Test Failed.",
		                              FAIL);
		testLogger.setPassingStatus(FAIL);			
	}
		
	testLogger.logEvent("******* End Not Found in List Test *******", INFO);
}



//****************************************************************************
//	NAME: testAtHeadSearch.
//
//	DESCRIPTION: Test method that will search for the head value of the list.
//****************************************************************************

template <class U>
bool TestLinkedList<U>::testAtHeadSearch()
{
	testLogger.logEvent("******* At-Head-Search Test *******", INFO);
	try
	{
		// Local Varaibles 
		U                  firstValue   = U(10);
		U                  secValue     = U(20);
		U                  thirdValue   = U(30);
		U                  fourthValue  = U(40);
		U                  fifthValue   = U(50);		
		std::ostringstream oss;		
		
		testLogger.logEvent("Clearing the list.", INFO);
		testList.Clear();
		
		testLogger.logEvent("Filling the list with default values.", INFO);
		testList.Insert(firstValue);
		testList.Insert(secValue);
		testList.Insert(thirdValue);
		testList.Insert(fourthValue);
		testList.Insert(fifthValue);
		
		oss << "Attempting to search the list for the head value: ";
		oss << testList.getHeadValue() << ".";
		
		testLogger.logEvent(oss.str(), INFO);
		oss.str("");
		oss.clear();
		
		if (testList.Search(testList.getHeadValue()))
		{
			oss << testList.getHeadValue() << " was found in the list!";
			testLogger.logEvent(oss.str(), OK);
			testLogger.printStatusMessage("At-Head-Search Test Passed.", 
			                              OK);			
		}
		else
		{
			oss << testList.getHeadValue() << " was not found in the list.";
			testLogger.logEvent(oss.str(), FAIL);
			testLogger.printStatusMessage("At-Head-Search Test Failed.",
			                              FAIL);	
			testLogger.setPassingStatus(FAIL);										  	
		}
	}
	catch(...)
	{
		std::string errorMsg = "Unexpected exception occurred testing search"
					           " at the head functionality.";
		testLogger.logEvent(errorMsg, FAIL);
		
		testLogger.printStatusMessage("At-Head-Search Test Failed.", FAIL);
		testLogger.setPassingStatus(FAIL);			
	}
		
	testLogger.logEvent("******* At-Head-Search Test *******", INFO);
}



//****************************************************************************
//	NAME: testAtTailSearch.
//
//	DESCRIPTION: Test method that will search for the tail value of the list.
//****************************************************************************

template <class U>
bool TestLinkedList<U>::testAtTailSearch()
{
	testLogger.logEvent("******* At-Tail-Search Test *******", INFO);
	try
	{
		// Local Varaibles 
		U                  firstValue   = U(10);
		U                  secValue     = U(20);
		U                  thirdValue   = U(30);
		U                  fourthValue  = U(40);
		U                  fifthValue   = U(50);		
		std::ostringstream oss;		
		
		testLogger.logEvent("Clearing the list.", INFO);
		testList.Clear();
		
		testLogger.logEvent("Filling the list with default values.", INFO);
		testList.Insert(firstValue);
		testList.Insert(secValue);
		testList.Insert(thirdValue);
		testList.Insert(fourthValue);
		testList.Insert(fifthValue);
		
		oss << "Attempting to search the list for the tail value: ";
		oss << testList.getTailValue() << ".";
		
		testLogger.logEvent(oss.str(), INFO);
		oss.str("");
		oss.clear();
		
		if (testList.Search(testList.getTailValue()))
		{
			oss << testList.getTailValue() << " was found in the list!";
			testLogger.logEvent(oss.str(), OK);
			testLogger.printStatusMessage("At-Tail-Search Test Passed.", 
			                              OK);			
		}
		else
		{
			oss << testList.getTailValue() << " was not found in the list.";
			testLogger.logEvent(oss.str(), FAIL);
			testLogger.printStatusMessage("At-Tail-Search Test Failed.",
			                              FAIL);	
			testLogger.setPassingStatus(FAIL);										  	
		}
	}
	catch(...)
	{
		std::string errorMsg = "Unexpected exception occurred testing search"
					           " at the tail functionality.";
		testLogger.logEvent(errorMsg, FAIL);
		
		testLogger.printStatusMessage("At-Tail-Search Test Failed.", FAIL);
		testLogger.setPassingStatus(FAIL);			
	}
		
	testLogger.logEvent("******* At-Tail-Search Test *******", INFO);
}



//****************************************************************************
//	NAME: testSearch.
//
//	DESCRIPTION: Test method that will insert values into the list, and 
//				 attempt to search for them.  If the item is detected, the 
//				 test will pass.  Otherwise, the test will fail. 
//****************************************************************************

template <class U>
bool TestLinkedList<U>::testSearch()
{
	testLogger.logEvent("******* Search List Test *******", INFO);
	try
	{
		// Local Varaibles 
		U                  firstValue   = U(10);
		U                  secValue     = U(20);
		U                  thirdValue   = U(30);
		U                  fourthValue  = U(40);
		U                  fifthValue   = U(50);		
		U                  testValue    = U(100);
		std::ostringstream oss;		
		
		testLogger.logEvent("Clearing the list.", INFO);
		testList.Clear();
		
		testLogger.logEvent("Filling the list with default values.", INFO);
		testList.Insert(firstValue);
		testList.Insert(secValue);
		testList.Insert(thirdValue);
		testList.Insert(fourthValue);
		testList.Insert(fifthValue);
		testList.Insert(testValue);
		
		oss << "Attempting to search the list for the value ";
		oss << testValue << ".";
		
		testLogger.logEvent(oss.str(), INFO);
		oss.str("");
		oss.clear();
		
		if (testList.Search(testValue))
		{
			oss << testValue << " was found in the list!";
			testLogger.logEvent(oss.str(), OK);
			testLogger.printStatusMessage("Search Test Passed.", 
			                              OK);			
		}
		else
		{
			oss << testValue << " was not found in the list.";
			testLogger.logEvent(oss.str(), FAIL);
			testLogger.printStatusMessage("Search List Test Failed.",
			                              FAIL);	
			testLogger.setPassingStatus(FAIL);										  	
		}
	}
	catch(...)
	{
		std::string errorMsg = "Unexpected exception occurred testing search"
					           " functionality.";
		testLogger.logEvent(errorMsg, FAIL);
		
		testLogger.printStatusMessage("Search Test Failed.", FAIL);
		testLogger.setPassingStatus(FAIL);			
	}
		
	testLogger.logEvent("******* Search List Test *******", INFO);
}
