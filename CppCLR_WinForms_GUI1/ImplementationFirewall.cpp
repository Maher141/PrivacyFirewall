#include "pch.h"
#include "Form1.h"

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
#include <msclr\marshal_cppstd.h>

#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")

#define MALLOC(x) HeapAlloc(GetProcessHeap(), 0, (x))
#define FREE(x) HeapFree(GetProcessHeap(), 0, (x))


char* reverseLookup(char* ip, char* hostname) {
	WSADATA wsaData = { 0 };
	int result = 0;
	DWORD dwRetval;
	struct sockaddr_in sockAddr_;
	char servInfo[NI_MAXSERV];
	std::string addr = ip;
	int port = 25;


	result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result == 0) {
		sockAddr_.sin_family = AF_INET;
		sockAddr_.sin_port = htons(port);
		sockAddr_.sin_addr.s_addr = inet_addr(addr.c_str());

		dwRetval = getnameinfo((struct sockaddr*)&sockAddr_,
			sizeof(struct sockaddr),
			hostname,
			NI_MAXHOST, servInfo, NI_MAXSERV, NI_NUMERICSERV);

		if (dwRetval == 0) {
			return hostname;
		} 
	} return 0;
}
// Quelle Konkatinieren String: https://github.com/balabit/libtermcapparser/blob/master/misc.c 
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
	char* result;
	const char* p = "Fehler beim Abrufen des Dateinamens";
	const char* p2 = "Zugriff verweigert/Falscher Parameter"; //Im Aufruf OpenProcess, wenn der Prozess schon beendet ist, führt dieser zum Error eines Aufrufs mit ungültigem Parameter
	HANDLE processHandle = NULL;
	char dataname[MAX_PATH];

	processHandle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, id);
	if (processHandle != NULL) {
		if (GetModuleBaseNameA(processHandle, NULL, dataname, sizeof(dataname)) == 0) {
			return p;
		}
		else {
			result = dupcat(dataname, 0);
			return result;
		}
		CloseHandle(processHandle);
	}
	return p2;
}
boolean loopThroughList(std::string s, std::list<std::string> mylist2) {

	for (std::list<std::string>::iterator t = mylist2.begin(); t != mylist2.end(); t++)
	{
		if (s.find(t->c_str()) != std::string::npos) {
			return true;
		}
		else
		{
			return false;
		}

	}
	return false;

}

array<System::String^, 2>^ start()
{

	array<System::String^, 2>^ matrix = gcnew array<System::String^, 2>(30, 4);

	std::list<std::string> mylist;
	std::list<std::string> mylist2;
	std::vector<const char*> v;
	PMIB_TCPTABLE_OWNER_PID pTcpTable;
	int* ports; 
	DWORD dwSize = 0;
	DWORD dwRetVal = 0;

	char szRemoteAddr[128];
	char szLocalAddr[128];
	struct in_addr IpAddr;
	char hostname[NI_MAXHOST];

	int i;
	int zaehler;
	int zeile;

	ports = new int[1 << (sizeof(u_short) * 8)]();

	pTcpTable = (MIB_TCPTABLE_OWNER_PID*)MALLOC(sizeof(MIB_TCPTABLE_OWNER_PID));
	if (pTcpTable == NULL) {
		printf("Error allocating memory\n");
	}

	dwSize = sizeof(MIB_TCPTABLE);

	if ((dwRetVal = GetExtendedTcpTable(pTcpTable, &dwSize, TRUE, AF_INET, TCP_TABLE_OWNER_PID_ALL, 0)) ==
		ERROR_INSUFFICIENT_BUFFER) {
		FREE(pTcpTable);
		pTcpTable = (MIB_TCPTABLE_OWNER_PID*)MALLOC(dwSize);
		if (pTcpTable == NULL) {
			printf("Error allocating memory\n");
		}
	}
	std::list<const char*>::iterator it;
	mylist2.emplace_front("dummy");

	if ((dwRetVal = GetExtendedTcpTable(pTcpTable, &dwSize, TRUE, AF_INET, TCP_TABLE_OWNER_PID_ALL, 0)) == NO_ERROR) {
		printf("\tNumber of entries: %d\n", (int)pTcpTable->dwNumEntries);
		for (i = 0; i < (int)pTcpTable->dwNumEntries; i++) {
			const char* pName = processName(pTcpTable->table[i].dwOwningPid);
			std::string s = pName;

			if (loopThroughList(s, mylist2) == true) {
				
			}
			else {

				System::String^ pNameCon = msclr::interop::marshal_as<System::String^>(s); //konvertieren in System::String
				matrix[zaehler,0] = pNameCon; //prozessnamen in liste 

				IpAddr.S_un.S_addr = (u_long)pTcpTable->table[i].dwLocalAddr;
				strcpy_s(szLocalAddr, sizeof(szLocalAddr), inet_ntoa(IpAddr));
				IpAddr.S_un.S_addr = (u_long)pTcpTable->table[i].dwRemoteAddr;
				strcpy_s(szRemoteAddr, sizeof(szRemoteAddr), inet_ntoa(IpAddr));

				std::ostringstream stringStream;
				stringStream << ("\n\tTCP[%i] PID: %ld ", i,
					pTcpTable->table[i].dwOwningPid);
				std::string copyOfStr = stringStream.str();
				printf("\n\tTCP[%i] PID: %ld ", i,
					pTcpTable->table[i].dwOwningPid);  
		
				System::String^ pidCon = msclr::interop::marshal_as<System::String^>(copyOfStr); //konvertieren in System::String
				matrix[zaehler, 1] = pidCon; //pid in liste 

				printf("\n");
				printf("\tTCP[%d] Name: %s\n", i, pName);
				printf("\tTCP[%d] Local Addr: %s\n", i, szLocalAddr);
				char* revLookL = reverseLookup(szLocalAddr, hostname);
				printf("\tTCP[%d] Local Reverse Adress: %s\n", i, revLookL);
				System::String^ revLookLCon = msclr::interop::marshal_as<System::String^>(revLookL); //konvertieren in System::String
				matrix[zaehler, 2] = revLookLCon; //revLookLocal in liste 

				printf("\tTCP[%d] Local Port: %d \n", i,
					ntohs((u_short)pTcpTable->table[i].dwLocalPort));
				printf("\tTCP[%d] Remote Addr: %s\n", i, szRemoteAddr);
				char* revLookR = reverseLookup(szRemoteAddr, hostname);

				System::String^ revLookRCon = msclr::interop::marshal_as<System::String^>(revLookR); //konvertieren in System::String
				matrix[zaehler, 3] = revLookRCon; //revLookRemote in liste 

				printf("\tTCP[%d] Remote Reverse Adress: %s\n", i, revLookR);
				printf("\tTCP[%d] Remote Port: %d\n", i,
					ntohs((u_short)pTcpTable->table[i].dwRemotePort));
				
				mylist2.emplace_front(s);
				zaehler++; //nächste zeile
				
			}
		}
	}
	else {
		printf("\tGetExtendedTcpTable failed with %d\n", dwRetVal);
		FREE(pTcpTable);
		delete[] ports;
	}

	if (pTcpTable != NULL) {
		FREE(pTcpTable);
		pTcpTable = NULL;
	}
	delete[] ports;
	return matrix;
}




System::Void CppCLRWinFormsProject::Form1::button_start_Click(System::Object^, System::EventArgs^)
{
	dataGridView1->Rows->Clear();
	
	array<System::String^, 2>^ matrix = start();
	
	int index = dataGridView1->Rows->Add();
	int index2 = dataGridView1->Rows->Add(matrix->Length);

	
	int row = 30;
	int col = 4;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			dataGridView1->Rows[i]->Cells[j]->Value = matrix[i, j];
		}
	}
	return System::Void();
}

System::Void CppCLRWinFormsProject::Form1::dataGridView1_CellContentClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e)
{
	return System::Void();
}
