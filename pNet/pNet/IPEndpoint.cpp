#include "IPEndpoint.h"


pNet::IPEndpoint::IPEndpoint(const char* ip, unsigned short port)
{
    this->port = port;
    in_addr addr; //store adress
    int result = inet_pton(AF_INET, ip, &addr);
    
    if (result == 1)
    {
        if (addr.S_un.S_addr != INADDR_NONE)
        {
            ip_string = ip;
            hostname = ip;
            ip_bytes.resize(sizeof(ULONG));
            memcpy(&ip_bytes[0], &addr.S_un.S_addr, sizeof(ULONG));
            return;
        }
    }
    addrinfo hints = {};
    hints.ai_family = AF_INET;
    addrinfo* hostinfo = nullptr;
    result = getaddrinfo(ip, NULL, &hints, &hostinfo);
    if (result == 0)
    {
        sockaddr_in* hostaddr = reinterpret_cast<sockaddr_in*>(hostinfo->ai_addr);
        ip_string.resize(16);
        inet_ntop(AF_INET, &hostaddr->sin_addr, &ip_string[0], 16);

        hostname = ip;
        ULONG ip_long = hostaddr->sin_addr.S_un.S_addr;
        ip_bytes.resize(sizeof(ULONG));
        memcpy(&ip_bytes[0], &ip_long, sizeof(ULONG));
        freeaddrinfo(hostinfo);
        return;
    }


}

pNet::IPEndpoint::IPEndpoint(sockaddr* addr)
{
    sockaddr_in* addrv4 = reinterpret_cast<sockaddr_in*>(addr);
    port = ntohs(addrv4->sin_port);
    ip_bytes.resize(sizeof(ULONG));
    memcpy(&ip_bytes[0], &addrv4->sin_addr, sizeof(ULONG));
    ip_string.resize(16);
    inet_ntop(AF_INET, &addrv4->sin_addr, &ip_string[0], 16);
    hostname = ip_string;
}

std::vector<uint8_t> pNet::IPEndpoint::GetIPBytes()
{
    return ip_bytes;
}

std::string pNet::IPEndpoint::GetHostname()
{
    return hostname;
}

std::string pNet::IPEndpoint::GetIPString()
{
    return ip_string;
}

unsigned short pNet::IPEndpoint::GetPort()
{
    return port;
}

sockaddr_in pNet::IPEndpoint::GetSockAddr()
{
    sockaddr_in addr = {};
    addr.sin_family = AF_INET;
    memcpy(&addr.sin_addr, &ip_bytes[0], sizeof(ULONG));
    addr.sin_port = htons(port);

    return addr;
}
