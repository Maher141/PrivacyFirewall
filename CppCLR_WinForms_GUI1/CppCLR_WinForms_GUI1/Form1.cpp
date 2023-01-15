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
//#include <map>
//using namespace std;

#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")

#define MALLOC(x) HeapAlloc(GetProcessHeap(), 0, (x))
#define FREE(x) HeapFree(GetProcessHeap(), 0, (x))


char* reverseLookup(char* ip, char* hostname) {
	WSADATA wsaData = { 0 };
	int iResult = 0;
	DWORD dwRetval;
	struct sockaddr_in saGNI;
	//char hostname[NI_MAXHOST];
	char servInfo[NI_MAXSERV];
	std::string s = ip;
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
			std::string l = GetLastErrorAsString();
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

boolean loopThroughList(std::string s, std::list<std::string> mylist2) {

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

struct t_thing {
	std::string alibaba[20][3];
	//array< System::String^ >^ local = gcnew array< System::String^ >(2);
	//array<array<System::String^>^>^ test = gcnew array<array<System::String^>^>(3)(3);

	

	
};


//struct t_thing  start()
array<System::String^, 2>^ start()
{

	array<System::String^, 2>^ matrix = gcnew array<System::String^, 2>(30, 4);

	std::list<std::string> mylist;
	std::list<std::string> mylist2;
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

    //extern std::string matrix[20][3];

	/*struct t_thing matrix = {
	{} };
	*/
	int i;
	int zaehler;
	int zeile;

	ports = new int[1 << (sizeof(u_short) * 8)]();

	pTcpTable = (MIB_TCPTABLE_OWNER_PID*)MALLOC(sizeof(MIB_TCPTABLE_OWNER_PID));
	if (pTcpTable == NULL) {
		printf("Error allocating memory\n");
		//return 1;
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
			//return NULL;
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
			std::string s = pName;

			if (loopThroughList(s, mylist2) == true) {
				//printf("found in banana\n");
				
			}
			else {

				System::String^ pNameCon = msclr::interop::marshal_as<System::String^>(s); //konvertieren in System::String
				matrix[zaehler,0] = pNameCon; //prozessnamen in liste 
				
				

				IpAddr.S_un.S_addr = (u_long)pTcpTable->table[i].dwLocalAddr;
				strcpy_s(szLocalAddr, sizeof(szLocalAddr), inet_ntoa(IpAddr));
				IpAddr.S_un.S_addr = (u_long)pTcpTable->table[i].dwRemoteAddr;
				strcpy_s(szRemoteAddr, sizeof(szRemoteAddr), inet_ntoa(IpAddr));

				//v.push_back(pName);
				//mylist.emplace_front(pName);

				std::ostringstream stringStream;
				stringStream << ("\n\tTCP[%i] PID: %ld ", i,
					pTcpTable->table[i].dwOwningPid);
				std::string copyOfStr = stringStream.str();
				printf("\n\tTCP[%i] PID: %ld ", i,
					pTcpTable->table[i].dwOwningPid);  
		
				System::String^ pidCon = msclr::interop::marshal_as<System::String^>(copyOfStr); //konvertieren in System::String
				matrix[zaehler, 1] = pidCon; //pid in liste 

				//matrix.alibaba[zaehler][1] = copyOfStr;
				printf("\n");
				printf("\tTCP[%d] Name: %s\n", i, pName);
				printf("\tTCP[%d] Local Addr: %s\n", i, szLocalAddr);
				char* revLookL = reverseLookup(szLocalAddr, hostname);
				//printf("\tTCP[%d] Local Reverse Adress: %s\n", i, reverseLookup(szLocalAddr, hostname));
				printf("\tTCP[%d] Local Reverse Adress: %s\n", i, revLookL);
				System::String^ revLookLCon = msclr::interop::marshal_as<System::String^>(revLookL); //konvertieren in System::String
				matrix[zaehler, 2] = revLookLCon; //revLookLocal in liste 

				//matrix.alibaba[zaehler][2] = revLookL;  //local reverse in liste
				printf("\tTCP[%d] Local Port: %d \n", i,
					ntohs((u_short)pTcpTable->table[i].dwLocalPort));
				printf("\tTCP[%d] Remote Addr: %s\n", i, szRemoteAddr);
				char* revLookR = reverseLookup(szRemoteAddr, hostname);

				System::String^ revLookRCon = msclr::interop::marshal_as<System::String^>(revLookR); //konvertieren in System::String
				matrix[zaehler, 3] = revLookRCon; //revLookRemote in liste 

				//matrix.alibaba[zaehler][3] = revLookR; //remote reverse in liste
				printf("\tTCP[%d] Remote Reverse Adress: %s\n", i, revLookR);
				//printf("\tTCP[%d] Remote Reverse Adress: %s\n", i, reverseLookup(szRemoteAddr, hostname));
				printf("\tTCP[%d] Remote Port: %d\n", i,
					ntohs((u_short)pTcpTable->table[i].dwRemotePort));
				
				mylist2.emplace_front(s);
				zaehler++; //nächste zeile
/*
				for (int a = 0; a < 3; a++)
				{
					for (int b = 0; b < 3; b++)
					{
						std::cout << matrix[a][b] << " \n";
					}
					std::cout << std::endl;
				}
				*/
				//std::cout << matrix.alibaba[0][1] << " dasdasdasdadsadsadsa\n";
				
			}
		}
	}
	else {
		printf("\tGetExtendedTcpTable failed with %d\n", dwRetVal);
		FREE(pTcpTable);
		delete[] ports;
		//return 1;
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
	//	struct t_thing matrix = start();

	//dataGridView1->DataSource = NULL;
	dataGridView1->Rows->Clear();
	
	array<System::String^, 2>^ matrix = start();
	

	//System::Data::DataTable dt;
	//dt.Columns->Add("ProcessName");

	//System::Windows::Forms::DataGridViewComboBoxColumn^ dgCol = gcnew System::Windows::Forms::DataGridViewComboBoxColumn();
	
	

	int index = dataGridView1->Rows->Add();
	int index2 = dataGridView1->Rows->Add(matrix->Length);

	//std::string bobo = matrix.alibaba[0][2].c_str();
	//const char* l = bobo.c_str();

	//System::Windows::Forms::BindingSource binding;
	//binding.DataSource = matrix.alibaba;

	//bind datagridview to binding source
	//dataGridView1.DataSource = binding;


	//listView1->Items->Insert(0, l);
	//dataGridView1->Rows[index]->SetValues(l);
	
	int row = 30;
	int col = 4;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			dataGridView1->Rows[i]->Cells[j]->Value = matrix[i, j];
		}
	}

	//dataGridView1->Rows[0]->Cells[0]->Value = matrix[0, 0];
	//dataGridView1->Rows[0]->Cells[0]->Value = matrix[0, 0];
	

	//dataGridView1->Rows[2]->Cells[0]->Value = matrix[0, 2];
	//dataGridView1->Rows[3]->Cells[0]->Value = matrix[0, 3];
	//dataGridView1->Rows[index]->Cells[1]->Value= matrix.alibaba[0][2].c_str();
//	dataGridView1.Rows[index].Cells[1].Value = "1";
	
	//this.dataGridView1.Rows[index].Cells[2].Value = "Baqar";

	//std::cout << matrix.alibaba[0][1] << " dasdasdasdadsadsadsa\n";

	return System::Void();
}

System::Void CppCLRWinFormsProject::Form1::dataGridView1_CellContentClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e)
{
	/*
	std::string list33 = ("11/22/1968", "29", "Revolution 9",
		"Beatles"); 

	System::Data::DataTable dt;
	dt.Columns->Add("ProcessName");

	System::Windows::Forms::DataGridViewComboBoxColumn^ dgCol = gcnew System::Windows::Forms::DataGridViewComboBoxColumn();

	System::Windows::Forms::DataGridViewColumn^ comboboxColumn = dataGridView1->Columns[1];
	dataGridView1->Rows->Add("22");

	
		//.columns("ProcessName");

	//dt.Columns.Add("Category", typeof(string));
	*/
	return System::Void();
}
