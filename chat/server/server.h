#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)
#pragma once
#include <winsock2.h>
#include <iostream>
#include <windows.h>

constexpr short SIZECONNECTIONS = 50;
constexpr short buffersize = 256;
static int Counter = 0;
static SOCKET Connections[SIZECONNECTIONS];

class Server
{
	int sizeof_myaddr = sizeof(my_addr);
	const short PORT;
	const char* IP;

	SOCKADDR_IN my_addr;

	struct ProgramTitles
	{
		const char* box_title = "Message_from_server";
		const char* application_title = "Server.exe";

	} titles;

public:
	Server(const char* ip, const short port) : IP(ip), PORT(port)
		{
			SetConsoleTitleA(titles.application_title);
			set_sock_bind_listen();
		}

	void set_sock_bind_listen(); 
};
