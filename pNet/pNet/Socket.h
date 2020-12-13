#pragma once
#include "SocketHandle.h"
#include "PResult.h"
#include "SocketOptions.h"
#include "IPEndpoint.h"

namespace pNet 
{
	class Socket
	{
	public:
		Socket(SocketHandle handle = INVALID_SOCKET);
		pResult Create();
		pResult Close();
		SocketHandle GetHandle();
		
	private:
		pResult SetSocketOptions(SocketOption option, BOOL value);
		SocketHandle handle = INVALID_SOCKET;
	};

}
