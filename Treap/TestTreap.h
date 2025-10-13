//****************************************************************************
//	Header File for Treap Test.
//	Programmed by: Houston Brown.
//	Last Compiled Date: 10/12/2025
//****************************************************************************

#ifndef _TESTTEAP_H
#define _TESTTEAP_H

#include "Treap.h"
#include "Logger.h"
#include <vector>
#include <random>
#include <chrono>
#include <set>
#include <unordered_set>
using namespace std::chrono;

template <class U>
class TestTreap
{
public:
	TestTreap();
	
	void printTestInfoHeader();
	int getMaxPossibleNodes();
	void runTests();

	bool testInsert();
	bool testDelete();
	bool bulkInsert();

	bool testEmptyTreapSearch();
	bool testNotFoundSearch();
	bool testAtRootSearch();
	bool testSearch();

	void benchmarkTreap(const vector<int>& data, const vector<int>& queries);
	void benchmarkSet(const vector<int>& data, const vector<int>& queries);
	void benchmarkUnorderedSet(const vector<int>& data, const vector<int>& queries);
	bool runBenchmarkTest();

private:
	Treap<U> testTreap;
	Logger testLogger;
};

#endif 