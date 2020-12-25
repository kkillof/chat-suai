//Server Code
#include <iostream>
#include <pNet/includes.h>
using namespace pNet;

int main()
{
	if (Network::Initialize())
	{
		std::cout << "Winsock api successfully initialized." << std::endl;

		Socket socket;
		if (socket.Create() == pResult::P_Success)
		{
			std::cout << "Socket successfully created." << std::endl;
			if (socket.Listen(IPEndpoint("0.0.0.0", 4790)) == pResult::P_Success)
			{
				std::cout << "Socket successfully listening on port 4790." << std::endl;
				Socket newConnection;
				if (socket.Accept(newConnection) == pResult::P_Success)
				{
					std::cout << "New connection accepted." << std::endl;
					uint32_t a(0), b(0), c(0);
					Packet packet;
					while (true)
					{
						
						pResult result = newConnection.Recv(packet);
						if (result != pResult::P_Success)
							break;

						packet >> a >> b >> c;
						std::cout << a << "," << b << "," << c << std::endl;
					}

					newConnection.Close();
				}
				else
				{
					std::cerr << "Failed to accept new connection." << std::endl;
				}
			}
			else
			{
				std::cerr << "Failed to listen on port 4790." << std::endl;
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