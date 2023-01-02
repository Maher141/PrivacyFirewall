#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <list>
#include <Psapi.h>
#include <list>
#include <iostream>
#include <algorithm>
#include <windows.h>
#include <strsafe.h>
#include <iostream>
#include <sstream>
//#include <map>
using namespace std;

#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")

#define MALLOC(x) HeapAlloc(GetProcessHeap(), 0, (x))
#define FREE(x) HeapFree(GetProcessHeap(), 0, (x))

/* Note: could also use malloc() and free() */


char* reverseLookup(char* ip, char* hostname) {
	WSADATA wsaData = { 0 };
	int iResult = 0;
	DWORD dwRetval;
	struct sockaddr_in saGNI;
	//char hostname[NI_MAXHOST];
	char servInfo[NI_MAXSERV];
	string s = ip;
	//std::string ip = "66.249.68.9";
	
	int port = 25;

	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult == 0) {
		saGNI.sin_family = AF_INET;
		saGNI.sin_addr.s_addr = inet_addr(s.c_str());
		saGNI.sin_port = htons(port);

		dwRetval = getnameinfo((struct sockaddr*)&saGNI,
			sizeof(struct sockaddr),
			hostname,
			NI_MAXHOST, servInfo, NI_MAXSERV, NI_NUMERICSERV);

		if (dwRetval == 0) {
			//cout << "IPAddress : " << hostname << endl;
			return hostname;
		} //return 0;
	} return 0;  
}
char* dupcat(const char* s1, ...) {
	int len;
	char* p, * q, * sn;
	va_list ap;

	len = strlen(s1);
	va_start(ap, s1);
	while (1) {
		sn = va_arg(ap, char*);
		if (!sn)
			break;
		len += strlen(sn);
	}
	va_end(ap);

	p = new char[len + 1];
	strcpy(p, s1);
	q = p + strlen(p);

	va_start(ap, s1);
	while (1) {
		sn = va_arg(ap, char*);
		if (!sn)
			break;
		strcpy(q, sn);
		q += strlen(q);
	}
	va_end(ap);

	return p;
}

std::string GetLastErrorAsString()
{
	//Get the error message ID, if any.
	DWORD errorMessageID = ::GetLastError();
	if (errorMessageID == 0) {
		return std::string(); //No error message has been recorded
		
	}

	LPSTR messageBuffer = nullptr;

	//Ask Win32 to give us the string version of that message ID.
	//The parameters we pass in, tell Win32 to create the buffer that holds the message for us (because we don't yet know how long the message string will be).
	size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

	//Copy the error message into a std::string.
	std::string message(messageBuffer, size);
	const char* lol = message.c_str();

	//Free the Win32's string's buffer.
	LocalFree(messageBuffer);

	return message;
}

const char* processName(DWORD id) {
	HANDLE processHandle = NULL;
	char filename[MAX_PATH];
	char* ret;
	const char* p = "Failed to get module filename";
	//string p22 = GetLastErrorAsString();
	//const char* c ;
	//GetLastErrorAsString().c_str();
	const char* p2 = "Zugriff verweigert/Falscher Parameter"; //Im Aufruf OpenProcess, wenn der Prozess schon beendet ist, führt dieser zum Error eines Aufrufs mit ungültigem Parameter

	processHandle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, id);
	if (processHandle != NULL) {
		if (GetModuleBaseNameA(processHandle, NULL, filename, sizeof(filename)) == 0) {
			//std::ostringstream a;
			//std::cout << "Follow this command1: " << GetLastErrorAsString();
			string l = GetLastErrorAsString();
			//const char* t=  l.c_str();
			//a << "Follow this command1: " << GetLastErrorAsString();
			//std::string b = a.str(); // Or better, `std::move(a).str()`.

			//std::cout << b;
			//const char* c = b.c_str();
			return p;
		}
		else {
			ret = dupcat(filename, 0);
			return ret;
		}
		CloseHandle(processHandle);
	}
	//std::cout << "Follow this command2: " << GetLastErrorAsString();
	//c = GetLastErrorAsString().c_str();
	//const char* l2 = GetLastErrorAsString();
	return p2;
	/* //Versuch den output std::string dazu zu kriegen, unter Namen zurückgegeben zu werden
	std::ostringstream a;
	a << "Follow this command1: " << GetLastErrorAsString();
	std::string b = a.str(); // Or better, `std::move(a).str()`.

	std::cout << b;
	const char* d = b.c_str();
	return d;
	*/
}

boolean loopThroughList(string s, list<string> mylist2) {
	
	//std::string s = pName;
	for (std::list<std::string>::iterator t = mylist2.begin(); t != mylist2.end(); t++)
	{
		//std::string s = pName;
		if (s.find(t->c_str()) != std::string::npos) {
			//printf("found\n");
			return true;
		}
		else {
			//printf("not found\n");

		}
		
	}
	return false;

}

int main()
{

	std::list<string> mylist;
	std::list<string> mylist2;
	std::vector<const char*> v;
	// Declare and initialize variables
	PMIB_TCPTABLE_OWNER_PID pTcpTable;
	int* ports; // an array of all the possible ports
	DWORD dwSize = 0;
	DWORD dwRetVal = 0;

	char szRemoteAddr[128];
	char szLocalAddr[128];
	struct in_addr IpAddr;
	char hostname[NI_MAXHOST];

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
	std::list<const char*>::iterator it;
	mylist2.emplace_front("dummy");
	// Make a second call to GetTcpTable to get
	// the actual data we require
	if ((dwRetVal = GetExtendedTcpTable(pTcpTable, &dwSize, TRUE, AF_INET, TCP_TABLE_OWNER_PID_ALL, 0)) == NO_ERROR) {
		printf("\tNumber of entries: %d\n", (int)pTcpTable->dwNumEntries);
		for (i = 0; i < (int)pTcpTable->dwNumEntries; i++) {
			const char* pName = processName(pTcpTable->table[i].dwOwningPid);
			string s = pName;
			
			if (loopThroughList(s, mylist2)== true) {
				//printf("found in banana\n");
			}
			else {
				IpAddr.S_un.S_addr = (u_long)pTcpTable->table[i].dwLocalAddr;
				strcpy_s(szLocalAddr, sizeof(szLocalAddr), inet_ntoa(IpAddr));
				IpAddr.S_un.S_addr = (u_long)pTcpTable->table[i].dwRemoteAddr;
				strcpy_s(szRemoteAddr, sizeof(szRemoteAddr), inet_ntoa(IpAddr));

				//v.push_back(pName);
				//mylist.emplace_front(pName);

				printf("\n\tTCP[%d] PID: %ld ", i,
					pTcpTable->table[i].dwOwningPid);
				printf("\n");
				printf("\tTCP[%d] Name: %s\n", i, pName);
				printf("\tTCP[%d] Local Addr: %s\n", i, szLocalAddr);
				printf("\tTCP[%d] Local Reverse Adress: %s\n", i, reverseLookup(szLocalAddr, hostname));
				printf("\tTCP[%d] Local Port: %d \n", i,
					ntohs((u_short)pTcpTable->table[i].dwLocalPort));
				printf("\tTCP[%d] Remote Addr: %s\n", i, szRemoteAddr);
				printf("\tTCP[%d] Remote Reverse Adress: %s\n", i, reverseLookup(szRemoteAddr, hostname));
				printf("\tTCP[%d] Remote Port: %d\n", i,
					ntohs((u_short)pTcpTable->table[i].dwRemotePort));
				mylist2.emplace_front(s);
			}

			/*if (std::find(std::begin(v), std::end(v), pName) != std::end(v)) {
				printf("skipped\n");
			} */

			//if (std::find(std::begin(mylist), std::end(mylist), pName) != std::end(mylist)) {
			//if (std::count(mylist2.begin(), mylist2.end(), pName)) {
			//	printf("skipped\n");
			//}
			//else {
			//mylist2.emplace_front(s);

		/*  	IpAddr.S_un.S_addr = (u_long)pTcpTable->table[i].dwLocalAddr;
				strcpy_s(szLocalAddr, sizeof(szLocalAddr), inet_ntoa(IpAddr));
				IpAddr.S_un.S_addr = (u_long)pTcpTable->table[i].dwRemoteAddr;
				strcpy_s(szRemoteAddr, sizeof(szRemoteAddr), inet_ntoa(IpAddr));

				//v.push_back(pName);
				//mylist.emplace_front(pName);

				printf("\n\tTCP[%d] PID: %ld ", i,
					pTcpTable->table[i].dwOwningPid);
				printf("\n");
				printf("\tTCP[%d] Name: %s\n", i, pName);
				printf("\tTCP[%d] Local Addr: %s\n", i, szLocalAddr);
				printf("\tTCP[%d] Local Reverse Adress: %s\n", i, reverseLookup(szLocalAddr, hostname));
				printf("\tTCP[%d] Local Port: %d \n", i,
					ntohs((u_short)pTcpTable->table[i].dwLocalPort));
				printf("\tTCP[%d] Remote Addr: %s\n", i, szRemoteAddr);
				printf("\tTCP[%d] Remote Reverse Adress: %s\n", i, reverseLookup(szRemoteAddr, hostname));
				printf("\tTCP[%d] Remote Port: %d\n", i,
					ntohs((u_short)pTcpTable->table[i].dwRemotePort));
			//} 
			*/
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

}
*/
