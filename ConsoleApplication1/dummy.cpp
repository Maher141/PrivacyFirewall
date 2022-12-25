#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <list>
using namespace std;

#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")

#define MALLOC(x) HeapAlloc(GetProcessHeap(), 0, (x))
#define FREE(x) HeapFree(GetProcessHeap(), 0, (x))

/* Note: could also use malloc() and free() */



int main2()
{
	// Declare and initialize variables
	PMIB_TCPTABLE_OWNER_PID pTcpTable;
	int* ports; // an array of all the possible ports
	DWORD dwSize = 0;
	DWORD dwRetVal = 0;

	char szRemoteAddr[128];
	char szLocalAddr[128];
	struct in_addr IpAddr;

	int i;

	ports = new int[1 << (sizeof(u_short) * 8)]();

	pTcpTable = (MIB_TCPTABLE_OWNER_PID*)MALLOC(sizeof(MIB_TCPTABLE_OWNER_PID));
	if (pTcpTable == NULL) {
		printf("Error allocating memory\n");
		return 1;
	}

	dwSize = sizeof(MIB_TCPTABLE);
	// Make an initial call to GetTcpTable to
	// get the necessary size into the dwSize variable
	if ((dwRetVal = GetExtendedTcpTable(pTcpTable, &dwSize, TRUE, AF_INET, TCP_TABLE_OWNER_PID_ALL, 0)) ==
		ERROR_INSUFFICIENT_BUFFER) {
		FREE(pTcpTable);
		pTcpTable = (MIB_TCPTABLE_OWNER_PID*)MALLOC(dwSize);
		if (pTcpTable == NULL) {
			printf("Error allocating memory\n");
			return 1;
		}
	}
	// Make a second call to GetTcpTable to get
	// the actual data we require
	if ((dwRetVal = GetExtendedTcpTable(pTcpTable, &dwSize, TRUE, AF_INET, TCP_TABLE_OWNER_PID_ALL, 0)) == NO_ERROR) {
		printf("\tNumber of entries: %d\n", (int)pTcpTable->dwNumEntries);
		for (i = 0; i < (int)pTcpTable->dwNumEntries; i++) {
			IpAddr.S_un.S_addr = (u_long)pTcpTable->table[i].dwLocalAddr;
			strcpy_s(szLocalAddr, sizeof(szLocalAddr), inet_ntoa(IpAddr));
			IpAddr.S_un.S_addr = (u_long)pTcpTable->table[i].dwRemoteAddr;
			strcpy_s(szRemoteAddr, sizeof(szRemoteAddr), inet_ntoa(IpAddr));


			if (pTcpTable->table[i].dwLocalAddr) {
				IpAddr.S_un.S_addr = (ULONG)pTcpTable->table[i].dwLocalAddr;
				//_snprintf(newConn->strIntIp,_countof(newConn->strIntIp),"%d.%d.%d.%d",IpAddr.S_un.S_un_b.s_b1,IpAddr.S_un.S_un_b.s_b2,IpAddr.S_un.S_un_b.s_b3,IpAddr.S_un.S_un_b.s_b4);
				//wcsncpy(newConn->strIntIp, mir_a2t(inet_ntoa(IpAddr)), _tcslen(mir_a2t(inet_ntoa(IpAddr))));
			}

			if (pTcpTable->table[i].dwRemoteAddr) {
				IpAddr.S_un.S_addr = (u_long)pTcpTable->table[i].dwRemoteAddr;
				//wcsncpy(newConn->strExtIp, mir_a2t(inet_ntoa(IpAddr)), _tcslen(mir_a2t(inet_ntoa(IpAddr))));
			}
			printf("\n\tTCP[%d] PID: %ld ", i,
				pTcpTable->table[i].dwOwningPid);
			printf("\n");
			printf("\tTCP[%d] Local Addr: %s\n", i, szLocalAddr);
			printf("\tTCP[%d] Local Port: %d \n", i,
				ntohs((u_short)pTcpTable->table[i].dwLocalPort));
			printf("\tTCP[%d] Remote Addr: %s\n", i, szRemoteAddr);
			printf("\tTCP[%d] Remote Port: %d\n", i,
				ntohs((u_short)pTcpTable->table[i].dwRemotePort));
		}
	}
	else {
		printf("\tGetExtendedTcpTable failed with %d\n", dwRetVal);
		FREE(pTcpTable);
		delete[] ports;
		return 1;
	}

	if (pTcpTable != NULL) {
		FREE(pTcpTable);
		pTcpTable = NULL;
	}
	delete[] ports;
	return 0;
}


/*
void getDnsName(TCHAR* strIp, TCHAR* strHostName, size_t len)
{
	in_addr iaHost;

	iaHost.s_addr = inet_addr(mir_t2a(strIp));
	hostent* h = gethostbyaddr((char*)&iaHost, sizeof(struct in_addr), AF_INET);
	_tcsncpy_s(strHostName, len, (h == NULL) ? strIp : _A2T(h->h_name), _TRUNCATE);
}
*/



/*v2
* int main()
{
	// Declare and initialize variables
	MIB_TCPTABLE_OWNER_PID* pTcpTable;
	DWORD i, dwSize = 0, dwRetVal = 0;
	struct in_addr IpAddr;
	struct CONNECTION* connHead = NULL;

	char szLocalAddr[128];
	char szRemoteAddr[128];

	pTcpTable = (MIB_TCPTABLE_OWNER_PID*)MALLOC(sizeof(MIB_TCPTABLE_OWNER_PID));
	if (pTcpTable == NULL) {
		//printf("Error allocating memory!\n");
		return NULL;
	}

	dwSize = sizeof(MIB_TCPTABLE_OWNER_PID);
	// Make an initial call to GetTcpTable to
	// get the necessary size into the dwSize variable
	if ((dwRetVal = GetExtendedTcpTable(pTcpTable, &dwSize, TRUE, AF_INET, TCP_TABLE_OWNER_PID_ALL, 0)) == ERROR_INSUFFICIENT_BUFFER) {
		FREE(pTcpTable);
		pTcpTable = (MIB_TCPTABLE_OWNER_PID*)MALLOC(dwSize);
		if (pTcpTable == NULL) {
			//printf("Error allocating memory\n");
			return NULL;
		}
	}

	// Make a second call to GetTcpTable to get
	// the actual data we require
	if ((dwRetVal = GetExtendedTcpTable(pTcpTable, &dwSize, TRUE, AF_INET, TCP_TABLE_OWNER_PID_ALL, 0)) != NO_ERROR) {
		//printf("\tGetTcpTable() failed with return value %d\n", dwRetVal);
		FREE(pTcpTable);
		return NULL;
	}
	//printf("\tLocal Addr\tLocal Port\tRemote Addr\tRemote Port\n");
	//printf("Number of entries: %d\n", (int) pTcpTable->dwNumEntries);
	for (i = 0; i < pTcpTable->dwNumEntries; i++) {
		IpAddr.S_un.S_addr = (u_long)pTcpTable->table[i].dwLocalAddr;
		strcpy_s(szLocalAddr, sizeof(szLocalAddr), inet_ntoa(IpAddr));
		IpAddr.S_un.S_addr = (u_long)pTcpTable->table[i].dwRemoteAddr;
		strcpy_s(szRemoteAddr, sizeof(szRemoteAddr), inet_ntoa(IpAddr));
		

		if (pTcpTable->table[i].dwLocalAddr) {
			IpAddr.S_un.S_addr = (ULONG)pTcpTable->table[i].dwLocalAddr;
			//_snprintf(newConn->strIntIp,_countof(newConn->strIntIp),"%d.%d.%d.%d",IpAddr.S_un.S_un_b.s_b1,IpAddr.S_un.S_un_b.s_b2,IpAddr.S_un.S_un_b.s_b3,IpAddr.S_un.S_un_b.s_b4);
			//wcsncpy(newConn->strIntIp, mir_a2t(inet_ntoa(IpAddr)), _tcslen(mir_a2t(inet_ntoa(IpAddr))));
		}

		if (pTcpTable->table[i].dwRemoteAddr) {
			IpAddr.S_un.S_addr = (u_long)pTcpTable->table[i].dwRemoteAddr;
			//wcsncpy(newConn->strExtIp, mir_a2t(inet_ntoa(IpAddr)), _tcslen(mir_a2t(inet_ntoa(IpAddr))));
		}
		printf("\n\tTCP[%d] PID: %ld - ", i,
			pTcpTable->table[i].dwOwningPid);
		printf("\n");
		printf("\tTCP[%d] Local Addr: %s\n", i, szLocalAddr);
		printf("\tTCP[%d] Local Port: %d \n", i,
			ntohs((u_short)pTcpTable->table[i].dwLocalPort));
		printf("\tTCP[%d] Remote Addr: %s\n", i, szRemoteAddr);
		printf("\tTCP[%d] Remote Port: %d\n", i,
			ntohs((u_short)pTcpTable->table[i].dwRemotePort));
	
	}
	FREE(pTcpTable);

}
*/

/* gut funktioniert
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <list>
using namespace std;

#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")

#define MALLOC(x) HeapAlloc(GetProcessHeap(), 0, (x))
#define FREE(x) HeapFree(GetProcessHeap(), 0, (x))



void main()
{
	// Declare and initialize variables
	MIB_TCPTABLE_OWNER_PID* pTcpTable;
	DWORD i, dwSize = 0, dwRetVal = 0;
	struct in_addr IpAddr;
	struct CONNECTION* connHead = NULL;

	char szLocalAddr[128];
	char szRemoteAddr[128];

	pTcpTable = (MIB_TCPTABLE_OWNER_PID*)MALLOC(sizeof(MIB_TCPTABLE_OWNER_PID));
	if (pTcpTable == NULL) {
		printf("Error allocating memory!\n");

	}

	dwSize = sizeof(MIB_TCPTABLE_OWNER_PID);
	// Make an initial call to GetTcpTable to
	// get the necessary size into the dwSize variable
	if ((dwRetVal = GetExtendedTcpTable(pTcpTable, &dwSize, TRUE, AF_INET, TCP_TABLE_OWNER_PID_ALL, 0)) == ERROR_INSUFFICIENT_BUFFER) {
		FREE(pTcpTable);
		pTcpTable = (MIB_TCPTABLE_OWNER_PID*)MALLOC(dwSize);
		if (pTcpTable == NULL) {
			printf("Error allocating memory\n");

		}
	}

	// Make a second call to GetTcpTable to get
	// the actual data we require
	if ((dwRetVal = GetExtendedTcpTable(pTcpTable, &dwSize, TRUE, AF_INET, TCP_TABLE_OWNER_PID_ALL, 0)) != NO_ERROR) {
		printf("\tGetTcpTable() failed with return value %d\n", dwRetVal);
		FREE(pTcpTable);
	}
	//printf("\tLocal Addr\tLocal Port\tRemote Addr\tRemote Port\n");
	//printf("Number of entries: %d\n", (int) pTcpTable->dwNumEntries);
	for (i = 0; i < pTcpTable->dwNumEntries; i++) {
		IpAddr.S_un.S_addr = (u_long)pTcpTable->table[i].dwLocalAddr;
		strcpy_s(szLocalAddr, sizeof(szLocalAddr), inet_ntoa(IpAddr));
		IpAddr.S_un.S_addr = (u_long)pTcpTable->table[i].dwRemoteAddr;
		strcpy_s(szRemoteAddr, sizeof(szRemoteAddr), inet_ntoa(IpAddr));
		//pid2name(pTcpTable->table[i].dwOwningPid,&newConn->Pname);

		if (pTcpTable->table[i].dwLocalAddr) {
			IpAddr.S_un.S_addr = (ULONG)pTcpTable->table[i].dwLocalAddr;
			//_snprintf(newConn->strIntIp,_countof(newConn->strIntIp),"%d.%d.%d.%d",IpAddr.S_un.S_un_b.s_b1,IpAddr.S_un.S_un_b.s_b2,IpAddr.S_un.S_un_b.s_b3,IpAddr.S_un.S_un_b.s_b4);
			//wcsncpy(newConn->strIntIp, mir_a2t(inet_ntoa(IpAddr)), _tcslen(mir_a2t(inet_ntoa(IpAddr))));
		}

		if (pTcpTable->table[i].dwRemoteAddr) {
			IpAddr.S_un.S_addr = (u_long)pTcpTable->table[i].dwRemoteAddr;
			//wcsncpy(newConn->strExtIp, mir_a2t(inet_ntoa(IpAddr)), _tcslen(mir_a2t(inet_ntoa(IpAddr))));
		}
		printf("\n\tTCP[%d] State: %ld - ", i,
			pTcpTable->table[i].dwState);
		printf("\tTCP[%d] Local Addr: %s\n", i, szLocalAddr);
		printf("\tTCP[%d] Local Port: %d \n", i,
			ntohs((u_short)pTcpTable->table[i].dwLocalPort));
		printf("\tTCP[%d] Remote Addr: %s\n", i, szRemoteAddr);
		printf("\tTCP[%d] Remote Port: %d\n", i,
			ntohs((u_short)pTcpTable->table[i].dwRemotePort));

		switch (pTcpTable->table[i].dwState) {
		case MIB_TCP_STATE_CLOSED:
			//printf("CLOSED\n");
			break;
		case MIB_TCP_STATE_LISTEN:
			//printf("LISTEN\n");
			break;
		case MIB_TCP_STATE_SYN_SENT:
			//printf("SYN-SENT\n");
			break;
		case MIB_TCP_STATE_SYN_RCVD:
			//printf("SYN-RECEIVED\n");
			break;
		case MIB_TCP_STATE_ESTAB:
			//printf("ESTABLISHED\n");
			break;
		case MIB_TCP_STATE_FIN_WAIT1:
			//printf("FIN-WAIT-1\n");
			break;
		case MIB_TCP_STATE_FIN_WAIT2:
			//printf("FIN-WAIT-2 \n");
			break;
		case MIB_TCP_STATE_CLOSE_WAIT:
			//printf("CLOSE-WAIT\n");
			break;
		case MIB_TCP_STATE_CLOSING:
			//printf("CLOSING\n");
			break;
		case MIB_TCP_STATE_LAST_ACK:
			//printf("LAST-ACK\n");
			break;
		case MIB_TCP_STATE_TIME_WAIT:
			//printf("TIME-WAIT\n");
			break;
		case MIB_TCP_STATE_DELETE_TCB:
			//printf("DELETE-TCB\n");
			break;
		default:
			//printf("UNKNOWN dwState value\n");
			break;
		}
		//printf("TCP[%d]:%s%15d%20s%15d\n", i, szLocalAddr,ntohs((u_short)pTcpTable->table[i].dwLocalPort), szRemoteAddr,ntohs((u_short)pTcpTable->table[i].dwRemotePort));
		//printf("\tTCP[%d] Local Addr: %s\n", i, szLocalAddr);
		// printf("\tTCP[%d] Local Port: %d \n", i, ntohs((u_short)pTcpTable->table[i].dwLocalPort));
		//printf("\tTCP[%d] Remote Addr: %s\n", i, szRemoteAddr);
		//printf("\tTCP[%d] Remote Port: %d\n", i, ntohs((u_short)pTcpTable->table[i].dwRemotePort));
	}
	FREE(pTcpTable);

}*/