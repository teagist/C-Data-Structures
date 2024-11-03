//****************************************************************************
//	Header File for Windows Utils
//	Programmed by: Houston Brown
//	Last Compiled Date: 10/12/2024
//****************************************************************************

#ifndef _WIN_UTILS_H
#define _WIN_UTILS_H

#include <iostream>
#include <ctime>
#include <limits>

// Needed for sleep function
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#define OK 1
#define FAIL 0
#define INFO 2

namespace WinUtils
{
	enum States
	{
		PASSING = 0,
		PASSED,
		FAILING,
		FAILED
	};
	
	enum MessageLabels
	{
		ERR = 0,  // Change to FAIL later when update removes #defines
		INFOR,
		SUCCESS,
		NOTICE		
	};
	
	void delayBoot(int bootSeconds);
	void wait(int seconds);
	void clearScreen();
	void pauseScreen();
	
	void printHardwareDetails();
	void printOSDetails();
	
	void printUIBanner();	
	void printInvalidUIBanner();
	
	int getUserInput();
	int getYesOrNo(std::string prompt);
}

#endif
