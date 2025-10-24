//****************************************************************************
//	Header File for Queue Test
//	Programmed by: Houston Brown
//	Last Compiled Date: 10/25/2025
//****************************************************************************

#ifndef _TESTQUEUE_H
#define _TESTQUEUE_H

#include "Queue.h"
#include "Logger.h"

template <class U>
class TestQueue
{
public: 
	TestQueue();
	
	void runTests();
	int getMaxPossibleNodes();
	void printTestInfoHeader();
	
	bool testEnqueue();
	bool bulkEnqueue();
	
	bool testDequeue();
	bool bulkDequeue();
	
	bool testPeek();
	
	bool testEmptyQueueSearch();
	bool testNotFoundSearch();
	bool testSearch();

private:
	Queue<U> testQueue;  
	Logger testLogger;
};

#endif 
