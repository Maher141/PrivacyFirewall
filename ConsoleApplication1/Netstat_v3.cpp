#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
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

#pragma comment(lib,"psapi")
#pragma comment(lib,"iphlpapi")
#pragma comment(lib,"wsock32")
#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")

using namespace std;

//BEIDES IPV4 UND 6

/*
void tipi() {
    WSADATA wsaData = { 0 };
    int iResult = 0;
    DWORD dwRetval;
    struct sockaddr_in saGNI;
    char hostname[NI_MAXHOST];
    char servInfo[NI_MAXSERV];
    std::string ip = "66.249.68.9";
    int port = 25;

    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult == 0) {
        saGNI.sin_family = AF_INET;
        saGNI.sin_addr.s_addr = inet_addr(ip.c_str());
        saGNI.sin_port = htons(port);

        dwRetval = getnameinfo((struct sockaddr*)&saGNI,
            sizeof(struct sockaddr),
            hostname,
            NI_MAXHOST, servInfo, NI_MAXSERV, NI_NUMERICSERV);

        if (dwRetval == 0) {
            cout << "IPAddress : " << hostname << endl;
        }
    }
}

char* dupcat(const char* s1, ...) {
    int len;
    char* p, * q, * sn;
    va_list ap;
    
    len = strlen(s1);
    va_start(ap, s1);
    while (1) { //infinite loop
        sn = va_arg(ap, char*);
        if (!sn)
            break;
        len += strlen(sn); //returns the length of the given C-string
    }
    va_end(ap);
  
    p = new char[len + 1];
    strcpy(p, s1);
    q = p + strlen(p);

    va_start(ap, s1);
    while (1) { //infinite loop
        sn = va_arg(ap, char*);
        if (!sn)
            break;
        strcpy(q, sn);
        q += strlen(q); //
    }
    va_end(ap);

    return p;
}

char* processName(DWORD id) {
    HANDLE processHandle = NULL; //catch return of creation of new process
    char filename[MAX_PATH];
    char* ret;
    char* ch = new char[32];
    strcpy_s(ch,32, "Failed to get module filename"); //copies a string
    char* ch2 = new char[32];
    strcpy_s(ch2, 32, "Failed to open process."); //copies a string

    processHandle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, id); //Opens an existing local process object.
    if (processHandle != NULL) {
        if (GetModuleBaseNameA(processHandle, NULL, filename, sizeof(filename)) == 0) { //Retrieves the base name of the specified module.
            return ch;
        }
        else {
            ret = dupcat(filename, 0);
            return ret;
        }
        CloseHandle(processHandle); //Closes an open object handle.
    }
    return ch;
}


int main()
{


    vector<unsigned char> buffer;
    DWORD dwSize = sizeof(MIB_TCPTABLE_OWNER_PID);
    DWORD dwRetValue = 0;

    // repeat till buffer is big enough
    do
    {
        buffer.resize(dwSize, 0);
        dwRetValue = GetExtendedTcpTable(buffer.data(), &dwSize, TRUE, AF_INET, TCP_TABLE_OWNER_PID_ALL, 0);

    } while (dwRetValue == ERROR_INSUFFICIENT_BUFFER);

    if (dwRetValue == ERROR_SUCCESS)
    {

        // cast to access element values
        PMIB_TCPTABLE_OWNER_PID ptTable = reinterpret_cast<PMIB_TCPTABLE_OWNER_PID>(buffer.data());

        cout << "Number of Entries: " << ptTable->dwNumEntries << endl << endl;


        // array starts with index 0, count starts by 1
        for (DWORD i = 0; i < ptTable->dwNumEntries; i++)
        {
            DWORD pid = ptTable->table[i].dwOwningPid;
            //if (ptTable->table[i].dwOwningPid > 0) { //skip System Idle Process who is on PID = 0
                cout << "PID: " << ptTable->table[i].dwOwningPid << endl;
                cout << "Name: " << processName(ptTable->table[i].dwOwningPid) << endl;
                cout << "State: " << ptTable->table[i].dwState << endl;

                cout << "Local: "
                    << (ptTable->table[i].dwLocalAddr & 0xFF)
                    << "."
                    << ((ptTable->table[i].dwLocalAddr >> 8) & 0xFF)
                    << "."
                    << ((ptTable->table[i].dwLocalAddr >> 16) & 0xFF)
                    << "."
                    << ((ptTable->table[i].dwLocalAddr >> 24) & 0xFF)
                    << "/"
                    << htons((unsigned short)ptTable->table[i].dwLocalPort)
                    << endl;

                cout << "Remote: "
                    << (ptTable->table[i].dwRemoteAddr & 0xFF)
                    << "."
                    << ((ptTable->table[i].dwRemoteAddr >> 8) & 0xFF)
                    << "."
                    << ((ptTable->table[i].dwRemoteAddr >> 16) & 0xFF)
                    << "."
                    << ((ptTable->table[i].dwRemoteAddr >> 24) & 0xFF)
                    << "/"
                    << htons((unsigned short)ptTable->table[i].dwRemotePort)
                    << endl;

                cout << endl;

          //  }
        }
    } cin.get();
}

/*

    /////
    
    vector<unsigned char> buffer2;
    DWORD dwSize2 = sizeof(MIB_TCP6TABLE_OWNER_PID);
    UCHAR dwRetValue2 = 0;
    // repeat till buffer is big enough
    do
    {
        buffer2.resize(dwSize2, 0);
        dwRetValue2 = GetExtendedTcpTable(buffer2.data(), &dwSize2, TRUE, AF_INET6, TCP_TABLE_OWNER_PID_ALL, 0);

    } while (dwRetValue2 == ERROR_INSUFFICIENT_BUFFER);

    if (dwRetValue2 == ERROR_SUCCESS)
    {
        // good case

        // cast to access element values
        PMIB_TCP6TABLE_OWNER_PID ptTable = reinterpret_cast<PMIB_TCP6TABLE_OWNER_PID>(buffer2.data());
        //PMIB_TCP6ROW_OWNER_MODULE  ptTable2 = reinterpret_cast<PMIB_TCP6ROW_OWNER_MODULE>(buffer2.data());

        cout << "Number of Entries: " << ptTable->dwNumEntries << endl << endl;

        // caution: array starts with index 0, count starts by 1
        for (DWORD i = 0; i < ptTable->dwNumEntries; i++)
        {

            DWORD pid = ptTable->table[i].dwOwningPid;
            UCHAR* lol = ptTable->table[i].ucLocalAddr;
            printf("%s", "--------------------------------\n");
            printf("%u", (unsigned char)ptTable->table[i].ucLocalAddr);
            printf("%s", "\n");
            if (ptTable->table[i].dwOwningPid > 0) { //skip System Idle Process who is on PID = 0

                cout << "PID: " << ptTable->table[i].dwOwningPid << endl;
                cout << "Name: " << processName(ptTable->table[i].dwOwningPid) << endl;
                cout << "State: " << ptTable->table[i].dwState << endl;
                cout << "Local: "
                    << (ptTable->table[i].ucLocalAddr )                                                //(ptTable->table[i].ucLocalAddr & 0xFF)
                    << ":"
                    << ((ptTable->table[i].ucLocalAddr))
                    << ":"
                    << ((ptTable->table[i].ucLocalAddr))
                    << ":"
                    << ((ptTable->table[i].ucLocalAddr))
                    << ":"
                    << htons((unsigned short)ptTable->table[i].dwLocalPort)
                    << endl;

                cout << "Remote: "
                    << (ptTable->table[i].ucRemoteAddr)
                    << ":"
                    << ((ptTable->table[i].ucRemoteAddr))
                    << ":"
                    << ((ptTable->table[i].ucRemoteAddr))
                    << ":"
                    << ((ptTable->table[i].ucRemoteAddr))
                    << ":"
                    << htons((unsigned short)ptTable->table[i].dwRemotePort)
                    << endl;

                cout << endl;

            }
        }
    }
    

       // cin.get();



}


*/