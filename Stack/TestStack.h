//****************************************************************************
//	Header File for Test Stack
//	Programmed by: Houston Brown
//	Last Compiled Date: 11/3/2024
//****************************************************************************

#ifndef _TESTSTACK_H
#define _TESTSTACK_H

#include "Stack.h"
#include "Logger.h"

template <class U>
class TestStack
{
public: 
	TestStack();
	
	void runTests();
	int getMaxPossibleNodes();
	void printTestInfoHeader();
	
	bool testPush();
	bool bulkPush();
	
	bool testPop();
	bool bulkPop();
	
	bool testPeek();
	
	bool testEmptyStackSearch();
	bool testNotFoundSearch();
	bool testSearch();

private:
	Stack<U> testStack;  
	Logger testLogger;
};

#endif 
