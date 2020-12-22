#pragma once
#include "SocketHandle.h"
#include "PResult.h"
#include "SocketOptions.h"
#include "IPEndpoint.h"
#include "Packet.h"

namespace pNet 
{
	class Socket
	{
	public:
		Socket(SocketHandle handle = INVALID_SOCKET);
		pResult Create();
		pResult Close();
		pResult Bind(IPEndpoint endpoint);
		pResult Listen(IPEndpoint endpoint, int backlog = 5);
		pResult Accept(Socket &outSocket);
		pResult Connect(IPEndpoint endpoint);
		pResult Send(void* data, int numberOfBytes, int &bytesSent);
		pResult Recv(const void* destination, int numberOfBytes, int& bytesReceived);
		pResult SendALL(const void* data, int numberOfBytes);
		pResult RecvALL(void* destination, int numberOfBytes);
		pResult Send(Packet& packet);
		pResult Recv(Packet& packet);
		SocketHandle GetHandle();
		
	private:
		pResult SetSocketOptions(SocketOption option, BOOL value);
		SocketHandle handle = INVALID_SOCKET;
	};

}
