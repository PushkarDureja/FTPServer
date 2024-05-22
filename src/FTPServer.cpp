#include "FTPServer.h"
#include <NetworkStream.h>
#include <Session.h>

using namespace std;

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

bool FTPServer::AddUser(string username, string password) {
	auto user = std::make_shared<User>(username, password);
	if (_users.find(username) == _users.end()) {
		_users.insert({ username, user });
		return true;
	}
	return false;
}

unordered_map<string, shared_ptr<User>> FTPServer::GetUsers() {
	return _users;
}

shared_ptr<User> FTPServer::GetUser(string username) {
	return _users[username];
}

void FTPServer::AcceptClientAsync() {
	while (true) {
		SOCKET client = _tcpServer.Accept();
		auto networkStream = std::make_shared<NetworkStream>(client);
		auto session = std::make_shared<Session>(networkStream, shared_from_this());
		sessions.push_back(session);
		thread(&Session::StartReadingAsync, session).detach();
	}
}

