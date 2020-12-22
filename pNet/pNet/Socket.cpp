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
			return pResult::P_GenericError;
		}

		handle = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (handle == INVALID_SOCKET)
		{
			int error = WSAGetLastError();
			return pResult::P_GenericError;
		}
		if (SetSocketOptions(SocketOption::TCP_NoDelay, TRUE) != pResult::P_Success)
		{
			return pResult::P_GenericError;
		}
		return pResult::P_Success;
	}

	pResult Socket::Close()
	{
		if (handle == INVALID_SOCKET)
		{
			return pResult::P_GenericError;
		}

		int result = closesocket(handle);
		if (result != 0)
		{
			int error = WSAGetLastError();
			return pResult::P_GenericError;
		}
		
		handle = INVALID_SOCKET;
		return pResult::P_Success;
	}

	pResult Socket::Bind(IPEndpoint endpoint)
	{
		sockaddr_in addr = endpoint.GetSockAddr();
		int result = bind(handle, (sockaddr*)(&addr), sizeof(sockaddr_in));
		if (result != 0)
		{
			int error = WSAGetLastError();
			return pResult::P_GenericError;
		}
		return pResult::P_Success;
	}

	pResult Socket::Listen(IPEndpoint endpoint, int backlog)
	{
		if (Bind(endpoint) != pResult::P_Success)
		{
			return pResult::P_GenericError;
		}

		int result = listen(handle, backlog);
		if (result != 0)
		{
			int error = WSAGetLastError();
			return pResult::P_GenericError;
		}

		return pResult::P_Success;
	}

	pResult Socket::Accept(Socket& outSocket)
	{
		sockaddr_in addr = {};
		int len = sizeof(sockaddr_in);
		SocketHandle acceptedConnectionHandle = accept(handle, (sockaddr*)(&addr), &len);
		if (acceptedConnectionHandle == INVALID_SOCKET)
		{
			int error = WSAGetLastError();
			return pResult::P_GenericError;
		}
		IPEndpoint newConnectionEndpoint((sockaddr*)&addr);
		outSocket = Socket(acceptedConnectionHandle);
		return pResult::P_Success;
	}

	pResult Socket::Connect(IPEndpoint endpoint)
	{
		sockaddr_in addr = endpoint.GetSockAddr();
		int result = connect(handle, (sockaddr*)(&addr), sizeof(sockaddr_in));
		if (result != 0)
		{
			int error = WSAGetLastError();
			return pResult::P_GenericError;
		}
		return pResult::P_Success;
	}

	pResult Socket::Send(void* data, int numberOfBytes, int& bytesSent)
	{
		bytesSent = send(handle, (const char*)data, numberOfBytes, NULL);
		if (bytesSent == SOCKET_ERROR)
		{
			int error = WSAGetLastError();
			return pResult::P_GenericError;
		}
		return pResult::P_Success;
	}

	pResult Socket::Recv(const void* destination, int numberOfBytes, int& bytesReceived)
	{
		bytesReceived = recv(handle, (char*)destination, numberOfBytes, NULL);
		if (bytesReceived == 0) 
		{
			return pResult::P_GenericError;
		}
		if (bytesReceived == SOCKET_ERROR)
		{
			int error = WSAGetLastError();
			return pResult::P_GenericError;
		}
		return pResult::P_Success;
	}

	pResult Socket::SendALL(const void* data, int numberOfBytes)
	{
		int totalBytesSent = 0;
		while (totalBytesSent < numberOfBytes)
		{
			int bytesRemaining = numberOfBytes - totalBytesSent;
			int bytesSent=0;
			char* bufferOffset = (char*)data + totalBytesSent;
			pResult result = Send(bufferOffset, bytesRemaining, bytesSent);
			if (result != pResult::P_Success) 
			{
				return pResult::P_GenericError;
			}
			totalBytesSent += bytesSent;
		}

		return pResult::P_Success;
	}

	pResult Socket::RecvALL(void* destination, int numberOfBytes)
	{
		int totalBytesReceived = 0;
		while (totalBytesReceived < numberOfBytes)
		{
			int bytesRemaining = numberOfBytes - totalBytesReceived;
			int bytesSent = 0;
			char* bufferOffset = (char*)destination + totalBytesReceived;
			pResult result = Recv(bufferOffset, bytesRemaining, bytesSent);
			if (result != pResult::P_Success)
			{
				return pResult::P_GenericError;
			}
			totalBytesReceived += bytesSent;
		}

		return pResult::P_Success;
	}

	pResult Socket::Send(Packet& packet)
	{
		uint32_t encodedPacketSize = htonl(packet.buffer.size());
		pResult result = SendALL(&encodedPacketSize, sizeof(uint32_t));
		if (result != pResult::P_Success)
			return pResult::P_GenericError;

		result = SendALL(packet.buffer.data(), packet.buffer.size());
		if (result != pResult::P_Success)
			return pResult::P_GenericError;
		
		return pResult::P_Success;
	}

	pResult Socket::Recv(Packet& packet)
	{
		packet.Clear();

		uint32_t encodedSize = 0;
		pResult result = RecvALL(&encodedSize, sizeof(uint32_t));
		if (result != pResult::P_Success)
		{
			return pResult::P_GenericError;
		}

		uint32_t bufferSize = ntohl(encodedSize);
		packet.buffer.resize(bufferSize);
		result = RecvALL(&packet.buffer[0], bufferSize);
		if (result != pResult::P_Success)
		{
			return pResult::P_GenericError;
		}
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
			return pResult::P_GenericError;
		}

		if (result!=0) 
		{
			int error = WSAGetLastError();
			return pResult::P_GenericError;
		}
		return pResult::P_Success;
	}
}