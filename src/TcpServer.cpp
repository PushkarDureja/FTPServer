#include "TcpServer.h"

TcpServer::TcpServer(string ip, int port) :_host(ip), _port(port), _listenSocket(-1) {}

TcpServer::~TcpServer() {
	Stop();
}

void TcpServer::Start() {
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);
	int wsOK = WSAStartup(ver, &wsData);
	if (wsOK != 0) {
		cerr << "Can't initialize Winsock! Quitting" << endl;
		return;
	}

	// Create a socket
	_listenSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (_listenSocket == INVALID_SOCKET) {
		cerr << "Can't create socket! Quitting" << endl;
		WSACleanup();
		return;
	}

	// Bind the socket to an IP address and port
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(_port);
	inet_pton(AF_INET, _host.c_str(), &hint.sin_addr);

	if (bind(_listenSocket, (sockaddr*)&hint, sizeof(hint)) == SOCKET_ERROR) {
		cerr << "Can't bind socket! Quitting" << endl;
		closesocket(_listenSocket);
		WSACleanup();
		return;
	}

	// Tell Winsock the socket is for listening
	if (listen(_listenSocket, SOMAXCONN) == SOCKET_ERROR) {
		cerr << "Can't listen on socket! Quitting" << endl;
		closesocket(_listenSocket);
		WSACleanup();
		return;
	}
}

SOCKET TcpServer::Accept() {
	sockaddr_in client;
	int clientSize = sizeof(client);
	SOCKET clientSocket = accept(_listenSocket, (sockaddr*)&client, &clientSize);

	if (clientSocket == INVALID_SOCKET) {
		cerr << "Error in accept()! Quitting" << endl;
		closesocket(_listenSocket);
		WSACleanup();
		return -1;
	}
	clientConnections[clientSocket] = client;

	return clientSocket;
}

void TcpServer::Close(SOCKET clientSocket) {
	auto it = clientConnections.find(clientSocket);
	if (it != clientConnections.end()) {
		int iResult = shutdown(clientSocket, SD_SEND);
		if (iResult == SOCKET_ERROR) {
			closesocket(clientSocket);
			cerr << "shutdown failed";
		}
		else {
			closesocket(clientSocket);
			clientConnections.erase(it);
		}
	}
}

void TcpServer::Stop() {
	for (auto& connection : clientConnections) {
		Close(connection.first);
	}
	if (_listenSocket != INVALID_SOCKET) {
		closesocket(_listenSocket);
		_listenSocket = INVALID_SOCKET;
	}
	clientConnections.clear();

	WSACleanup();
}

