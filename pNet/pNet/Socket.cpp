#include "Socket.h"
#include <assert.h>

namespace pNet {
	Socket::Socket(SocketHandle handle)
		:handle(handle)
	{
		
	}

	pResult Socket::Create()
	{
		if (handle != INVALID_SOCKET)
		{
			return pResult::P_NotYetImplemented;
		}

		handle = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (handle == INVALID_SOCKET)
		{
			int error = WSAGetLastError();
			return pResult::P_NotYetImplemented;
		}
		if (SetSocketOptions(SocketOption::TCP_NoDelay, TRUE) != pResult::P_Success)
		{
			return pResult::P_NotYetImplemented;
		}
		return pResult::P_Success;
	}

	pResult Socket::Close()
	{
		if (handle == INVALID_SOCKET)
		{
			return pResult::P_NotYetImplemented;
		}

		int result = closesocket(handle);
		if (result != 0)
		{
			int error = WSAGetLastError();
			return pResult::P_NotYetImplemented;
		}
		
		handle = INVALID_SOCKET;
		return pResult::P_Success;
	}

	SocketHandle Socket::GetHandle()
	{
		return handle;
	}

	pResult Socket::SetSocketOptions(SocketOption option, BOOL value)
	{
		int result = 0;
		switch (option)
		{
		case SocketOption::TCP_NoDelay:
			result = setsockopt(handle, IPPROTO_TCP, TCP_NODELAY, (const char*)&value, sizeof(value));
			break;

		default:
			return pResult::P_NotYetImplemented;
		}

		if (result!=0) 
		{
			int error = WSAGetLastError();
			return pResult::P_NotYetImplemented;
		}
		return pResult::P_Success;
	}
}