#ifndef SESSION_H
#define SESSION_H

#include <WinSock2.h>
#include <NetworkStream.h>
#include <unordered_map>
#include <commands/CommandHandler.h>
#include <FTPServer.h>
#include <memory>
#include <string>
#include <TcpClient.h>

class CommandHandler;
class FTPServer;
class User;

class Session :public std::enable_shared_from_this<Session>
{

public:
	enum DATA_CONNECTION_MODE {
		ACTIVE = 1,
		PASSIVE = 2
	};

private:
	std::shared_ptr<NetworkStream> _stream;
	std::shared_ptr<FTPServer> _server;
	unordered_map<std::string, unique_ptr<CommandHandler>> _commandHandlers;
	std::shared_ptr<User> _user;
	bool _isAuthenticated = false;

	std::shared_ptr<TcpServer> _passiveDataServer;
	std::shared_ptr<TcpClient> _activeDataClient;
	SOCKET _dataConnectionSock = 0;
	DATA_CONNECTION_MODE _dataConnectionType;

	void AcceptDataServerClient();


public:

	Session(std::shared_ptr<NetworkStream>  stream, std::shared_ptr<FTPServer> server);
	void StartReadingAsync();
	void SendResponse(std::string responseString);
	string ReadLine();
	void OpenDataConnection(string host, int port, DATA_CONNECTION_MODE connectionMode);
	void CloseDataConnection();
	std::pair<std::string, int> parsePortCommand(const std::string& portCommandArgs);

	//getters
	std::shared_ptr<User> GetUser();
	std::shared_ptr<FTPServer> GetServer();
	bool GetAuthState();
	SOCKET GetDataSocket();

	//setter
	void SetUser(std::shared_ptr<User> user);
	void SetAuthState(bool state);
};

#endif

