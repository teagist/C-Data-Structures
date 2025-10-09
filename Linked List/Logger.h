//****************************************************************************
//	Header File for Logger Class
//	Programmed by: Houston Brown
//	Last Compiled Date: 10/17/2024
//****************************************************************************

#ifndef _LOGGER_H
#define _LOGGER_H

#include <fstream>
#include <string>
#include <sstream>
#include "WinUtils.h"

class Logger
{
public: 
	Logger(): m_test(""), m_version(""), m_isPassing(true){}
	Logger(std::string newTest, std::string newVersion);

	std::string getTest() const { return m_test; }
	void setTest(std::string newTest);

	std::string getVersion() const { return m_version; }
	void setVersion(std::string newVersion);
	
	void setPassingStatus(bool isSuccess);
	
	void readVersionInfo();
	
	void printStatusMessage(const std::string& message, 
	                                       const int& status) const;
	void logEvent(const std::string& message, const int type) const;
	
	void printLineHeader() const;
	void printTime() const;
	void setTitlebar() const;
	
	void printResult() const;
	
private:
	std::string   m_test;
	std::string   m_version;
	bool          m_isPassing;
	std::ofstream logFile;
};

#endif
