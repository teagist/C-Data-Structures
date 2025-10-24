//****************************************************************************
//	Implementation File for Queue Test
//	Programmed by: Houston Brown
//	Last Compiled Date: 10/25/2025
//****************************************************************************

#include "TestQueue.h"

//****************************************************************************
//	CONSTRUCTOR.   
//****************************************************************************
template <class U>
TestQueue<U>::TestQueue()
{
	testLogger.setTest("Queue Test");
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
int TestQueue<U>::getMaxPossibleNodes()
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
		size_t maxObjs = status.ullTotalPhys / sizeof(QNode<U>);
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
void TestQueue<U>::printTestInfoHeader()
{
	try
	{
		std::string stars = "****************************************";
		std::cout << stars << stars << std::endl;
		testLogger.printLineHeader();
		std::cout << "Testing Validity of Queue Class." << std::endl;
		
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
void TestQueue<U>::runTests()
{
	WinUtils::clearScreen();
	printTestInfoHeader();
	std::cout << std::endl;
	
	int maxNodes = getMaxPossibleNodes();
	bool testStatus = false;
	try
	{
		if (bulkEnqueue())
		{			
			testDequeue();
			
			bulkDequeue();
			
			testPeek();
			
			testEmptyQueueSearch();
			
			testNotFoundSearch();
			
			testSearch();
		}
		else
		{
			std::cerr << "Unable to bulk load the queue." << std::endl;
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
//	NAME: bulkEnqueue.
//
//	DESCRIPTION: The purpose of this function is to load the queue with 100
//				 items.  
//****************************************************************************
template <class U>
bool TestQueue<U>::bulkEnqueue()
{
	int status = OK;
	
	testLogger.logEvent("***** Begin Bulk Enqueue Test *****", INFO);
	testLogger.logEvent("Attempting to Enqueue 100 items into the Queue", 
	                                                               INFO);
	WinUtils::wait(5);
	try
	{
		U   value;
		int numOfNodes = 0;
		int queueMax   = 100;
		
		while (numOfNodes < queueMax)
		{
			testQueue.Enqueue(value);
			numOfNodes = numOfNodes + 1;
		}
	}
	catch(...)
	{
		std::string errMsg = "Unexcpected error occurred while bulk "
		                     "inserting values into the queue.";
		testLogger.logEvent(errMsg, FAIL);
		status = FAIL;
	}

	if (status == OK)
	{
		testLogger.logEvent("Successfully added all items to the Queue", OK);
		WinUtils::wait(5);
	}
	
	if (status == OK && testQueue.Size() == 100)
	{
		testLogger.logEvent("Printing Queue of 100 items", INFO);
		testQueue.Print();
		testLogger.printStatusMessage("Bulk Enqueue Test Passed.", OK);
	}
	else
	{
		testLogger.printStatusMessage("Bulk Enqueue Test Failed.", FAIL);
	}

	
	testLogger.logEvent("***** Bulk Enqueue Test complete *****", INFO);
	testLogger.setPassingStatus(status);
	std::cout << std::endl;
	return status;
}

//****************************************************************************
//	NAME: testDequeue.
//
//	DESCRIPTION: This test will add items to the queue and test the dequeue
//				 functionality.  
//****************************************************************************
template <class U>
bool TestQueue<U>::testDequeue()
{
	testLogger.logEvent("***** Begin Dequeue Test *****", INFO);
	int status = OK;
	
	try
	{
		testLogger.logEvent("Clearing the queue before further testing.", 
		                                                           INFO);
		testQueue.~Queue();
		if (testQueue.Size() == 0)
		{
			testLogger.logEvent("Successfully cleared the queue.", OK);
		}
		else
		{
			testLogger.logEvent("Failed to destroy the queue.", FAIL);
			status = FAIL;
		}
	}
	catch(...)
	{
		std::string exMsg = "Unexpected exception occurred when attempting"
		                    " to destroy the queue.";
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
		testQueue.Enqueue(value1);
		testQueue.Enqueue(value2);
		testQueue.Enqueue(value3);
		
		testLogger.logEvent("Printing the queue.", INFO);
		std::cout << "\nQueue before dequeue" << std::endl;
		testQueue.Print();
		std::cout << std::endl;
		
		testLogger.logEvent("Removing the first value.", INFO);
		testQueue.Dequeue();
		WinUtils::wait(5);
		
		testLogger.logEvent("Printing the queue after dequeue.", INFO);
		std::cout << "\nQueue after dequeue" << std::endl;
		testQueue.Print();
		std::cout << std::endl;
		
		if (testQueue.Size() == 2)
		{
			testLogger.logEvent("Successfully dequeued.", OK);
		}
		else
		{
			testLogger.logEvent("Failed to dequeue.", FAIL);
			status = FAIL;
		}
	}
	catch(...)
	{
		std::string errMsg = "Unexpected exception caught while testing "
		                     "dequeue.";
		testLogger.logEvent(errMsg, FAIL);
		status = FAIL;
	}
	
	if (status == OK)
	{
		testLogger.printStatusMessage("Dequeue Passed.", OK);
	}
	else
	{
		testLogger.printStatusMessage("Dequeue Failed.", FAIL);
	}
	
	testLogger.logEvent("***** End Dequeue Test *****", INFO);
	testLogger.setPassingStatus(status);
	std::cout << std::endl;
	return status;
}

//****************************************************************************
//	NAME: bulkDequeue.
//
//	DESCRIPTION: Enqueue 100 items into the queue and then dequeue all items 
//				 from the queue. 
//****************************************************************************
template <class U>
bool TestQueue<U>::bulkDequeue()
{
	testLogger.logEvent("***** Begin Bulk Dequeue Test *****", INFO);
	int status = OK;
	
	try
	{
		testLogger.logEvent("Clearing the queue before further testing.", 
		                                                           INFO);
		testQueue.~Queue();
		if (testQueue.Size() == 0)
		{
			testLogger.logEvent("Successfully cleared the queue.", OK);
		}
		else
		{
			testLogger.logEvent("Failed to destroy the queue.", FAIL);
			status = FAIL;
		}
	}
	catch(...)
	{
		std::string exMsg = "Unexpected exception occurred when attempting"
		                    " to destroy the queue.";
		testLogger.logEvent(exMsg, FAIL);
		status = FAIL;
		testLogger.setPassingStatus(status);
	}
	
	try
	{
		U   value;
		int ctr      = 0;  
		int queueMax = 100;
		
		testLogger.logEvent("Enqueue 100 items to the queue.", INFO);
		WinUtils::wait(5);
		while (ctr < queueMax)
		{
			testQueue.Enqueue(value);
			ctr = ctr + 1;
		}
		
		testLogger.logEvent("Dequeue 100 items from the queue.", INFO);
		ctr = 0;
		while (ctr < queueMax)
		{
			testQueue.Dequeue();
			ctr = ctr + 1;
		}
		
		if (testQueue.Size() == 0)
		{
			testLogger.logEvent("Successfully dequeued 100 items.", OK);
		}
		else
		{
			testLogger.logEvent("Failed to dequeue 100 items", FAIL);
		}
	}
	catch(...)	
	{
		std::string errMsg = "Unexpected exception caught while testing "
		                     "bulk dequeue.";
		testLogger.logEvent(errMsg, FAIL);
		status = FAIL;
	}
	
	if (status == OK)
	{
		testLogger.printStatusMessage("Bulk Dequeue Passed.", OK);
	}
	else
	{
		testLogger.printStatusMessage("Bulk Dequeue Failed.", FAIL);
	}
	
	testLogger.logEvent("***** End Bulk Dequeue Test *****", INFO);
	testLogger.setPassingStatus(status);
	std::cout << std::endl;
	return status;	
}

//****************************************************************************
//	NAME: testPeek.
//
//	DESCRIPTION: Enqueue several items into the queue and test that the peek
//				 function returns the correct values.    
//****************************************************************************
template <class U>
bool TestQueue<U>::testPeek()
{
	testLogger.logEvent("***** Begin Peek Test *****", INFO);
	int status = OK;
	
	try
	{
		testLogger.logEvent("Clearing the queue before further testing.", 
		                                                           INFO);
		testQueue.~Queue();
		if (testQueue.Size() == 0)
		{
			testLogger.logEvent("Successfully cleared the queue.", OK);
		}
		else
		{
			testLogger.logEvent("Failed to destroy the queue.", FAIL);
			status = FAIL;
		}
	}
	catch(...)
	{
		std::string exMsg = "Unexpected exception occurred when attempting"
		                    " to destroy the queue.";
		testLogger.logEvent(exMsg, FAIL);
		status = FAIL;
		testLogger.setPassingStatus(status);
	}
	
	try
	{
		testLogger.logEvent("Adding 3 values to the queue.", OK);
		U value1;
		U value2;
		U value3;
		
		testQueue.Enqueue(value1);
		testQueue.Enqueue(value2);
		testQueue.Enqueue(value3);
		
		testLogger.logEvent("Peeking the queue...", INFO);
		if (testQueue.Peek() == value1)
		{
			std::string passMsg = "Peek was equal to the front of the queue.";
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
	}
	
	if (status == OK)
	{
		testLogger.printStatusMessage("Peek Passed.", OK);
	}
	else
	{
		testLogger.printStatusMessage("Peek Failed.", FAIL);
	}
	
	testLogger.logEvent("***** End Peek Test *****", INFO);
	testLogger.setPassingStatus(status);
	std::cout << std::endl;
	return status;
}

//****************************************************************************
//	NAME: testEmptyQueueSearch.
//
//	DESCRIPTION: Clear the queue and attempt to search for values in the
//				 queue. 
//****************************************************************************
template <class U>
bool TestQueue<U>::testEmptyQueueSearch()
{
	testLogger.logEvent("***** Begin Empty Queue Search Test *****", INFO);
	int status = OK;
	
	try
	{
		testLogger.logEvent("Clearing the queue before further testing.", 
		                                                           INFO);
		testQueue.~Queue();
		if (testQueue.Size() == 0)
		{
			testLogger.logEvent("Successfully cleared the queue.", OK);
		}
		else
		{
			testLogger.logEvent("Failed to destroy the queue.", FAIL);
			status = FAIL;
		}
	}
	catch(...)
	{
		std::string exMsg = "Unexpected exception occurred when attempting"
		                    " to destroy the queue.";
		testLogger.logEvent(exMsg, FAIL);
		status = FAIL;
		testLogger.setPassingStatus(status);
	}
	
	try
	{
		if (status == OK && testQueue.Size() == 0)
		{
			testLogger.logEvent("Attempting to search empty queue...", INFO);
			WinUtils::wait(5);
			
			U value;
			if (testQueue.Search(value))
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
			                      " the queue.";
			testLogger.logEvent(failMsg, FAIL);
			status = FAIL;
		}
	}
	catch(...)
	{
		std::string errMsg = "Unexpected exception caught while testing"
		                     " search of an empty queue.";
		testLogger.logEvent(errMsg, FAIL);
		status = FAIL;
	}
	
	if (status == OK)
	{
		testLogger.printStatusMessage("Empty Queue Search Passed.", OK);
	}
	else
	{
		testLogger.printStatusMessage("Empty Queue Search Failed.", FAIL);
	}
	
	testLogger.logEvent("***** End Empty Queue Search Test *****", INFO);
	testLogger.setPassingStatus(status);
	std::cout << std::endl;
	return status;	
}

//****************************************************************************
//	NAME: testNotFoundSearch.
//
//	DESCRIPTION: Enqueue several items into the queue and search for values
//				 not in the queue.  
//****************************************************************************
template <class U>
bool TestQueue<U>::testNotFoundSearch()
{
	testLogger.logEvent("***** Begin Not Found Search Test *****", INFO);
	int status = OK;
	
	try
	{
		testLogger.logEvent("Clearing the queue before further testing.", 
		                                                           INFO);
		testQueue.~Queue();
		if (testQueue.Size() == 0)
		{
			testLogger.logEvent("Successfully cleared the queue.", OK);
		}
		else
		{
			testLogger.logEvent("Failed to destroy the queue.", FAIL);
			status = FAIL;
		}
	}
	catch(...)
	{
		std::string exMsg = "Unexpected exception occurred when attempting"
		                    " to destroy the queue.";
		testLogger.logEvent(exMsg, FAIL);
		status = FAIL;
		testLogger.setPassingStatus(status);
	}
	
	try
	{
		U value1;
		U value2;
		
		testLogger.logEvent("Adding value to the queue.", INFO);
		testQueue.Enqueue(value1);
		
		testLogger.logEvent("Searching for item not in queue...", INFO);
		WinUtils::wait(5);
		
		if (testQueue.Search(value2))
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
		                     " invalid search of a queue.";
		testLogger.logEvent(errMsg, FAIL);
		status = FAIL;		
	}
	
	if (status == OK)
	{
		testLogger.printStatusMessage("Not Found Search Passed.", OK);
	}
	else
	{
		testLogger.printStatusMessage("Not Found Search Failed.", FAIL);
	}
	
	testLogger.logEvent("***** End Not Found Search Test *****", INFO);
	testLogger.setPassingStatus(status);
	std::cout << std::endl;
	return status;		
}

//****************************************************************************
//	NAME: testSearch.
//
//	DESCRIPTION: Enqueue items into the list and seach for those same values
//				 to determine if the search function will return 
//				 successfully.  
//****************************************************************************
template <class U>
bool TestQueue<U>::testSearch()
{
	testLogger.logEvent("***** Begin Successful Search Test *****", INFO);
	int status = OK;
	
	try
	{
		testLogger.logEvent("Clearing the queue before further testing.", 
		                                                           INFO);
		testQueue.~Queue();
		if (testQueue.Size() == 0)
		{
			testLogger.logEvent("Successfully cleared the queue.", OK);
		}
		else
		{
			testLogger.logEvent("Failed to destroy the queue.", FAIL);
			status = FAIL;
		}
	}
	catch(...)
	{
		std::string exMsg = "Unexpected exception occurred when attempting"
		                    " to destroy the queue.";
		testLogger.logEvent(exMsg, FAIL);
		status = FAIL;
		testLogger.setPassingStatus(status);
	}
	
	try
	{
		U value1;
		U value2;
		U value3;
		
		testLogger.logEvent("Adding 3 values to the queue.", INFO);
		WinUtils::wait(5);
		
		testQueue.Enqueue(value1);
		testQueue.Enqueue(value2);
		testQueue.Enqueue(value3);
		
		testLogger.logEvent("Searching queue for valid item...", INFO);
		WinUtils::wait(5);
		if (testQueue.Search(value1))
		{
			testLogger.logEvent("Item was found in the queue!", OK);
		}
		else
		{
			testLogger.logEvent("Item was not found in the queue", FAIL);
		}
	}
	catch(...)
	{
		std::string errMsg = "Unexpected exception caught while testing"
		                     " search functionality.";
		testLogger.logEvent(errMsg, FAIL);
		status = FAIL;		
	}
	
	if (status == OK)
	{
		testLogger.printStatusMessage("Successful Search Passed.", OK);
	}
	else
	{
		testLogger.printStatusMessage("Successful Search Failed.", FAIL);
	}	
	
	testLogger.logEvent("***** End Successful Search  Test *****", INFO);
	testLogger.setPassingStatus(status);
	std::cout << std::endl;
	return status;
}
