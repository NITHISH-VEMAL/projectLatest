#include <winsock2.h>
#include <iphlpapi.h>
#include <iostream>
#include <vector>
using namespace std;

#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")

void activeNet(DWORD processID)
{
    vector<unsigned char> buffer;
    DWORD dwSize = sizeof(MIB_TCPTABLE_OWNER_PID);
    DWORD dwRetValue = 0;
    PTCP_ESTATS_DATA_ROD_v0 dataRod = { 0 };
    // repeat till buffer is big enough
    do
    {
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                                buffer.resize(dwSize, 0);                                                     
                 dwRetValue = GetExtendedTcpTable(buffer.data(), &dwSize, TRUE, AF_INET, TCP_TABLE_OWNER_PID_ALL, 0);  //retrieves a table that contains a list of TCP endpoints
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    } while (dwRetValue == ERROR_INSUFFICIENT_BUFFER);

    if (dwRetValue == ERROR_SUCCESS)
    {
        
        PMIB_TCPTABLE_OWNER_PID ptTable = reinterpret_cast<PMIB_TCPTABLE_OWNER_PID>(buffer.data());

        int flag = 0;
        DWORD i;
        
        for (i = 0; i < ptTable->dwNumEntries; i++)
        {
            
           
            if ((DWORD)ptTable->table[i].dwOwningPid == processID) {
                
                ULONG rosSize = 0, rodSize = 0;
                ULONG winStatus;
                PUCHAR ros = NULL, rod = NULL;
                rodSize = sizeof(TCP_ESTATS_DATA_ROD_v0);

                if (rosSize != 0) {
                    ros = (PUCHAR)malloc(rosSize);
                    if (ros == NULL) {
                        wprintf(L"\nOut of memory");
                        return;
                    }
                    else
                        memset(ros, 0, rosSize); // zero the buffer
                }
                if (rodSize != 0) {
                    rod = (PUCHAR)malloc(rodSize);
                    if (rod == NULL) {
                        free(ros);
                        wprintf(L"\nOut of memory");
                        return;
                    }
                    else
                        memset(rod, 0, rodSize); // zero the buffer
                }

                dataRod = (PTCP_ESTATS_DATA_ROD_v0)rod;


                ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                      GetPerTcpConnectionEStats((PMIB_TCPROW) &ptTable->table[i], TcpConnectionEstatsData ,NULL, 0, 0,ros, 0, rosSize, rod, 0, rodSize);
               ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


                wprintf(L" %lu | ", dataRod->DataBytesIn + dataRod->DataBytesOut);
             
                flag = 1;
                break;

            }
            
        }
        if (flag == 0)
        {
            cout << "No usage";
        }
        

    }
    

    

}