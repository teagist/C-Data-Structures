//****************************************************************************
//	Implementation File for Treap Test.
//	Programmed by: Houston Brown.
//	Last Compiled Date: 10/12/2025
//****************************************************************************

#include "TestTreap.h"

//****************************************************************************
//	CONSTRUCTOR.   
//****************************************************************************
template <class U>
TestTreap<U>::TestTreap()
{
    testLogger.setTest("Treap Test");
    testLogger.setVersion("1.00.00.01");
    testLogger.setTitlebar();
}

//****************************************************************************
//  NAME: printTestInfoHeader.
//
//  DESCRIPTION: Print the preamble of the test.
// 
//  PARAMETERS:  
//****************************************************************************
template <class U>
void TestTreap<U>::printTestInfoHeader()
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
    catch (...)
    {
        std::cerr << "Error retrieving test info." << std::endl;
    }
}

//****************************************************************************
//  NAME: getMaxPossibleNodes.
//
//  DESCRIPTION: Return the max number of possible nodes that can be 
//               allocated.
// 
//  PARAMETERS: N/A.
//****************************************************************************
template <class U>
int TestTreap<U>::getMaxPossibleNodes()
{
    try
    {
        MEMORYSTATUSEX status;
        status.dwLength = sizeof(status);
        GlobalMemoryStatusEx(&status);

        testLogger.logEvent("  Memory Check", INFO);
        testLogger.logEvent("Total physical memory: " + std::to_string(status.ullTotalPhys) + " bytes.", INFO);
        testLogger.logEvent("The size of a TreapNode is: " + std::to_string(sizeof(TreapNode<U>)) + " bytes.", INFO);

        size_t maxObjs = status.ullTotalPhys / sizeof(TreapNode<U>);
        testLogger.logEvent("The total number of possible Treap Nodes is: " + std::to_string(maxObjs), INFO);
        testLogger.logEvent("", INFO);

        return maxObjs;
    }
    catch (...)
    {
        testLogger.logEvent("Unexpected error when retreiving max number of "
            "objects.", FAIL);
    }
    return 0;
}

//****************************************************************************
//  NAME: runTests.
//
//  DESCRIPTION: This method will run all of the subtests for the treap.
// 
//  PARAMETERS: N/A.
//****************************************************************************
template <class U>
void TestTreap<U>::runTests()
{
    printTestInfoHeader();
    std::cout << std::endl;
    int maxNodes = getMaxPossibleNodes();
    bool testStatus = false;

    try
    {
        testLogger.logEvent("******* Beginning Preliminary Tests *******", INFO);
        testInsert();
        std::cout << std::endl;

        testDelete();
        std::cout << std::endl;

        testEmptyTreapSearch();
        std::cout << std::endl;

        testNotFoundSearch();
        std::cout << std::endl;

        testAtRootSearch();
        std::cout << std::endl;

        testSearch();
        testLogger.logEvent("******* End Preliminary Tests *******", INFO);
        std::cout << std::endl;

        runBenchmarkTest();
    }
    catch (...)
    {
        testLogger.printStatusMessage("Unexpected exception caught while running Treap tests.", FAIL);
    }

    testLogger.printResult();
}

//****************************************************************************
//  NAME: testInsert.
//
//  DESCRIPTION: Ensure that the treap is clear, and attempt to insert an
//               item into it.  Verify that the insertion occurred as 
//               expected.
// 
//  PARAMETERS: N/A.
//****************************************************************************
template <class U>
bool TestTreap<U>::testInsert()
{
    testLogger.logEvent("******* Begin Insert Test *******", INFO);

    try
    {
        U testValue = U(45518);

        testLogger.logEvent("Clearing the Treap.", INFO);
        testTreap.Clear();

        testLogger.logEvent("Inserting " + std::to_string(testValue) + " into the treap.", INFO);
        testTreap.Insert(testValue);

        testLogger.logEvent("Searching the treap for " + std::to_string(testValue) + ".", INFO);
        if (testTreap.Search(testValue))
        {
            testLogger.logEvent(std::to_string(testValue) + " was found in the Treap.", OK);
            testLogger.printStatusMessage("Insert Test Passed.", OK);
        }
        else
        {
            testLogger.logEvent("Error, search method returned false.", FAIL);
            testLogger.printStatusMessage("Insert Test Failed.", FAIL);
            testLogger.setPassingStatus(FAIL);
        }
    }
    catch (...)
    {
        testLogger.logEvent("Unexpected exception caught during the Insert Test.", FAIL);
        testLogger.setPassingStatus(FAIL);
    }

    testLogger.logEvent("", INFO);
    testLogger.logEvent("******* End Insert Test *******", INFO);
    return false;
}

//****************************************************************************
//  NAME: testDelete.
//
//  DESCRIPTION: Fill the treap with values and attempt to delete and item.
//               Ensure that the removal occurred as expected.
// 
//  PARAMETERS: N/A.
//****************************************************************************
template <class U>
bool TestTreap<U>::testDelete()
{
    testLogger.logEvent("******* Begin Delete Test *******", INFO);

    try
    {
        U testValue = U(45518);

        testLogger.logEvent("Clearing the Treap.", INFO);
        testTreap.Clear();

        testLogger.logEvent("Inserting " + std::to_string(testValue) + " into the treap.", INFO);
        testTreap.Insert(testValue);

        testLogger.logEvent("Deleting " + std::to_string(testValue) + " from the treap.", INFO);
        testTreap.Delete(testValue);

        testLogger.logEvent("Searching the treap for " + std::to_string(testValue) + ".", INFO);
        if (testTreap.Search(testValue))
        {
            testLogger.logEvent(std::to_string(testValue) + " was found in the Treap.", FAIL);
            testLogger.printStatusMessage("Delete Test Failed.", FAIL);
            testLogger.setPassingStatus(FAIL);
        }
        else
        {
            testLogger.logEvent(std::to_string(testValue) + " was not found in the Treap.", OK);
            testLogger.printStatusMessage("Delete Test Passed.", OK);
        }
    }
    catch (...)
    {
        testLogger.logEvent("Unexpected exception caught during the Delete Test.", FAIL);
        testLogger.setPassingStatus(FAIL);
    }

    testLogger.logEvent("", INFO);
    testLogger.logEvent("******* End Delete Test *******", INFO);
    return false;
}

//****************************************************************************
//  NAME: bulkInsert.
//
//  DESCRIPTION: Load the Treap with 100 items.
// 
//  PARAMETERS: N/A.
//****************************************************************************
template <class U>
bool TestTreap<U>::bulkInsert()
{
    int status = OK;

    try
    {
        U value;
        int numOfNodes = 0;
        int itemMax = 100;

        mt19937 rng(static_cast<unsigned int>(steady_clock::now().time_since_epoch().count()));
        uniform_int_distribution<int> dist(1, itemMax);

        while (numOfNodes < itemMax)
        {
            testTreap.Insert(dist(rng));
            numOfNodes = numOfNodes + 1;
        }
    }
    catch (...)
    {
        testLogger.logEvent("Unexcpected error occurred while bulk inserting values"
            " into the treap.", FAIL);
        status = FAIL;
    }

    return status;
}

//****************************************************************************
//  NAME: testEmptyTreapSearch.
//
//  DESCRIPTION: Clear the contents of the treap and ensure that the search
//               function will return false for searching an empty treap.
// 
//  PARAMETERS: N/A.
//****************************************************************************
template <class U>
bool TestTreap<U>::testEmptyTreapSearch()
{
    testLogger.logEvent("******* Begin Empty Treap Search Test *******", INFO);
    try
    {
        std::ostringstream oss;
        U testValue = U(10);

        testLogger.logEvent("Clearing the Treap.", INFO);
        testTreap.Clear();

        oss << "Attempting to search the empty treap for the value ";
        oss << testValue << ".";

        testLogger.logEvent(oss.str(), INFO);
        oss.str("");
        oss.clear();

        if (testTreap.Search(testValue))
        {
            testLogger.logEvent("Error, search method returned true.", FAIL);
            testLogger.printStatusMessage("Empty Treap Search Test Failed.", FAIL);
            testLogger.setPassingStatus(FAIL);
        }
        else
        {
            oss << testValue << " was not found in the Treap.";
            testLogger.logEvent(oss.str(), FAIL);
            testLogger.printStatusMessage("Empty Treap Search Test Passed.", OK);
        }
    }
    catch (...)
    {
        testLogger.logEvent("Unexpected exception occurred testing search of an empty treap.", FAIL);
        testLogger.printStatusMessage("Empty Treap Search Test Failed.", FAIL);
        testLogger.setPassingStatus(FAIL);
    }

    testLogger.logEvent("", INFO);
    testLogger.logEvent("******* End Empty Treap Search Test *******", INFO);
    return true;
}

//****************************************************************************
//  NAME: testNotFoundSearch.
//
//  DESCRIPTION: Load the treap with somve values and ensure that the search
//               method will return false for an item not present in the 
//               treap.
// 
//  PARAMETERS: N/A.
//****************************************************************************
template <class U>
bool TestTreap<U>::testNotFoundSearch()
{
    testLogger.logEvent("******* Begin Not Found in Treap Test *******", INFO);
    try
    {
        // Local Varaibles 
        U                  firstValue = U(10);
        U                  secValue = U(20);
        U                  thirdValue = U(30);
        U                  fourthValue = U(40);
        U                  fifthValue = U(50);
        U                  testValue = U(100);
        std::ostringstream oss;

        testLogger.logEvent("Clearing the treap.", INFO);
        testTreap.Clear();

        testLogger.logEvent("Filling the treap with default values.", INFO);
        testTreap.Insert(firstValue);
        testTreap.Insert(secValue);
        testTreap.Insert(thirdValue);
        testTreap.Insert(fourthValue);
        testTreap.Insert(fifthValue);

        oss << "Attempting to search the treap for the value ";
        oss << testValue << ".";

        testLogger.logEvent(oss.str(), INFO);
        oss.str("");
        oss.clear();

        if (testTreap.Search(testValue))
        {
            testLogger.logEvent("Error, search method returned true.", FAIL);
            testLogger.printStatusMessage("Item not found Test Failed.", FAIL);
            testLogger.setPassingStatus(FAIL);
        }
        else
        {
            oss << testValue << " was not found in the treap.";
            testLogger.logEvent(oss.str(), FAIL);
            testLogger.printStatusMessage("Not Found in Treap Test Passed.", OK);
        }
    }
    catch (...)
    {
        testLogger.logEvent("Unexpected exception occurred testing search"
            " of a value that is not in the treap.", FAIL);

        testLogger.printStatusMessage("Not Found in Treap Search Test Failed.", FAIL);
        testLogger.setPassingStatus(FAIL);
    }

    testLogger.logEvent("", INFO);
    testLogger.logEvent("******* End Not Found in Treap Test *******", INFO);
    return true;
}

//****************************************************************************
//  NAME: testAtRootSearch.
//
//  DESCRIPTION: Clear the contents of the treap, insert one item, and 
//               search for it to ensure that the search method works 
//               properly.
// 
//  PARAMETERS: N/A.
//****************************************************************************
template <class U>
bool TestTreap<U>::testAtRootSearch()
{
    testLogger.logEvent("******* Begin At Root Search Test *******", INFO);

    try
    {
        U testValue = U(45518);

        testLogger.logEvent("Clearing the Treap.", INFO);
        testTreap.Clear();

        testLogger.logEvent("Inserting " + std::to_string(testValue) + " into the treap.", INFO);
        testTreap.Insert(testValue);

        testLogger.logEvent("Searching the treap for " + std::to_string(testValue) + ".", INFO);
        if (testTreap.Search(testValue))
        {
            testLogger.logEvent(std::to_string(testValue) + " was found in the Treap.", OK);
            testLogger.printStatusMessage("At Root Search Test Passed.", OK);
        }
        else
        {
            testLogger.logEvent("Error, search method returned false.", FAIL);
            testLogger.printStatusMessage("At Root Search Test Failed.", FAIL);
            testLogger.setPassingStatus(FAIL);
        }
    }
    catch (...)
    {
        testLogger.logEvent("Unexpected exception caught during the At Root Search Test.", FAIL);
        testLogger.setPassingStatus(FAIL);
    }

    testLogger.logEvent("", INFO);
    testLogger.logEvent("******* End At Root Search Test *******", INFO);
    return false;
}

//****************************************************************************
//  NAME: testSearch.
//
//  DESCRIPTION: Load the treap with values, and search for leaf values to 
//               ensure the search method is working properly.
// 
//  PARAMETERS: N/A.
//****************************************************************************
template <class U>
bool TestTreap<U>::testSearch()
{
    testLogger.logEvent("******* Begin Search Test *******", INFO);

    try
    {
        U testValue = U(45518);

        testLogger.logEvent("Clearing the Treap.", INFO);
        testTreap.Clear();

        testLogger.logEvent("Loading 100 items into the treap.", INFO);
        bulkInsert();

        testLogger.logEvent("Inserting " + std::to_string(testValue) + " into the treap.", INFO);
        testTreap.Insert(testValue);

        testLogger.logEvent("Searching the treap.", INFO);
        if (testTreap.Search(testValue))
        {
            testLogger.logEvent(std::to_string(testValue) + " was found in the Treap.", OK);
            testLogger.printStatusMessage("Search Test Passed.", OK);
        }
        else
        {
            testLogger.logEvent("Error, search method returned false.", FAIL);
            testLogger.printStatusMessage("Search Test Failed.", FAIL);
            testLogger.setPassingStatus(FAIL);
        }
    }
    catch (...)
    {
        testLogger.logEvent("Unexpected exception caught during the Search Test.", FAIL);
        testLogger.setPassingStatus(FAIL);
    }

    testLogger.logEvent("", INFO);
    testLogger.logEvent("******* End Search Test *******", INFO);
    return false;
}

//****************************************************************************
//  NAME: benchmarkTreap.
//
//  DESCRIPTION: Attempt to insert 100,000 entries into a treap and record 
//               the time it takes.  Additionally, search the unordered set 
//               10,000 times and record the time that it takes and display 
//               all results.
// 
//  PARAMETERS: data: vector of values to be inserted.
//              queries: vector of values to be searched for.
//****************************************************************************
template <class U>
void TestTreap<U>::benchmarkTreap(const vector<int>& data, const vector<int>& queries)
{
    testLogger.logEvent("Inserting 100,000 entries into the treap.", INFO);

    std::chrono::steady_clock::time_point start = high_resolution_clock::now();
    for (int x = 0; x < data.size(); x++)
    {
        testTreap.Insert(x);
    }
    std::chrono::steady_clock::time_point end = high_resolution_clock::now();
    long long  insert_time = duration_cast<milliseconds>(end - start).count();

    testLogger.logEvent("Searching for entries in the treap to record search time.", INFO);

    start = high_resolution_clock::now();
    int foundCount = 0;
    for (int q = 0; q < queries.size(); q++)
    {
        if (testTreap.Search(q))
        {
            foundCount++;
        }
    }

    end = high_resolution_clock::now();
    long long search_time = duration_cast<milliseconds>(end - start).count();

    std::cout << "          Treap: " << std::endl;
    std::cout << "                Insert time = " << insert_time << " ms." << std::endl;
    std::cout << "                Search time = " << search_time << " ms." << std::endl;
    std::cout << "                Found = " << foundCount << "." << std::endl << std::endl;
}

//****************************************************************************
//  NAME: benchmarkSet.
//
//  DESCRIPTION: Attempt to insert 100,000 entries into a set and record the 
//               time it takes.  Additionally, search the unordered set 
//               10,000 times and record the time that it takes and display 
//               all results.
// 
//  PARAMETERS: data: vector of values to be inserted.
//              queries: vector of values to be searched for.
//****************************************************************************
template <class U>
void TestTreap<U>::benchmarkSet(const vector<int>& data, const vector<int>& queries)
{
    set<int> st;

    std::chrono::steady_clock::time_point start = high_resolution_clock::now();
    for (int x = 0; x < data.size(); x++)
    {
        st.insert(x);
    }
    std::chrono::steady_clock::time_point end = high_resolution_clock::now();
    long long  insert_time = duration_cast<milliseconds>(end - start).count();

    start = high_resolution_clock::now();

    int foundCount = 0;
    for (int q = 0; q < queries.size(); q++)
    {
        if (st.find(q) != st.end())
        {
            foundCount++;
        }
    }

    end = high_resolution_clock::now();
    long long search_time = duration_cast<milliseconds>(end - start).count();

    std::cout << "            Set: " << std::endl;
    std::cout << "                Insert time = " << insert_time << " ms." << std::endl;
    std::cout << "                Search time = " << search_time << " ms." << std::endl;
    std::cout << "                Found = " << foundCount << "." << std::endl << std::endl;
}

//****************************************************************************
//  NAME: benchmarkUnorderedSet.
//
//  DESCRIPTION: Attempt to insert 100,000 entries into an unordered set and
//               record the time it takes.  Additionally, search the 
//               unordered set 10,000 times and record the time that it 
//               takes and display all results.
// 
//  PARAMETERS: data: vector of values to be inserted.
//              queries: vector of values to be searched for.
//****************************************************************************
template <class U>
void TestTreap<U>::benchmarkUnorderedSet(const vector<int>& data, const vector<int>& queries)
{
    unordered_set<int> ust;

    std::chrono::steady_clock::time_point start = high_resolution_clock::now();
    for (int x = 0; x < data.size(); x++)
    {
        ust.insert(x);
    }
    std::chrono::steady_clock::time_point end = high_resolution_clock::now();
    long long insert_time = duration_cast<milliseconds>(end - start).count();

    start = high_resolution_clock::now();

    int foundCount = 0;
    for (int q = 0; q < queries.size(); q++)
    {
        if (ust.find(q) != ust.end())
        {
            foundCount++;
        }
    }

    end = high_resolution_clock::now();
    long long search_time = duration_cast<milliseconds>(end - start).count();

    std::cout << "  Unordered Set: " << std::endl;
    std::cout << "                Insert time = " << insert_time << " ms." << std::endl;
    std::cout << "                Search time = " << search_time << " ms." << std::endl;
    std::cout << "                Found = " << foundCount << "." << std::endl << std::endl;
}

//****************************************************************************
//  NAME: runBenchmarkTest.
//
//  DESCRIPTION: Run the benchmark comparisons of the Treap, set, and 
//               unordered set structures and display their insertion and
//               search results.
// 
//  PARAMETERS: N/A.
//****************************************************************************
template <class U>
bool TestTreap<U>::runBenchmarkTest()
{
    testLogger.logEvent("******* Begin Benchmark Test *******", INFO);
    int subTestStatus = -1;

    try
    {
        testLogger.logEvent("Clearing the treap.", INFO);
        testTreap.Clear();

        const int DATA_SIZE = 100000;
        const int QUERY_SIZE = 10000;

        vector<int> data;
        vector<int> queries;

        mt19937 rng(static_cast<unsigned int>(steady_clock::now().time_since_epoch().count()));
        uniform_int_distribution<int> dist(1, DATA_SIZE * 10);

        for (int i = 0; i < DATA_SIZE; ++i)
        {
            data.push_back(dist(rng));
        }
        for (int i = 0; i < QUERY_SIZE; ++i)
        {
            queries.push_back(dist(rng));
        }

        testLogger.logEvent("Benchmarking with " + std::to_string(DATA_SIZE) +
            " insertions and " + std::to_string(QUERY_SIZE) +
            " searches...", INFO);

        benchmarkTreap(data, queries);
        benchmarkSet(data, queries);
        benchmarkUnorderedSet(data, queries);

        testLogger.printStatusMessage("Benchmark Test Passed.", OK);
    }
    catch (...)
    {
        testLogger.logEvent("Unexpected exception occurred testing item "
            "removal functionality.", FAIL);

        testLogger.printStatusMessage("Benchmark Test Failed.", FAIL);
        testLogger.setPassingStatus(FAIL);
    }

    testLogger.logEvent("", INFO);
    testLogger.logEvent("******* End Benchmark Test *******", INFO);
    return subTestStatus;
}