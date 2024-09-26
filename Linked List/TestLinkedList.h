//****************************************************************************
//	Header File for Linked List Test
//	Programmed by: Houston Brown
//	Last Compiled Date: 1/15/2024
//****************************************************************************

#ifndef _TESTLINKEDLIST_H
#define _TESTLINKEDLIST_H

#include "LinkedList.h"
#include "Logger.h"

template <class U>
class TestLinkedList
{
public: 
	TestLinkedList();
	
	void runTests();
	bool bulkInsert();
	int getMaxPossibleListNodes();
	void printTestInfoHeader();
	
	bool testInOrderInsert();
	bool testInsertAtHead();
	bool testInsertAtTail();
	
	bool testRemove();
	bool testRemoveFromHead();
	bool testRemoveFromTail();
	
	bool testEmptyListSearch();
	bool testNotFoundSearch();
	bool testAtHeadSearch();
	bool testAtTailSearch();
	bool testSearch();

private:
	LinkedList<U> testList;  
	Logger testLogger;
};

#endif 
