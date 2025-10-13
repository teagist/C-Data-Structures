//****************************************************************************
//	Implementation File for Logger Class.
//	Programmed by: Houston Brown.
//	Last Compiled Date: 10/12/2025
//****************************************************************************

#include "Logger.h"

//****************************************************************************
//	CONSTRUCTOR.
//****************************************************************************
Logger::Logger(std::string newTest, std::string newVersion)
{
	m_test = newTest;
	m_version = newVersion;
	m_isPassing = true;

	/*std::time_t t = std::time(nullptr);
	std::tm* now = std::localtime(&t);

	// Format the date as YYYYMMDD
	std::stringstream date_stream;
	date_stream << (now->tm_year + 1900); // Year since 1900
	date_stream << std::setw(2) << std::setfill('0') << (now->tm_mon + 1);
	date_stream << std::setw(2) << std::setfill('0') << now->tm_mday;
	std::string date_str = date_stream.str();

	std::string fileName = "log_file" + date_str + ".txt";
	logFile.open(fileName);*/
}

//****************************************************************************
//	SETTER FOR TEST NAME.
//****************************************************************************
void Logger::setTest(std::string newTest)
{
	m_test = newTest;
}

//****************************************************************************
//	SETTER FOR VERSION NAME.
//****************************************************************************
void Logger::setVersion(std::string newVersion)
{
	m_version = newVersion;
}

//****************************************************************************
//	SETTER FOR PASSING/FAILING STATUS.
//****************************************************************************
void Logger::setPassingStatus(bool isSuccess)
{
	m_isPassing = isSuccess;

	setTitlebar();
}

//****************************************************************************
//	NAME: readVersionInfo.
//
//	DESCRIPTION: Reads the version information from the text file.  If the
//				 version file cannot be found, then the program terminates.  
// 
//  PARAMETERS: N/A.
//****************************************************************************
void Logger::readVersionInfo()
{
	try
	{
		std::ifstream infile("versionInfo.txt");

		if (infile.fail())
		{
			printStatusMessage("Version infomation file unable to be read", 1);
			setPassingStatus(false);
			setTitlebar();
			printResult();
			exit(1);
		}
		else
		{
			std::getline(infile, m_test);
			std::getline(infile, m_version);
		}
	}
	catch (...)
	{
		logEvent("Unexpected exception caught while attempting to read version info." ,FAIL);
	}
}

//****************************************************************************
//  NAME: printStatusMessage.
//
//  DESCRIPTION: Method to print the status message contained in the message
//				 string.  If the status is 0, then a "success" tag will be
//				 displayed.  If the status is 1, and "error" tag will be 
//				 displayed.  
// 
//  PARAMETERS:  message: The status message to be displayed.
//               status:  Success/Error value.
//****************************************************************************
void Logger::printStatusMessage(const std::string& message,
	const int& status) const
{
	if (status == OK)
	{
		printLineHeader();
		std::cout << " ";

		HANDLE hConsole;
		CONSOLE_SCREEN_BUFFER_INFO myBuffInfo;

		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		GetConsoleScreenBufferInfo(hConsole, &myBuffInfo);
		SetConsoleTextAttribute(hConsole, 47);

		std::cout << "  Success  ";
		SetConsoleTextAttribute(hConsole, myBuffInfo.wAttributes);
		std::cout << "  " << message << std::endl;
	}
	else if (status == FAIL)
	{
		printLineHeader();
		std::cout << " ";

		HANDLE hConsole;
		CONSOLE_SCREEN_BUFFER_INFO myBuffInfo;

		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		GetConsoleScreenBufferInfo(hConsole, &myBuffInfo);
		SetConsoleTextAttribute(hConsole, 79);

		std::cout << "  Error  ";
		SetConsoleTextAttribute(hConsole, myBuffInfo.wAttributes);
		std::cout << "  " << message << std::endl;
	}
}

//****************************************************************************
//  NAME: logEvent.
//
//  DESCRIPTION: Logs and prints the time and message.  
//
//  PARAMETERS: message: The log message to be displayed.
//              type:    The severity of the log.
//****************************************************************************
void Logger::logEvent(const std::string& message, const int type) const
{
	std::cout << "[";
	printTime();

	if (type == OK)
	{
		std::cout << " Notice]: ";
	}
	else if (type == FAIL)
	{
		std::cerr << " Error]: ";
	}
	else
	{
		std::cout << " Information]: ";
	}

	std::cout << message << std::endl;
}

//****************************************************************************
//  NAME: printLineHeader.
//
//  DESCRIPTION: Prints the header information of each line of each log.  
//				 Each log header contains the test name with the date and 
//				 time.  
// 
//  PARAMETERS: N/A.
//****************************************************************************
void Logger::printLineHeader() const
{
	std::cout << "[";
	printTime();
	std::cout << "]: ";
}

//****************************************************************************
//  NAME: printTime.
//
//  DESCRIPTION: Method to print the current date and time.
//   
//  PARAMETERS: N/A.
//****************************************************************************
void Logger::printTime() const
{
	// Get the current time using time_t
	std::time_t currentTime = std::time(nullptr);

	// Convert the time_t object to a tm struct
	std::tm localTime;
	::localtime_s(&localTime, &currentTime);

	// Format the date and time
	// Increase size to accommodate the formatted date/time
	char formattedTime[25];
	std::strftime(formattedTime, sizeof(formattedTime),
		"%m/%d/%Y %H:%M:%S", &localTime);

	// Output the formatted date and time
	std::cout << formattedTime;
}

//****************************************************************************
//  NAME: setTitlebar.
//
//  DESCRIPTION: This function will display the current test name and version
//				 in the titlebar of the executable window.  It will also
//				 display the pass/fail status of the test.   
// 
//  PARAMETERS: N/A.
//****************************************************************************
void Logger::setTitlebar() const
{
	std::stringstream title;
	std::string       endTime;		// To be implemented at a later date.

	if (m_isPassing == OK)
	{
		title << "Passing |  " << m_test << " (Version: " << m_version << ")";
	}
	else if (m_isPassing == FAIL)
	{
		title << "Failing |  " << m_test << " (Version: " << m_version << ")";
	}

	SetConsoleTitleA(title.str().c_str());
}

//****************************************************************************
//  NAME: printResult.
//
//  DESCRIPTION: Method to print the final result of the test.
// 
//  PARAMETERS: N/A.
//****************************************************************************
void Logger::printResult() const
{
	std::cout << std::endl;
	printLineHeader();
	std::cout << m_test << " Status: ";

	HANDLE hConsole;
	CONSOLE_SCREEN_BUFFER_INFO myBuffInfo;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsole, &myBuffInfo);
	SetConsoleTextAttribute(hConsole, 224);

	if (m_isPassing == OK)
	{
		std::cout << "  PASSED  ";
	}
	else if (m_isPassing == FAIL)
	{
		std::cout << "  FAILED  ";
	}

	SetConsoleTextAttribute(hConsole, myBuffInfo.wAttributes);
	std::cout << std::endl;
}