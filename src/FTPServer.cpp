#include "FTPServer.h"
#include <NetworkStream.h>
#include <Session.h>

FTPServer::FTPServer(int port) : _port(port), _tcpServer("127.0.0.1", _port) {}

FTPServer::~FTPServer() {
	Stop();
	if (acceptClientThread.joinable())
		acceptClientThread.join();
}

void FTPServer::Start() {
	_tcpServer.Start();
	acceptClientThread = thread(&FTPServer::AcceptClientAsync, this);
	acceptClientThread.detach();
}

void FTPServer::Stop() {
	_tcpServer.Stop();
}

void FTPServer::AcceptClientAsync() {
	while (true) {
		SOCKET client = _tcpServer.Accept();
		auto networkStream = std::make_shared<NetworkStream>(client);
		auto session = std::make_shared<Session>(*networkStream);
		sessions.push_back(session);
		thread(&Session::StartReadingAsync, session).detach();
	}
}