

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
#include <pdh.h>

#include "terminate.h"
#include "printpname.h"
#include "memoryinfo.h"
#include "cpuUsage.h"
#include "diskUsage.h"
#include "netUsage.h"
#include "findUser.h"



#pragma comment(lib,"pdh.lib")
using namespace std;


int main(int argc, TCHAR * argv[])
{
	cout << " 1: view all process\n 2: To start a new process\n 3: To terminate a process from listed\n";

	while (1)
	{
		int getOption;
		cout << "\nChoose your option : ";
		cin >> getOption;

		switch (getOption)
		{


			// case 1 to view all process
		case 1:
		{

			DWORD aProcesses[1024], cbNeeded, cProcesses;
			unsigned int i;

			////////////////////////////////////////////////////////////////////
			if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))               //     to get all the process ID [ array, size, number of bytes ]
			///////////////////////////////////////////////////////////////////
			{
				return 1;
			}


			int f = 0;
			cProcesses = cbNeeded / sizeof(DWORD);   //to find no. of 
			DWORD pid[1000] = { 0 };
			double cpuusage[1000] = { 0 };
			int index = 0;

			for (i = 0; i < cProcesses; i++)
			{
				pid[i] = aProcesses[i];
				if (f == 0) {
					
					start(aProcesses[i]);
				}
					

				for (int i = 0; i <= 10000000; i++);

				//cout << getCurrentValue(aProcesses[i]);

				cpuusage[i] = getCurrentValue(aProcesses[i]);
				if (cpuusage[i] > 0) {
					f = 1;
				 }
				//cout << pid[index]<<"}";
				
			}

			int j, k;

			for (j = 0; j < cProcesses; j++)
			{
				for (k = j + 1; k < cProcesses; k++)
				{
					if ((int)cpuusage[j] > (int)cpuusage[k])
					{
						double temp = cpuusage[j];
						cpuusage[j] = cpuusage[k];
						cpuusage[k] = temp;

						int temporary = pid[j];
						pid[j] = pid[k];
						pid[k] = temporary;
					}
				}
			}
			
			for (i = 0; i < cProcesses; i++)
			{
				if (aProcesses[i] != 0)
				{
					cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
					//cout << pid[i]<<endl;
					//DWORD pID = aProcesses[i];
				  ///////////////////////////////////////////////////////
					//DWORD pID = pid[i];
					//cout << pID << endl << endl;
					//cout << i << endl << endl;
					PrintProcessNameAndID(pid[i]);                             
				    memoryInformation(pid[i]);
					cout<<"\t|" << cpuusage[i] <<"\t| ";
					/*start(aProcesses[i]);

					long sum = 0;
					for (long long i = 1; i < 100000; i++) {
						sum += log((double)i);
					}

					getCurrentValue();*/
					/*init(aProcesses[i]);

					for (long int i = 0; i <=100000000; i++);

					cout<<getCurrentValue(aProcesses[i])<<endl;*/
					//cout << cpuusage[i] << " | ";
					findDiskUsage(pid[i]);
	
					openProcessToken(pid[i]);
					cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl<<endl;
				//////////////////////////////////////////////////////


				}
			}

			break;
		}



		//case 2 to start new process
		case 2:
		{



			///////////////////////////////////////////////////////////////////
			string processName;
			cout << "Enter the process name : ";
			cin >> processName;
			std::wstring ws;                                                   // convert string to LPCWSTR
			ws.assign(processName.begin(), processName.end());
			LPWSTR pwst = &ws[0];
			LPCWSTR pcwstr = ws.c_str();
			///////////////////////////////////////////////////////////////////




			/////////////////////////////////////////////////////////////////////
			     ShellExecute(0, L"open", pcwstr, NULL, 0, SW_SHOW);                  //   to open the process  [ message, whatToDo, fileName, parameter, directory, how to open]
           ////////////////////////////////////////////////////////////////////

			break;

		}




		case 3:
		{


			cout << "Enter the process ID to be deleted : ";
			DWORD processID;
			cin >> processID;


			//////////////////////////////////////
			       Terminate(processID);             //   terminate process function
    	  //////////////////////////////////////


			break;


		}



		}


	}

	return 0;
}
