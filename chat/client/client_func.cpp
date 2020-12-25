#include "client.h"

void client_handler() 
{
	char msg[buffersize];
	char client_id[id_length];
	std::string client_id_buf;

	while (true) {
		short result_id = recv(Connection, client_id, id_length, NULL);
		short result = recv(Connection, msg, buffersize, NULL);

		if (result < 0) {
			std::cout << "\n\nThe server dropped the connection! Error code: " << WSAGetLastError() << std::endl;
			system("pause");
			exit(1);
		}
		else {
			client_id_buf = client_id;
			std::cout << "\n\n[" << client_id_buf << "] >> " << msg << std::endl;
			std::cout << "\nMessage >> ";
		}
	}
}

void Client::client_set_connection()
{
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);

	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		std::cout << "\nVersion check error!\n" << std::endl;
		system("pause");
		exit(1);
	}
	std::cout << "The version check was successful!" << std::endl;

	my_addr.sin_addr.s_addr = inet_addr(IP);
	my_addr.sin_port = htons(PORT);
	my_addr.sin_family = AF_INET;

	Connection = socket(AF_INET, SOCK_STREAM, NULL);

	std::cout << "\nConnecting to: " << IP << ':' << PORT << std::endl;

	while (connect(Connection, (SOCKADDR*)&my_addr, sizeof_myaddr) != 0)
	{
		std::cout << "\nTry to connect: " << IP << ':' << PORT << std::endl;
		Sleep(2500);
	}
	
	system("cls");
	std::cout << "\nThe connection to the server was successful! " << IP << ':' << PORT << std::endl;
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)client_handler, NULL, NULL, NULL);

	do {
		std::cout << "\nEnter your nickname(max 15 characters): ";
		getline(std::cin, nickname);

	} while (nickname[0] == 0 || nickname[0] == ' ');

	short nickname_result = send(Connection, nickname.c_str(), nickname.length() + 1, NULL);

	if (nickname_result == 1) {
		closesocket(Connection);
		return;
	}

	while (true) {
		std::cout << "\nMessage >> ";
		getline(std::cin, message);
		short result = send(Connection, message.c_str(), message.length() + 1, NULL);

		if (result < 0) {
			std::cout << "\nFailed to send message!\n" << std::endl;
			return;
		}
	}
}
