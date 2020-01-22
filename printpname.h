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



void PrintProcessNameAndID(DWORD processID)
{
	TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");  //enter as unknown for all process initially, handles object


  //////////////////////////////////////////////////////////////////////////////////////////////////
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, TRUE , processID);      // provide an abstraction of a resource [ needed , inherit handle , id]
  /////////////////////////////////////////////////////////////////////////////////////////////////
 
  // token, exit code
  //process vm read - Required to read memory in a process using ReadProcessMemory.

	if (NULL != hProcess)
	{
		HMODULE hMod;
		DWORD cbNeeded;

		///////////////////////////////////////////////////////////////////////////////
		   if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded)) {}                  // handle for each module in the specified process, many process present
	   //////////////////////////////////////////////////////////////////////////////

		{


		 /////////////////////////////////////////////////////////////////////////////////////////////////
			GetModuleBaseName(hProcess, hMod, szProcessName, sizeof(szProcessName) / sizeof(TCHAR));             //   get process name and store in szprocessname
		////////////////////////////////////////////////////////////////////////////////////////////////


		}
	}
	
		for (int i = 0; i < 15; i++)
			_tprintf(TEXT("%c"), szProcessName[i]);
		printf(" |");
		DWORD pid = processID;
		int size = 1;
		while (pid != 0) {
			size++;
			pid /= 10;
		}
		_tprintf(TEXT(" %u"), processID);
		for (int i = 0; i < 10 - size; i++) {
			printf(" ");
		}
		printf(" |");
	
	if (CloseHandle(hProcess))
	{
		return;
	}
}
