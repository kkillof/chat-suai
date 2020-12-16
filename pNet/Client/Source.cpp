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
			if (socket.Connect(IPEndpoint("127.0.0.1", 1111)) == pResult::P_Success)
			{
				std::cout << "Successfully connected to server" << std::endl;
				char buffer[256];
				strcpy_s(buffer, "Hello world\0");
				int bytesSent = 0;
				int result = pResult::P_Success;
				while (result == pResult::P_Success);
				{
					result = socket.Send(buffer, 256, bytesSent);
					std::cout << "Attempting to send chunk of data..." << std::endl;
					Sleep(500);
				}
			}
			else
			{
				std::cerr << "Connection to server failed" << std::endl;
			}
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