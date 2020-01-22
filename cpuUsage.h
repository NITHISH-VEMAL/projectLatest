/* CPU USAGE : all program shares same [PROCESSOR], time execution taken by processor or execution  */

// 



#include <winsock2.h>
#include <Ws2tcpip.h>
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <psapi.h>
#include <iostream>
#include <string>
#include<WinBase.h>
#include <iphlpapi.h>
#include <Tcpestats.h>


ULARGE_INTEGER lastCPU, lastSysCPU, lastUserCPU;
static int numProcessors;



void start(DWORD processID) {

	SYSTEM_INFO sysInfo;
	FILETIME ftime, fsys, fuser;


	/////////////////////////////////////////////////////////////////
	GetSystemInfo(&sysInfo);                                         // fetch system information to get no. of processor
	numProcessors = sysInfo.dwNumberOfProcessors;                   // get number of processor--------------------------------<
///////////////////////////////////////////////////////////////





//////////////////////////////////////////////////////////
	GetSystemTimeAsFileTime(&ftime);                             // Retrieves the current system date and time 
	memcpy(&lastCPU, &ftime, sizeof(FILETIME));                  // copy the system time to lastCPU times
////////////////////////////////////////////////////////




	HANDLE self = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_QUERY_LIMITED_INFORMATION, TRUE, processID);




	///////////////////////////////////////////////////////////////////
	GetProcessTimes(self, &ftime, &ftime, &fsys, &fuser);
	
	memcpy(&lastSysCPU, &fsys, sizeof(FILETIME));                   // amount of time process executed in kernel mode
	memcpy(&lastUserCPU, &fuser, sizeof(FILETIME));                 // amount of time process executed in user mode
//////////////////////////////////////////////////////////////////
	//cout << lastSysCPU.QuadPart;


}



double getCurrentValue(DWORD processID) {

	//cout << lastSysCPU.QuadPart;

	HANDLE self = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_QUERY_LIMITED_INFORMATION, TRUE, processID);

	FILETIME ftime, fsys, fuser;
	ULARGE_INTEGER now, sys, user;
	double percent;

	////////////////////////////////////////////////////////////////
	GetSystemTimeAsFileTime(&ftime);                          //system time
	memcpy(&now, &ftime, sizeof(FILETIME));
	///////////////////////////////////////////////////////////////



	///////////////////////////////////////////////////////////////////////
	GetProcessTimes(self, &ftime, &ftime, &fsys, &fuser);
		memcpy(&sys, &fsys, sizeof(FILETIME));
		memcpy(&user, &fuser, sizeof(FILETIME));

		///////////////////////////////////////////////////////////////////////


		percent = (sys.QuadPart - lastSysCPU.QuadPart) + (user.QuadPart - lastUserCPU.QuadPart);     //time duration kernel + user    
		percent = percent / (now.QuadPart - lastCPU.QuadPart);                                    //difference between system time
		percent = percent / numProcessors;                                                           // divided by no. of processor

		lastCPU = now;
		lastUserCPU = user;
		lastSysCPU = sys;

		//cout << "CPU PERCENTAGE IS :" << percent << endl;
		return percent * 100;
		//cout << 1.0000 * 100 << endl;
		//cout << 1.0000 * 100 << endl <<endl;
		//printf("CPU usage percentage : %lf \n", percent);
	}
	

