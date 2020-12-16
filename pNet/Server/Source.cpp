//Server Code
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
			if (socket.Listen(IPEndpoint("0.0.0.0", 1111))==pResult::P_Success)
			{
				std::cout << "Socket successfully bound to port 1111" << std::endl;
				Socket newConnection;
				if (socket.Accept(newConnection) == pResult::P_Success)
				{
					std::cout << "New Connection accepted" << std::endl;
					
					char buffer[256];
					int bytesReceived = 0;
					int result = pResult::P_Success;
					while (result == pResult::P_Success)
					{
						result = newConnection.Recv(buffer, 256, bytesReceived);
						if (result != pResult::P_Success)
							break;
						std::cout << buffer << std::endl;
					}
					newConnection.Close();
				}
				else
				{
					std::cerr << "Failed to accept new connection" << std::endl;
				}
			}
			else
			{
				std::cerr << "Failed to bind socket to port 1111" << std::endl;
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