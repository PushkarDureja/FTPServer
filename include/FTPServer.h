#ifndef FTP_SERVER_H
#define FTP_SERVER_H

#include "TcpServer.h"
#include "Session.h"
#include <thread>
class FTPServer
{
private:
	int _port;
	TcpServer _tcpServer;
	std::vector<std::shared_ptr<Session>> sessions;

	std::thread acceptClientThread;
	void AcceptClientAsync();

public:
	FTPServer(int port = 21);
	~FTPServer();

	void Start();
	void Stop();
};

#endif
