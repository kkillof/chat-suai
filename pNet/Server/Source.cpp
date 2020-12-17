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

					std::string buffer = "";
					while (true)
					{
						uint32_t bufferSize = 0;
						pResult result = newConnection.RecvALL(&bufferSize, sizeof(uint32_t));
						if (result != pResult::P_Success)
							break;

						bufferSize = ntohl(bufferSize); //convert buffer size from network byte order to host byte order due to integer endiannesss


						buffer.resize(bufferSize);
						result = newConnection.RecvALL(&buffer[0], bufferSize);
						if (result != pResult::P_Success)
							break;

						std::cout << "[" << bufferSize << "] - " << buffer << std::endl;
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