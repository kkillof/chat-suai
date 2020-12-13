//Client code

#include <iostream>
#include <pNet/includes.h>
using namespace pNet;

int main()
{
	if (Network::Initialize())
	{
		std::cout << "Winsock api succesfully initialized" << std::endl;
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
}