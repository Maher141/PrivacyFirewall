// Need to link with Iphlpapi.lib and Ws2_32.lib
//https://learn.microsoft.com/de-de/windows/win32/api/iphlpapi/nf-iphlpapi-gettcptable?redirectedfrom=MSDN
//https://learn.microsoft.com/de-de/windows/win32/api/iphlpapi/nf-iphlpapi-gettcp6table?redirectedfrom=MSDN
//

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "Ws2_32.lib")

#ifndef UNICODE
#define UNICODE
#endif

#include <iostream>
#include <fstream>
//using namespace std;

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>

#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")

#define MALLOC(x) HeapAlloc(GetProcessHeap(), 0, (x))
#define FREE(x) HeapFree(GetProcessHeap(), 0, (x))

/* Note: could also use malloc() and free() */

/*
int main12412312()
{

    //ofstream myfile;
    //myfile.open("example.txt");
    // Declare and initialize variables
    PMIB_TCPTABLE pTcpTable;
    DWORD dwSize = 0;
    DWORD dwRetVal = 0;

    char szLocalAddr[128];
    char szRemoteAddr[128];

    struct in_addr IpAddr;

    int i;

    pTcpTable = (MIB_TCPTABLE*)MALLOC(sizeof(MIB_TCPTABLE));
    if (pTcpTable == NULL) {
        fprintf("Error allocating memory\n");
        return 1;
    }

    dwSize = sizeof(MIB_TCPTABLE);
    // Make an initial call to GetTcpTable to
    // get the necessary size into the dwSize variable
    if ((dwRetVal = GetTcpTable(pTcpTable, &dwSize, TRUE)) ==
        ERROR_INSUFFICIENT_BUFFER) {
        FREE(pTcpTable);
        pTcpTable = (MIB_TCPTABLE*)MALLOC(dwSize);
        if (pTcpTable == NULL) {
            fprintf("Error allocating memory\n");
            return 1;
        }
    }
    // Make a second call to GetTcpTable to get
    // the actual data we require
    if ((dwRetVal = GetTcpTable(pTcpTable, &dwSize, TRUE)) == NO_ERROR) {
        fprintf("\tNumber of IPV4 entries: %d\n", (int)pTcpTable->dwNumEntries);
        for (i = 0; i < (int)pTcpTable->dwNumEntries; i++) {
            IpAddr.S_un.S_addr = (u_long)pTcpTable->table[i].dwLocalAddr;
            strcpy_s(szLocalAddr, sizeof(szLocalAddr), inet_ntoa(IpAddr));
            IpAddr.S_un.S_addr = (u_long)pTcpTable->table[i].dwRemoteAddr;
            strcpy_s(szRemoteAddr, sizeof(szRemoteAddr), inet_ntoa(IpAddr));

            fprintf("\n\tTCP[%d] State: %ld - ", i,
                pTcpTable->table[i].dwState);
            switch (pTcpTable->table[i].dwState) {
            case MIB_TCP_STATE_CLOSED:
                fprintf("CLOSED\n");
                break;
            case MIB_TCP_STATE_LISTEN:
                fprintf("LISTEN\n");
                break;
            case MIB_TCP_STATE_SYN_SENT:
                fprintf("SYN-SENT\n");
                break;
            case MIB_TCP_STATE_SYN_RCVD:
                fprintf("SYN-RECEIVED\n");
                break;
            case MIB_TCP_STATE_ESTAB:
                fprintf("ESTABLISHED\n");
                break;
            case MIB_TCP_STATE_FIN_WAIT1:
                fprintf("FIN-WAIT-1\n");
                break;
            case MIB_TCP_STATE_FIN_WAIT2:
                fprintf("FIN-WAIT-2 \n");
                break;
            case MIB_TCP_STATE_CLOSE_WAIT:
                fprintf("CLOSE-WAIT\n");
                break;
            case MIB_TCP_STATE_CLOSING:
                fprintf("CLOSING\n");
                break;
            case MIB_TCP_STATE_LAST_ACK:
                fprintf("LAST-ACK\n");
                break;
            case MIB_TCP_STATE_TIME_WAIT:
                fprintf("TIME-WAIT\n");
                break;
            case MIB_TCP_STATE_DELETE_TCB:
                fprintf("DELETE-TCB\n");
                break;
            default:
                fprintf("UNKNOWN dwState value\n");
                break;
            }
            fprintf("\tTCP[%d] Local Addr: %s\n", i, szLocalAddr);
            //myfile << ("\tTCP[%d] Local Addr: %s\n", i, szLocalAddr);
            fprintf("\tTCP[%d] Local Port: %d \n", i,
                ntohs((u_short)pTcpTable->table[i].dwLocalPort));
            fprintf("\tTCP[%d] Remote Addr: %s\n", i, szRemoteAddr);
            fprintf("\tTCP[%d] Remote Port: %d\n", i,
                ntohs((u_short)pTcpTable->table[i].dwRemotePort));
        }
    }
    else {
        fprintf("\tGetTcpTable failed with %d\n", dwRetVal);
        FREE(pTcpTable);
        return 1;
    }

    if (pTcpTable != NULL) {
        FREE(pTcpTable);
        pTcpTable = NULL;
    }



    PMIB_TCP6TABLE pTcpTable2;
    DWORD dwSize2 = 0;
    DWORD dwRetVal2 = 0;

    wchar_t ipstringbuffer[46];

    int i2;

    pTcpTable2 = (MIB_TCP6TABLE*)MALLOC(sizeof(MIB_TCP6TABLE));
    if (pTcpTable2 == NULL) {
        wprintf(L"Error allocating memory\n");
        return 1;
    }

    dwSize = sizeof(MIB_TCP6TABLE);
    // Make an initial call to GetTcp6Table to
    // get the necessary size into the dwSize variable
    if ((dwRetVal2 = GetTcp6Table(pTcpTable2, &dwSize2, TRUE)) ==
        ERROR_INSUFFICIENT_BUFFER) {
        FREE(pTcpTable2);
        pTcpTable2 = (MIB_TCP6TABLE*)MALLOC(dwSize2);
        if (pTcpTable2 == NULL) {
            wprintf(L"Error allocating memory\n");
            return 1;
        }
    }
    // Make a second call to GetTcp6Table to get
    // the actual data we require
    if ((dwRetVal2 = GetTcp6Table(pTcpTable2, &dwSize2, TRUE)) == NO_ERROR) {
        wprintf(L"\n");
        wprintf(L"\tNumber of IPV6 entries: %d\n", (int)pTcpTable2->dwNumEntries);
        for (i2 = 0; i2 < (int)pTcpTable2->dwNumEntries; i2++) {
            wprintf(L"\n\tTCP[%d] State: %ld - ", i2,
                pTcpTable2->table[i2].State);
            switch (pTcpTable2->table[i2].State) {
            case MIB_TCP_STATE_CLOSED:
                wprintf(L"CLOSED\n");
                break;
            case MIB_TCP_STATE_LISTEN:
                wprintf(L"LISTEN\n");
                break;
            case MIB_TCP_STATE_SYN_SENT:
                wprintf(L"SYN-SENT\n");
                break;
            case MIB_TCP_STATE_SYN_RCVD:
                wprintf(L"SYN-RECEIVED\n");
                break;
            case MIB_TCP_STATE_ESTAB:
                wprintf(L"ESTABLISHED\n");
                break;
            case MIB_TCP_STATE_FIN_WAIT1:
                wprintf(L"FIN-WAIT-1\n");
                break;
            case MIB_TCP_STATE_FIN_WAIT2:
                wprintf(L"FIN-WAIT-2 \n");
                break;
            case MIB_TCP_STATE_CLOSE_WAIT:
                wprintf(L"CLOSE-WAIT\n");
                break;
            case MIB_TCP_STATE_CLOSING:
                wprintf(L"CLOSING\n");
                break;
            case MIB_TCP_STATE_LAST_ACK:
                wprintf(L"LAST-ACK\n");
                break;
            case MIB_TCP_STATE_TIME_WAIT:
                wprintf(L"TIME-WAIT\n");
                break;
            case MIB_TCP_STATE_DELETE_TCB:
                wprintf(L"DELETE-TCB\n");
                break;
            default:
                wprintf(L"UNKNOWN dwState value\n");
                break;
            }

            if (InetNtop(AF_INET6, &pTcpTable2->table[i2].LocalAddr, ipstringbuffer, 46) == NULL)
                wprintf(L"  InetNtop function failed for local IPv6 address\n");
            else
                wprintf(L"\tTCP[%d] Local Addr: %s\n", i2, ipstringbuffer);
            wprintf(L"\tTCP[%d] Local Scope ID: %d \n", i2,
                ntohl(pTcpTable2->table[i2].dwLocalScopeId));
            wprintf(L"\tTCP[%d] Local Port: %d \n", i2,
                ntohs((u_short)pTcpTable2->table[i2].dwLocalPort));

            if (InetNtop(AF_INET6, &pTcpTable2->table[i2].RemoteAddr, ipstringbuffer, 46) == NULL)
                wprintf(L"  InetNtop function failed for remote IPv6 address\n");
            else
                wprintf(L"\tTCP[%d] Remote Addr: %s\n", i2, ipstringbuffer);
            wprintf(L"\tTCP[%d] Remote Scope ID: %d \n", i2,
                ntohl(pTcpTable2->table[i2].dwRemoteScopeId));
            wprintf(L"\tTCP[%d] Remote Port: %d\n", i2,
                ntohs((u_short)pTcpTable2->table[i2].dwRemotePort));
        }
    }
    else {
        wprintf(L"\tGetTcp6Table failed with %d\n", dwRetVal2);
        FREE(pTcpTable2);
        return 1;
    }

    if (pTcpTable2 != NULL) {
        FREE(pTcpTable2);
        pTcpTable2 = NULL;
    }


    return 0;
}
*/

//C:\Users\Bachelor\source\repos\ConsoleApplication1\ConsoleApplication1