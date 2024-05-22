#ifndef SESSION_H
#define SESSION_H

#include <WinSock2.h>
#include <NetworkStream.h>
#include <unordered_map>
#include <commands/CommandHandler.h>
#include <FTPServer.h>
#include <memory>
#include <string>

class CommandHandler;
class FTPServer;
class User;

class Session:public std::enable_shared_from_this<Session>
{
private:
	std::shared_ptr<NetworkStream> _stream;
	std::shared_ptr<FTPServer> _server;
	unordered_map<std::string, unique_ptr<CommandHandler>> _commandHandlers;
	std::shared_ptr<User> _user;
	bool _isAuthenticated = false;

public:
	Session(std::shared_ptr<NetworkStream>  stream, std::shared_ptr<FTPServer> server);
	void StartReadingAsync();
	void SendResponse(std::string responseString);
	string ReadLine();

	//getters
	std::shared_ptr<User> GetUser();
	std::shared_ptr<FTPServer> GetServer();
	bool GetAuthState();

	//setter
	void SetUser(std::shared_ptr<User> user);
	void SetAuthState(bool state);
};

#endif

