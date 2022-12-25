//#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <ws2tcpip.h> 
#include <iphlpapi.h>
#include <iostream>
#include <vector>
#include <in6addr.h>
#include <Ws2ipdef.h>
#include <mstcpip.h>
#include <winapifamily.h>
#include <ip2string.h>
#include <Windows.h>

#define INITGUID
#include <guiddef.h>

#define __IP2STRING__


#pragma comment(lib, "Onecore")
#pragma comment(lib, "psapi")
#pragma comment(lib, "iphlpapi")
#pragma comment(lib, "wsock32")
#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")

#define stdin  (__acrt_iob_func(0))
#define stdout (__acrt_iob_func(1))
#define stderr (__acrt_iob_func(2))


using namespace std;
/*
int main()
{
    vector<BYTE> buffer;
    DWORD dwSize = sizeof(MIB_TCP6TABLE_OWNER_PID);
    DWORD dwRetValue = 0;

    in6_addr in6_localAddr, in6_remoteAddr; //The IN6_ADDR structure specifies an IPv6 transport address.
    char szLocalAddr[INET6_ADDRSTRLEN], szRemoteAddr[INET6_ADDRSTRLEN]; //128-bit ipv6 address
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
            printf("%s", "--------------------------------\n");
            printf("%u", (unsigned char)ptTable->table[i].ucLocalAddr);
            printf("%s", "\n");

            memcpy(&in6_localAddr.u.Byte, ptTable->table[i].ucLocalAddr, 16); //copies n characters from memory area src to memory area dest
            memcpy(&in6_remoteAddr.u.Byte, ptTable->table[i].ucRemoteAddr, 16); //dest, src, length

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