#pragma once
#define WIN32_LEAN_AND_MEAN
#include <WinSock2.h>

namespace pNet
{
	class Network
	{
	public:
		static bool Initialize();
		static void Shutdown();
	};
}