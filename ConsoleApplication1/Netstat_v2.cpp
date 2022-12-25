#define _CRT_SECURE_NO_WARNINGS
//#define _TCPMIB_
#include <winsock2.h> //import für AF_INET6
#include <ws2tcpip.h> //import für MIB_TCP6TABLE_OWNER_PID, AF_INET6
#include <iphlpapi.h>
//#include <stdio.h>
#include <windows.h>
#include <winsock.h>
#include <iphlpapi.h>
#include <psapi.h>
#include <iostream>
#include <vector>
#include <Iphlpapi.h>
#include <winapifamily.h>
#include <ip2string.h>
#include <Mstcpip.h>

#pragma comment(lib,"psapi")
#pragma comment(lib,"iphlpapi")
#pragma comment(lib,"wsock32")
#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")
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
	unsigned long parts[] = { (id & 0xff),(id >> 8) & 0xff,(id >> 16) & 0xff,(id >> 24) & 0xff};
	char* ret = dupcat(_ultoa(parts[0], aux, 10), ":", 0);
	for (int i = 1; i < 4; i++) {
		if (i < 3)
			ret = dupcat(ret, _ultoa(parts[i], aux, 10), ":", 0);
		else
			ret = dupcat(ret, _ultoa(parts[i], aux, 10), 0);
	}
	return ret;
}

char* ucharToString(UCHAR id) {
	char aux[10];
	unsigned long parts[] = { (id & 0xff),(id >> 7 >> 1) & 0xff,(id >> 7 >>7 >> 2) & 0xff,(id >> 7 >> 7 >> 7 >> 3) & 0xff };
	char* ret = dupcat(_ultoa(parts[0], aux, 10), ".", 0);
	for (int i = 1; i < 4; i++) {
		if (i < 3)
			ret = dupcat(ret, _ultoa(parts[i], aux, 10), ".", 0);
		else
			ret = dupcat(ret, _ultoa(parts[i], aux, 10), 0);
	}
	return ret;
}

int main() {
	vector<unsigned char> buffer;
	DWORD dwSize = sizeof(MIB_TCP6TABLE_OWNER_PID);
	DWORD dwRetValue = 0;

	do {
		buffer.resize(dwSize, 0);
		dwRetValue = GetExtendedTcpTable(buffer.data(), &dwSize, TRUE, AF_INET6, TCP_TABLE_OWNER_PID_ALL, 0);
	} while (dwRetValue == ERROR_INSUFFICIENT_BUFFER);
	if (dwRetValue == ERROR_SUCCESS)
	{
		
		PMIB_TCP6TABLE_OWNER_PID ptTable = reinterpret_cast<PMIB_TCP6TABLE_OWNER_PID>(buffer.data());


		cout << "Number of Entries: " << ptTable->dwNumEntries << endl << endl;
		for (DWORD i = 0; i < ptTable->dwNumEntries; i++) {

			DWORD pid = ptTable->table[i].dwOwningPid;
			cout << "PID: " << pid << endl;
			cout << "Name: " << processName(ptTable->table[i].dwOwningPid) << endl;
			cout << "State: " << ptTable->table[i].dwState << endl;
			cout << "Local: "
				<< dwordToString((DWORD)ptTable->table[i].ucLocalAddr)
				<< ":"
				<< htons((unsigned short)ptTable->table[i].dwLocalPort)
				<< endl;

			cout << "Remote: "
				<< dwordToString((DWORD)ptTable->table[i].ucRemoteAddr)
				<< ":"
				<< htons((unsigned short)ptTable->table[i].dwRemotePort)
				<< endl;

			cout << endl;
		}
	}
	cin.get();
}

*/