// Need to link with Iphlpapi.lib and Ws2_32.lib
//https://learn.microsoft.com/de-de/windows/win32/api/iphlpapi/nf-iphlpapi-gettcptable?redirectedfrom=MSDN
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "Ws2_32.lib")
#define _CRT_SECURE_NO_WARNINGS

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <cstdio>

#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")

#define MALLOC(x) HeapAlloc(GetProcessHeap(), 0, (x))
#define FREE(x) HeapFree(GetProcessHeap(), 0, (x))

/* Note: could also use malloc() and free() */
/*
int main()
{

    FILE* fp;
    fp = fopen("example.txt", "w");


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
        fprintf(fp, "Error allocating memory\n");
        return 1;
    }

    dwSize = sizeof(MIB_TCPTABLE);
 
    if ((dwRetVal = GetTcpTable(pTcpTable, &dwSize, TRUE)) ==
        ERROR_INSUFFICIENT_BUFFER) {
        FREE(pTcpTable);
        pTcpTable = (MIB_TCPTABLE*)MALLOC(dwSize);
        if (pTcpTable == NULL) {
            fprintf(fp, "Error allocating memory\n");
            return 1;
        }
    }


    // Make a second call to GetTcpTable to get
    // the actual data we require
    if ((dwRetVal = GetTcpTable(pTcpTable, &dwSize, TRUE)) == NO_ERROR) {
        fprintf(fp, "\tNumber of IPV4 entries: %d\n", (int)pTcpTable->dwNumEntries);
        for (i = 0; i < (int)pTcpTable->dwNumEntries; i++) {
            IpAddr.S_un.S_addr = (u_long)pTcpTable->table[i].dwLocalAddr;
            strcpy_s(szLocalAddr, sizeof(szLocalAddr), inet_ntoa(IpAddr ));
            IpAddr.S_un.S_addr = (u_long)pTcpTable->table[i].dwRemoteAddr;
            strcpy_s(szRemoteAddr, sizeof(szRemoteAddr), inet_ntoa(IpAddr));

            fprintf(fp, "\n\tTCP[%d] State: %ld - ", i,
                pTcpTable->table[i].dwState);
            switch (pTcpTable->table[i].dwState) {
            case MIB_TCP_STATE_CLOSED:
                fprintf(fp, "CLOSED\n");
                break;
            case MIB_TCP_STATE_LISTEN:
                fprintf(fp, "LISTEN\n");
                break;
            case MIB_TCP_STATE_SYN_SENT:
                fprintf(fp, "SYN-SENT\n");
                break;
            case MIB_TCP_STATE_SYN_RCVD:
                fprintf(fp, "SYN-RECEIVED\n");
                break;
            case MIB_TCP_STATE_ESTAB:
                fprintf(fp, "ESTABLISHED\n");
                break;
            case MIB_TCP_STATE_FIN_WAIT1:
                fprintf(fp, "FIN-WAIT-1\n");
                break;
            case MIB_TCP_STATE_FIN_WAIT2:
                fprintf(fp, "FIN-WAIT-2 \n");
                break;
            case MIB_TCP_STATE_CLOSE_WAIT:
                fprintf(fp, "CLOSE-WAIT\n");
                break;
            case MIB_TCP_STATE_CLOSING:
                fprintf(fp, "CLOSING\n");
                break;
            case MIB_TCP_STATE_LAST_ACK:
                fprintf(fp, "LAST-ACK\n");
                break;
            case MIB_TCP_STATE_TIME_WAIT:
                fprintf(fp, "TIME-WAIT\n");
                break;
            case MIB_TCP_STATE_DELETE_TCB:
                fprintf(fp, "DELETE-TCB\n");
                break;
            default:
                fprintf(fp, "UNKNOWN dwState value\n");
                break;
            }
            fprintf(fp, "\tTCP[%d] Local Addr: %s\n", i, szLocalAddr);
            fprintf(fp, "\tTCP[%d] Local Port: %d \n", i,
                ntohs((u_short)pTcpTable->table[i].dwLocalPort));
            fprintf(fp, "\tTCP[%d] Remote Addr: %s\n", i, szRemoteAddr);
            fprintf(fp, "\tTCP[%d] Remote Port: %d\n", i,
                ntohs((u_short)pTcpTable->table[i].dwRemotePort));
        }
    }
    else {
        fprintf(fp, "\tGetTcpTable failed with %d\n", dwRetVal);
        FREE(pTcpTable);
        return 1;
    }

    if (pTcpTable != NULL) {
        FREE(pTcpTable);
        pTcpTable = NULL;
    }
    fclose(fp);
    return 0;
}


*/