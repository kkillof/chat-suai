//Server Code
#include <iostream>
#include <pNet/includes.h>
using namespace pNet;

int main()
{
	
	if (Network::Initialize())
	{
		std::cout << "Winsock api succesfully initialized" << std::endl;

		IPEndpoint test("192.168.0.2", 1111);
		std::cout << "Hostname: " << test.GetHostname() << std::endl;
		std::cout << "IP: " << test.GetIPString() << std::endl;
		std::cout << "Port: " << test.GetPort() << std::endl;
		std::cout << "IP_Bytes: " << std::endl;
		for (auto& digit : test.GetIPBytes())
		{
			std::cout << (int)digit << std::endl;
		}
		Socket socket;
		if (socket.Create() == pResult::P_Success)
		{
			std::cout << "Socket successfully created." << std::endl;
			socket.Close();
		}
		else
		{
			std::cerr << "Socket failed to create." << std::endl;
		}
	}
	Network::Shutdown();
	system("pause");
	return 0;
}