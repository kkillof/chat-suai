#include "server.h"

void client_handler(int index)
{
	char id_buffer[SIZECONNECTIONS];
	const short id_length = 15;

	char client_buf[id_length];
	char msg[buffersize];

	char* p = itoa(Counter, id_buffer, 10);
	short client_id_result = recv(Connections[index], client_buf, id_length, 0);

	if (client_id_result == id_length) {
		closesocket(Connections[index]); //overflow
		Counter--;
		return;
	}
	else {
		strcat(client_buf, "_");
		strcat(client_buf, p);
		std::cout << "\n\nClient connected! User ID:" << client_buf << std::endl;
	}

	std::string client_id = client_buf;

	while (true) {
		short result = recv(Connections[index], msg, buffersize, 0);

		if (result == buffersize) {
			closesocket(Connections[index]); //overflow
			std::cout << "\nBuffer overflow! " << "This User ID:[" << client_id << "] has overflowed the buffer!\n";
			Counter--;
			return;
		}

		if (result < 0) {
			std::cout << "\nConnection dropped! User ID:[" << client_id << "] Error code: " << WSAGetLastError() << std::endl;
			closesocket(Connections[index]); // connection refused
			Counter--;
			return;
		}

		for (int i = 0; i < Counter; i++) {
			if (i == index) {
				continue;
			}

			if (*msg == ' ') { //ignoring whitespace
				continue;
			}

			if (result == 1) { //ignore enter
				continue;
			}
			else {
				send(Connections[i], client_id.c_str(), client_id.length() + 1, NULL);
				send(Connections[i], msg, result, NULL);
			}
		}
	}
}

void Server::set_sock_bind_listen()
{
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);

	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		std::cout << "\nVersion check error!\n" << std::endl;
		exit(1);
	}
	std::cout << "The version check was successful!\n" << std::endl;

	my_addr.sin_addr.s_addr = inet_addr(IP);
	my_addr.sin_port = htons(PORT);
	my_addr.sin_family = AF_INET;

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
	short result_bind = bind(sListen, (SOCKADDR*)&my_addr, sizeof_myaddr);
	short listen_sock = listen(sListen, SOMAXCONN);

	if (result_bind == SOCKET_ERROR) {
		std::cout << "\nBind failed with error: " << WSAGetLastError() << std::endl;
		system("pause");
		exit(1);
	}
	else {
		std::cout << "\nBinding the socket to the address was successful!\n" << std::endl;
	}

	if (listen_sock == INVALID_SOCKET) {
		std::cout << "\nStart listening error: " << WSAGetLastError() << std::endl;
		system("pause");
		exit(1);
	}
	else {
		std::cout << "\nStart listening successfully!\n" << std::endl;
	}

	MessageBoxA(NULL, "\nThe server is running!\n", titles.box_title, MB_OK);
	system("cls");
	std::cout << "\nStart listening on ip and port: " << IP << ":" << PORT << std::endl << std::endl;

	for (int i = 0; i < SIZECONNECTIONS; i++) {
		SOCKET newConnection = accept(sListen, (SOCKADDR*)&my_addr, &sizeof_myaddr);
		if (newConnection == 0) {
			std::cout << "\nConnection error!\n";
		}
		else {
			Counter++;
			Connections[i] = newConnection;
			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)client_handler, (LPVOID)(i), NULL, NULL);
		}
	}
}