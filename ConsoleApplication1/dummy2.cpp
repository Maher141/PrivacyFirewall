#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib,"psapi")
#pragma comment(lib,"iphlpapi")
#pragma comment(lib,"wsock32")
#include <WS2tcpip.h>
#include <windows.h>
#include <winsock.h>
#include <iphlpapi.h>
#include <psapi.h>
#include <iostream>
#include <vector>
//#include <WS2tcpip.h>
#include <list>
using namespace std;


/*

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

const char* processName(DWORD id) {
	HANDLE processHandle = NULL;
	char filename[MAX_PATH];
	char* ret;
	const char* p = "Failed to get module filename";
	const char* p2 = "Failed to open process.";

	processHandle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, id);
	if (processHandle != NULL) {
		if (GetModuleBaseNameA(processHandle, NULL, filename, sizeof(filename)) == 0) {
			return p;
		}
		else {
			ret = dupcat(filename, 0);
			return ret;
		}
		CloseHandle(processHandle);
	}
	return p2;
}

char* dwordToString(DWORD id) {
	char aux[10];
	unsigned long parts[] = { (id & 0xff),(id >> 8) & 0xff,(id >> 16) & 0xff,(id >> 24) & 0xff };
	char* ret = dupcat(_ultoa(parts[0], aux, 10), ".", 0);
	for (int i = 1; i < 4; i++) {
		if (i < 3)
			ret = dupcat(ret, _ultoa(parts[i], aux, 10), ".", 0);
		else
			ret = dupcat(ret, _ultoa(parts[i], aux, 10), 0);
	}
	return ret;
}

void reverseLookup(char* s) {

	WSADATA wsaData = { 0 };
	int iResult = 0;
	DWORD dwRetval;
	struct sockaddr_in saGNI;
	char hostname[NI_MAXHOST];
	char servInfo[NI_MAXSERV];
	std::string ip = s;
	//std::string ip = "8.8.8.8";
	int port = 25;

	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult == 0) {
		saGNI.sin_family = AF_INET;
		//saGNI.sin_addr.s_addr = inet_addr(ip.c_str());
		saGNI.sin_addr.s_addr = inet_addr(ip.c_str());
		saGNI.sin_port = htons(port);

		dwRetval = getnameinfo((struct sockaddr*)&saGNI,
			sizeof(struct sockaddr),
			hostname,
			NI_MAXHOST, servInfo, NI_MAXSERV, NI_NUMERICSERV);

		if (dwRetval == 0) {
			cout << "Ip Adress : " << hostname << endl;
			
		}
		
	}
}

void main() {
	vector<unsigned char> buffer;
	DWORD dwSize = sizeof(MIB_TCPTABLE_OWNER_PID);
	DWORD dwRetValue = 0;
	std::list<string> my_list;

	do {
		buffer.resize(dwSize, 0);
		dwRetValue = GetExtendedTcpTable(buffer.data(), &dwSize, TRUE, AF_INET, TCP_TABLE_OWNER_PID_ALL, 0);
	} while (dwRetValue == ERROR_INSUFFICIENT_BUFFER);
	if (dwRetValue == ERROR_SUCCESS)
	{
		PMIB_TCPTABLE_OWNER_PID ptTable = reinterpret_cast<PMIB_TCPTABLE_OWNER_PID>(buffer.data());
		cout << "Number of Entries: " << ptTable->dwNumEntries << endl << endl;
		for (DWORD i = 0; i < ptTable->dwNumEntries; i++) {
			if (ptTable->table[i].dwOwningPid > 0) { //skip System Idle Process who is on PID = 0
				for (string x : my_list) {
					DWORD pid = ptTable->table[i].dwOwningPid;
					std::cout << "PID: "  << pid << endl;
					cout << "Name: " << processName(ptTable->table[i].dwOwningPid) << endl;
					cout << "State: " << ptTable->table[i].dwState << endl;
					cout << "Local: "
						<< dwordToString(ptTable->table[i].dwLocalAddr)
						<< ":"
						<< htons((unsigned short)ptTable->table[i].dwLocalPort)
						<< endl;
					reverseLookup(dwordToString(ptTable->table[i].dwLocalAddr));


					cout << "Remote: "
						<< dwordToString(ptTable->table[i].dwRemoteAddr)
						<< ":"
						<< htons((unsigned short)ptTable->table[i].dwRemotePort)
						<< endl;
					reverseLookup(dwordToString(ptTable->table[i].dwLocalAddr));
					cout << endl;
				}
			}
		}
	}
	cin.get();
}


/*
		PMIB_TCPTABLE_OWNER_PID ptTable = reinterpret_cast<PMIB_TCPTABLE_OWNER_PID>(buffer.data());
		cout << "Number of Entries: " << ptTable->dwNumEntries << endl << endl;
		for (DWORD i = 0; i < ptTable->dwNumEntries; i++) {
			if (ptTable->table[i].dwOwningPid > 0) { //skip System Idle Process who is on PID = 0
				for (string x : my_list) {
					DWORD pid = ptTable->table[i].dwOwningPid;
					cout << "PID: " <<  pid << endl;
					cout << "Name: " << processName(ptTable->table[i].dwOwningPid) << endl;
					cout << "State: " << ptTable->table[i].dwState << endl;
					cout << "Local: "
						<< dwordToString(ptTable->table[i].dwLocalAddr)
						<< ":"
						<< htons((unsigned short)ptTable->table[i].dwLocalPort)
						<< endl;
					reverseLookup(dwordToString(ptTable->table[i].dwLocalAddr));


					cout << "Remote: "
						<< dwordToString(ptTable->table[i].dwRemoteAddr)
						<< ":"
						<< htons((unsigned short)ptTable->table[i].dwRemotePort)
						<< endl;
					reverseLookup(dwordToString(ptTable->table[i].dwLocalAddr));
					cout << endl;
				}
			}
		}*/