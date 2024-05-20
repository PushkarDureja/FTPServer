#ifndef SESSION_H
#define SESSION_H

#include <WinSock2.h>
#include <NetworkStream.h>
#include <unordered_map>
#include <CommandHandler.h>
#include <memory>
#include <string>

class CommandHandler;

class Session
{
private:
	NetworkStream _stream;
	unordered_map<std::string, unique_ptr<CommandHandler>> _commandHandlers;

public:
	Session(NetworkStream& stream);
	void StartReadingAsync();
	void SendResponse(std::string responseString);
	string ReadLine();

};

#endif

