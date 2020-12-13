#pragma once
#include <string>
#include <vector>

namespace pNet 
{
	class IPEndpoint
	{
	public:
		IPEndpoint(const char* ip, unsigned short port);
		std::vector<uint8_t> GetIPBytes();
		std::string GetHostname();
		std::string GetIPString();
		unsigned short GetPort();
	private:
		std::string hostname;
		std::string ip_string;
		std::vector<uint8_t> ip_bytes;
		unsigned short port = 0;
	};
}