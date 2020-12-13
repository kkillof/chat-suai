#include "IPEndpoint.h"
#include <WS2tcpip.h>

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
