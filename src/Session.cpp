#include "Session.h"
#include <thread>
#include "commands/UserCommand.h"
#include "commands/OptionCommand.h"
#include "commands/PassCommand.h"
#include "FTPServer.h"
#include <iostream>

#define BUFFER_SIZE 1024

Session::Session(std::shared_ptr<NetworkStream> stream, std::shared_ptr<FTPServer> server) : _stream(stream), _server(server) {
	_commandHandlers.insert({ "OPTS",std::make_unique<OptionCommand>() });
	_commandHandlers.insert({ "USER",std::make_unique<UserCommand>() });
	_commandHandlers.insert({ "PASS",std::make_unique<PassCommand>() });

};

void Session::StartReadingAsync() {

	//send ok to start reading commands from client
	SendResponse("220 Service Ready for new user");

	while (true) {
		string command = ReadLine();

		if (command.length() < 1) {
			_stream->Close();
			return;
		}

		//find and execute command handler
		auto spacePos = command.find(' ');
		std::string cmdName = (spacePos == std::string::npos) ? command : command.substr(0, spacePos);
		std::string args = (spacePos == std::string::npos) ? "" : command.substr(spacePos + 1);

		auto endLinePos = args.find("\r\n");
		string sanitizedArgs = (endLinePos == string::npos) ? args : args.substr(0, endLinePos);

		auto handler = _commandHandlers.find(cmdName);
		if (handler != _commandHandlers.end()) {
			handler->second->Handle(shared_from_this(), sanitizedArgs);
		}
		else {
			SendResponse("502 Command not implemented");
		}
	}
}

string Session::ReadLine() {

	string command = "";
	string endline = "\r\n";

	while (true) {
		vector<char> commandBuffer(BUFFER_SIZE);
		int bytesRead = _stream->Read(commandBuffer, 0, BUFFER_SIZE);
		if (bytesRead < 1)
			return "";

		string commandBufferString(commandBuffer.begin(), commandBuffer.end());
		command = command + commandBufferString;

		if (command.find(endline) != std::string::npos) {
			return command;
		}
	}

	return "";
}

void Session::SendResponse(string responseString) {
	responseString = responseString + "\r\n";
	vector<char> buff(responseString.begin(), responseString.end());
	_stream->Write(buff, 0, (int)buff.size());
}

shared_ptr<User> Session::GetUser() {
	return  _user;
}

shared_ptr<FTPServer> Session::GetServer() {
	return  _server;
}

bool Session::GetAuthState() {
	return  _isAuthenticated;
}

void Session::SetUser(shared_ptr<User> user) {
	_user = move(user);
}

void Session::SetAuthState(bool state) {
	_isAuthenticated = state;
}
