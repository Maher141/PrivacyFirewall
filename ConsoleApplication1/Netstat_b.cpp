//http://www.rohitab.com/discuss/topic/40685-how-to-get-list-of-processes-using-internet/

#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib,"psapi")
#pragma comment(lib,"iphlpapi")
#pragma comment(lib,"wsock32")
#include <windows.h>
#include <winsock.h>
#include <iphlpapi.h>
#include <psapi.h>
#include <iostream>
#include <vector>
using namespace std;
/*
char* dupcat(const char* s1, ...) { //... (ellipses) allow you to create functions where the number of parameters are not known beforehand
    int len;
    char* p, * q, * sn;
    va_list ap;

    len = strlen(s1);
    va_start(ap, s1);
    while (1) {
        sn = va_arg(ap, char*);
        if (!sn)
            break;
        len += strlen(sn); //returns length of the string
    }
    va_end(ap);

    p = new char[len + 1];
    strcpy(p, s1); //strcpy() copy string
    q = p + strlen(p);

    va_start(ap, s1);
    while (1) {
        sn = va_arg(ap, char*);
        if (!sn)
            break;
        strcpy(q, sn); //strcpy() copy string
        q += strlen(q);
    }
    va_end(ap);

    return p;
}

const char* processName(DWORD id) { //show process name
    HANDLE processHandle = NULL;   //store process information
    char filename[MAX_PATH];
    char* ret;
    char* my_c_string;
    const char* name = "Failed to get module filename";
    const char* p = name;
    const char* name2 = "Failed to open process.";
    const char* p2 = name;

    processHandle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, id); //Required to retrieve certain information about a process, such as its token, exit code, and priority class. False, processes do not inherit this handle. return value is an open handle to the specified process. 
    if (processHandle != NULL) {
        if (GetModuleBaseNameA(processHandle, NULL, filename, sizeof(filename)) == 0) { //GetModuleBaseNameA checks if processHandle is empty
            return p; //"Failed to get module filename.";
        }
        else {
            ret = dupcat(filename, 0);
            return ret;
        }
        CloseHandle(processHandle);
    }
    return p2; // "Failed to open process.";
}

int main() {
    vector<unsigned char> buffer;
    DWORD dwSize = sizeof(MIB_TCPTABLE_OWNER_PID);
    DWORD dwRetValue = 0;
    DWORD dwRetValue2 = 0;
    //UDP_TABLE_CLASS *UdpTable = 1;

    do {
        buffer.resize(dwSize, 0);
        dwRetValue = GetExtendedTcpTable(buffer.data(), &dwSize, TRUE, AF_INET, TCP_TABLE_OWNER_PID_ALL, 0);
      //  dwRetValue2 = GetExtendedUdpTable(buffer.data(), &dwSize, TRUE, AF_INET, MIB_UDP6TABLE_OWNER_PID, 0);
    } while (dwRetValue == ERROR_INSUFFICIENT_BUFFER);
    if (dwRetValue == ERROR_SUCCESS)
    {
        PMIB_TCPTABLE_OWNER_PID ptTable = reinterpret_cast<PMIB_TCPTABLE_OWNER_PID>(buffer.data());
        cout << "Number of Entries: " << ptTable->dwNumEntries << endl << endl;
        for (DWORD i = 0; i < ptTable->dwNumEntries; i++) {
            DWORD pid = ptTable->table[i].dwOwningPid;
            cout << "PID: " << pid << endl;
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
                << ":"
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
                << ":"
                << htons((unsigned short)ptTable->table[i].dwRemotePort)
                << endl;

            cout << endl;
        }
    }
    cin.get();
}

*/