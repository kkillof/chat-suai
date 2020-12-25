#pragma once
#define WIN32_LEAN_AND_MEAN
#include <WinSock2.h>
#include <vector>

namespace pNet
{
	class Packet
	{
	public:
		void Clear();
		void Append(const void* data, uint32_t size);

		Packet& operator << (uint32_t data);
		Packet& operator >> (uint32_t data);

		uint32_t extractionOffset = 0;
		std::vector<char> buffer;
	};
}