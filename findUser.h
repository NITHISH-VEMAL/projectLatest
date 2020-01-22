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

#include <comdef.h>
#define MAX_NAME 256


void openProcessToken(DWORD processID)
{
    //string user="";
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION , TRUE, processID);
    HANDLE hProcessToken = NULL;
    if (!::OpenProcessToken(hProcess, TOKEN_READ, &hProcessToken) || !hProcessToken)
    {
       
    }
    DWORD dwProcessTokenInfoAllocSize = 0;
    if(!GetTokenInformation(hProcessToken, TokenUser, NULL, 0, &dwProcessTokenInfoAllocSize)){}

    PTOKEN_USER pUserToken = NULL;//  reinterpret_cast<PTOKEN_USER>(new BYTE[dwProcessTokenInfoAllocSize]);
    pUserToken = (PTOKEN_USER)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, MAX_PATH);

    if (GetTokenInformation(hProcessToken, TokenUser, pUserToken, dwProcessTokenInfoAllocSize, &dwProcessTokenInfoAllocSize))
    {
        
        SID_NAME_USE   snuSIDNameUse;
        TCHAR          szUser[MAX_PATH] = { 0 };
        DWORD          dwUserNameLength = MAX_PATH;
        TCHAR          szDomain[MAX_PATH] = { 0 };
        DWORD          dwDomainNameLength = MAX_PATH;

        // Retrieve user name and domain name based on user's SID.
        if (LookupAccountSid(NULL,
            pUserToken->User.Sid,
            szUser,
            &dwUserNameLength,
            szDomain,
            &dwDomainNameLength,
            &snuSIDNameUse))
        {
            // Prepare user name string
            //cout << pUserToken->User.Sid;
            cout << "\t";
            for(int i=0;i<15;i++)
            cout << (char)szUser[i];
            cout <<"..|"<< endl;
        }
        
    }
    else {
        printf("\tSystem handles..|\n");
    }

}
