#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <iostream>
#include <string>
#include <WS2tcpip.h>
#include <unordered_map>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

class TcpServer
{
private:
	string _host;
	int _port;

	SOCKET _listenSocket;
	unordered_map<SOCKET, sockaddr_in> clientConnections;

public:
	TcpServer(string ip, int port);
	~TcpServer();

	void Start();
	SOCKET Accept();
	void Close(SOCKET clientSocket);
	void Stop();
};

#endif 