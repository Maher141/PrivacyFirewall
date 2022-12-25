//https://learn.microsoft.com/de-de/windows/win32/api/iphlpapi/nf-iphlpapi-getipstatisticsex
/*
#ifndef UNICODE
#define UNICODE
#endif

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>

#pragma comment(lib, "iphlpapi.lib")

#define MALLOC(x) HeapAlloc(GetProcessHeap(), 0, (x))
#define FREE(x) HeapFree(GetProcessHeap(), 0, (x))

#include <iostream>
 
int main3()
{

    DWORD dwRetvalIpv4;
    DWORD dwRetvalIpv6;
    MIB_IPSTATS* pStatsIpv4;
    MIB_IPSTATS* pStatsIpv6;

    pStatsIpv4 = (MIB_IPSTATS*)MALLOC(sizeof(MIB_IPSTATS));
    pStatsIpv6 = (MIB_IPSTATS*)MALLOC(sizeof(MIB_IPSTATS));

    if (pStatsIpv4 == NULL) {
        wprintf(L"Unable to allocate memory for MIB_IPSTATS\n");
        exit(1);
    }
    dwRetvalIpv4 = GetIpStatisticsEx(pStatsIpv4, AF_INET);
    dwRetvalIpv6 = GetIpStatisticsEx(pStatsIpv6, AF_INET);
    if (dwRetvalIpv4 != NO_ERROR) {
        wprintf(L"GetIpStatistics call failed with %d\n", dwRetvalIpv4);
        exit(1);
    }
    else {
        wprintf(L"Number of IPV4 addresses: \t\t\t\t%u\n", pStatsIpv4->dwNumAddr);
        wprintf(L"Number of IPV6 addresses: \t\t\t\t%u\n", pStatsIpv6->dwNumAddr);
        
        
    }

    // Free memory allocated for the MIB_IPSTATS structure
    if (pStatsIpv4)
        FREE(pStatsIpv4);


    return 0;
}
*/