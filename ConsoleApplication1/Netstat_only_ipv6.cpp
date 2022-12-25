#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <ws2tcpip.h> 
#include <iphlpapi.h>
#include <iostream>
#include <vector>
#include <in6addr.h>
#include <Ws2ipdef.h>
#include <ws2tcpip.h>
#include <Mstcpip.h>
#include <ip2string.h>


#pragma comment(lib, "psapi")
#pragma comment(lib, "iphlpapi")
#pragma comment(lib, "wsock32")
#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")

using namespace std;



#define MALLOC(x) HeapAlloc(GetProcessHeap(), 0, (x))
#define FREE(x) HeapFree(GetProcessHeap(), 0, (x))

#include <iostream>
#include <vector>
#include <WS2tcpip.h>
#include <winsock2.h>


// link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")

/*

int main()
{
    vector<BYTE> buffer;
    DWORD dwSize = sizeof(MIB_TCP6TABLE_OWNER_PID);
    DWORD dwRetValue = 0;

    in6_addr in6_localAddr, in6_remoteAddr;
    char szLocalAddr[INET6_ADDRSTRLEN], szRemoteAddr[INET6_ADDRSTRLEN];
    ULONG ulAddrLen;


    addrinfo* ptr = nullptr;
    addrinfo* res = nullptr;
    addrinfo hints;
    int addr_ret;

    memset(&hints, 0, sizeof(hints));

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family = AF_UNSPEC;

    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_family = AF_INET6;

    WSAData wsaData;
    LPSOCKADDR ip_v6;
    int count = 0;
    int retval;
    DWORD ip_v6_strlen = 46;
    char ip_v6_str[46];
    const char* hostname = "DESKTOP-BRNR41U";

    int wsaRes = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (wsaRes != 0) {
        cerr << "WSAload failed：" << wsaRes << endl;
        system("pause");
        return -1;
    }

    //para1can be ip\dns, para2 can be service/port type like 80/http 443/https
    addr_ret = getaddrinfo(hostname, "443", &hints, &res);


    do
    {
        buffer.resize(dwSize, 0);
        dwRetValue = GetExtendedTcpTable(buffer.data(), &dwSize, TRUE, AF_INET6, TCP_TABLE_OWNER_PID_ALL, 0);

    } while (dwRetValue == ERROR_INSUFFICIENT_BUFFER);

    if (dwRetValue == ERROR_SUCCESS)
    {
        PMIB_TCP6TABLE_OWNER_PID ptTable = reinterpret_cast<PMIB_TCP6TABLE_OWNER_PID>(buffer.data());

        cout << "Number of Entries: " << ptTable->dwNumEntries << endl << endl;

        for (DWORD i = 0; i < ptTable->dwNumEntries; i++)
        {
            for (ptr = (addrinfo*)ptTable->table[i].ucLocalAddr; ptr != NULL; ptr = ptr->ai_next) {
                cout << "The " << count++ << "ip address:" << endl;
               // switch (ptr->ai_family)
                memcpy(&in6_localAddr.u.Byte, ptTable->table[i].ucLocalAddr, 16);
                memcpy(&in6_remoteAddr.u.Byte, ptTable->table[i].ucRemoteAddr, 16);

                ulAddrLen = INET6_ADDRSTRLEN;
                RtlIpv6AddressToStringExA(&in6_localAddr, ptTable->table[i].dwLocalScopeId, ptTable->table[i].dwLocalPort, szLocalAddr, &ulAddrLen);

                ulAddrLen = INET6_ADDRSTRLEN;
                RtlIpv6AddressToStringExA(&in6_remoteAddr, ptTable->table[i].dwRemoteScopeId, ptTable->table[i].dwRemotePort, szRemoteAddr, &ulAddrLen);

                cout << "--------------------------------\n";

                cout << "PID: " << ptTable->table[i].dwOwningPid << endl;
                cout << "State: " << ptTable->table[i].dwState << endl;
                cout << "Local: " << szLocalAddr << endl;
                ip_v6 = (LPSOCKADDR)ptr->ai_addr;
#pragma warning(disable : 4996)
                retval = WSAAddressToStringA(ip_v6, (DWORD)ptr->ai_addrlen, NULL, ip_v6_str, &ip_v6_strlen);
                cout << ip_v6_str << endl;
                cout << "Remote: " << szRemoteAddr << endl;

                cout << endl;
            }
        }
    }
    cin.get();
    freeaddrinfo(res);
    WSACleanup();
    system("pause");
    return 0;
}

*/


/*

int main()
{
    vector<BYTE> buffer;
    DWORD dwSize = sizeof(MIB_TCP6TABLE_OWNER_PID);
    DWORD dwRetValue = 0;

    in6_addr in6_localAddr, in6_remoteAddr;
    char szLocalAddr[INET6_ADDRSTRLEN], szRemoteAddr[INET6_ADDRSTRLEN];
    ULONG ulAddrLen;

    do
    {
        buffer.resize(dwSize, 0);
        dwRetValue = GetExtendedTcpTable(buffer.data(), &dwSize, TRUE, AF_INET6, TCP_TABLE_OWNER_PID_ALL, 0);

    } while (dwRetValue == ERROR_INSUFFICIENT_BUFFER);

    if (dwRetValue == ERROR_SUCCESS)
    {
        PMIB_TCP6TABLE_OWNER_PID ptTable = reinterpret_cast<PMIB_TCP6TABLE_OWNER_PID>(buffer.data());

        cout << "Number of Entries: " << ptTable->dwNumEntries << endl << endl;

        for (DWORD i = 0; i < ptTable->dwNumEntries; i++)
        {
            memcpy(&in6_localAddr.u.Byte, ptTable->table[i].ucLocalAddr, 16);
            memcpy(&in6_remoteAddr.u.Byte, ptTable->table[i].ucRemoteAddr, 16);

            ulAddrLen = INET6_ADDRSTRLEN;
            RtlIpv6AddressToStringExA(&in6_localAddr, ptTable->table[i].dwLocalScopeId, ptTable->table[i].dwLocalPort, szLocalAddr, &ulAddrLen);

            ulAddrLen = INET6_ADDRSTRLEN;
            RtlIpv6AddressToStringExA(&in6_remoteAddr, ptTable->table[i].dwRemoteScopeId, ptTable->table[i].dwRemotePort, szRemoteAddr, &ulAddrLen);

            cout << "--------------------------------\n";

            cout << "PID: " << ptTable->table[i].dwOwningPid << endl;
            cout << "State: " << ptTable->table[i].dwState << endl;
            cout << "Local: " << szLocalAddr << endl;
            cout << "Remote: " << szRemoteAddr << endl;

            cout << endl;
        }
    }

    cin.get();
}

*/