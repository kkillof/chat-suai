#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)
#pragma once
#include <winsock2.h>
#include <iostream>
#include <string>
#include <time.h>

static SOCKET Connection;
constexpr int buffersize = 256;
constexpr short id_length = 15;

class Client
{
	int sizeof_myaddr = sizeof(my_addr);
	std::string message;
	std::string nickname;

	const int PORT;
	const char* IP;

	SOCKADDR_IN my_addr;

	struct  Program_Titles
	{
		const char* box_title = "Message_from_client";
		const char* application_title = "client.exe";

	} titles;

public:
	Client(const char* ip, const int port) : IP(ip), PORT(port)
	{
		SetConsoleTitleA(titles.application_title);
		client_set_connection();
	}

	void client_set_connection();
};