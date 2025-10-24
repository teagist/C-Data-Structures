//****************************************************************************
//	Implementation File for Windows Utils
//	Programmed by: Houston Brown
//	Last Compiled Date: 10/25/2025
//****************************************************************************

#include "WinUtils.h"

//****************************************************************************
//	NAME: delayBoot.
//
//	DESCRIPTION: Delays the booting of the system while displaying the 
//				 booting information.  
//****************************************************************************
void WinUtils::delayBoot(int bootSeconds)
{
	std::string clk[4] = {"booting...|",
					 	  "booting.../",
					 	  "booting...-",
					 	  "booting...\\" };

	time_t seconds1 = time(NULL);
	time_t seconds2 = time(NULL);
	bool   bootComplete = false;
	int    idx = 0;

	while (!bootComplete)
	{
		if ((time(NULL) - seconds1) >= bootSeconds)
		{
			bootComplete = true;
		}
		if ((time(NULL) - seconds2) >= 1)
		{
			seconds2 = time(NULL);
			for (int i = 0; i < 8; ++i)
			{
				std::cout << "\r" << clk[idx++] << " (" << (bootSeconds + 1) -
					              (time(NULL) - seconds1) << " secs.)   ";
				if (idx > 3)
				{
					idx = 0;
				}
#ifdef _WIN32				
				Sleep(125);
#else
				usleep(125000);
#endif					
			}
		}
	}
	std::cout << std::endl;
}

//****************************************************************************
//	NAME: wait.
//
//	DESCRIPTION: Places a wait on the program until the number of seconds
//				 have been exhausted.  
//****************************************************************************
void WinUtils::wait(int seconds)
{
	time_t currentSeconds = time(NULL);

	std::cout << "Waiting for " << seconds << " seconds" << std::endl;

	while (seconds)
	{
		if ((time(NULL) - currentSeconds) >= 1)
		{
			std::cout << "\r" << seconds - 1 << " secs...";
			seconds = seconds - 1;
			currentSeconds = time(NULL);
		}
	}
	std::cout << std::endl;
}

//****************************************************************************
//	NAME: clearScreen.
//
//	DESCRIPTION: Clears the screen with an appropriate system command.
//****************************************************************************
void WinUtils::clearScreen()
{
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif	
}

//****************************************************************************
//	NAME: pauseScreen.
//
//	DESCRIPTION: Pauses the program an prompts the user to press the <enter>
//				 key to continue.
//****************************************************************************
void WinUtils::pauseScreen()
{
	std::string entry = "";
	std::cout << "Please press <enter> to continue..." << std::endl;
	std::cin.clear();
	fflush(stdin);
	std::getline(std::cin, entry);
}

//****************************************************************************
//	NAME: printHardwareDetails.
//
//	DESCRIPTION: This function displays the hardware information of the 
//				 machine running the system.  
//****************************************************************************
void WinUtils::printHardwareDetails()
{
#ifdef _WIN32 
   SYSTEM_INFO siSysInfo;
   GetSystemInfo(&siSysInfo);
   
   std::cout << "\t\t\tOEM ID: " << siSysInfo.dwOemId << std::endl;
   std::cout << "\t\t\tNumber of processors: ";
   std::cout << siSysInfo.dwNumberOfProcessors << std::endl;
   std::cout << "\t\t\tPage size: " << siSysInfo.dwPageSize << std::endl;
   std::cout << "\t\t\tProcessor type: " << siSysInfo.dwProcessorType;
	
#else
	std::cout << "Unix/Linux Distro";	
#endif
}

//****************************************************************************
//	NAME: printOSDetails.
//
//	DESCRIPTION: This function displays the operating system information of
//				 the machine running the system.
//****************************************************************************
void WinUtils::printOSDetails()
{
#ifdef _WIN32
	BYTE* sharedUserData = (BYTE*)0x7FFE0000;
	std::cout << "Windows " << *(ULONG*)(sharedUserData + 0x26c);
	std::cout << "." << *(ULONG*)(sharedUserData + 0x270);
	std::cout << " (Build: " << *(ULONG*)(sharedUserData + 0x260) << ")";
	    
#else
	std::cout << "Unix/Linux Distro";
#endif
}

//****************************************************************************
//	NAME: printUIBanner.
//
//	DESCRIPTION: Displays a block of text that will alert the user that 
//				 their input is needed.  
//****************************************************************************
void WinUtils::printUIBanner()
{
	HANDLE hConsole;
	CONSOLE_SCREEN_BUFFER_INFO myBuffInfo;
		
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsole, &myBuffInfo);    
	SetConsoleTextAttribute(hConsole, 31);
	
	std::string stars = "****************************************";
	
	std::cout << stars << stars << std::endl;
	std::cout << "         User Input Required\t\t\t\t\t\t\t" << std::endl;
	std::cout << stars << stars << std::endl;
	SetConsoleTextAttribute(hConsole, myBuffInfo.wAttributes);
}

//****************************************************************************
//	NAME: printInvalidUIBanner.
//
//	DESCRIPTION: Displays a block of text that will alert the user that 
//				 their input is invalid.  
//****************************************************************************
void WinUtils::printInvalidUIBanner()
{
	HANDLE hConsole;
	CONSOLE_SCREEN_BUFFER_INFO myBuffInfo;
		
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsole, &myBuffInfo);    
	SetConsoleTextAttribute(hConsole, 79);
	
	std::string stars = "****************************************";
	
	std::cout << stars << stars << std::endl;
	std::cout << "         Invalid Entry\t\t\t\t\t\t\t\t" << std::endl;
	std::cout << stars << stars << std::endl;
	SetConsoleTextAttribute(hConsole, myBuffInfo.wAttributes);
}

//****************************************************************************
//	NAME: getUserInput.
//
//	DESCRIPTION: This function will attempt to receive input from the user.
//				 If the input is invalid, the user will be prompted to try
//				 again.  
//****************************************************************************
int WinUtils::getUserInput()
{
	int entryValue;
	
	while (true)
	{
		if (std::cin >> entryValue)
		{
			// User input successful
			break;
		}
		else
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), 
			                '\n');
			std::cout << std::endl;
			printInvalidUIBanner();
		}
	}
	
	return entryValue;
}

//****************************************************************************
//	NAME: getYesOrNo.
//
//	DESCRIPTION: This function will display the prompt to the user and 
//				 prompt them to enter a yes or no answer.  If the user's 
//				 entry is invalid, a message will be displayed.  Otherwise,
//				 the value will be returned to the caller.
//****************************************************************************
int WinUtils::getYesOrNo(std::string prompt)
{
    char userEntry;

    while (true)
    {
        std::cout << prompt << "(y/n) ";
        if (std::cin >> userEntry)
        {
            // Convert the input to uppercase
            userEntry = std::toupper(userEntry);

            // Check if it's a valid input
            if (userEntry == 'Y')
            {
                return OK;
            }
            else if (userEntry == 'N')
            {
                return FAIL; 
            }
            else
            {
            	std::cout << std::endl;
            	printInvalidUIBanner();
            }
        }
        else
        {
            // Clear input buffer to handle invalid input
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << std::endl;
            printInvalidUIBanner();
        }
    }	
}
