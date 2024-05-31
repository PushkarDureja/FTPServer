#ifndef FTP_SERVER_H
#define FTP_SERVER_H

#include "TcpServer.h"
#include "Session.h"
#include "User.h"
#include <thread>
#include <unordered_map>

class Session;

class FTPServer:public std::enable_shared_from_this<FTPServer>
{
private:
	int _port;
	TcpServer _tcpServer;
	std::vector<std::shared_ptr<Session>> sessions;
	std::unordered_map<std::string, std::shared_ptr<User>> _users; 

	std::thread acceptClientThread;
	void AcceptClientAsync();

public:
	FTPServer(int port = 21);
	~FTPServer();

	void Start();
	void Stop();
	bool AddUser(std::string username, std::string password, std::string baseDirectoryPath);

	//getters
	unordered_map<string, shared_ptr<User>> GetUsers();
};

#endif
	