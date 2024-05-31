#include "Session.h"
#include <thread>
#include "commands/UserCommand.h"
#include "commands/OptionCommand.h"
#include "commands/PassCommand.h"
#include "commands/PassiveCommand.h"
#include "commands/PortCommand.h"
#include "commands/NamelistCommand.h"
#include "commands/CwdCommand.h"
#include "FTPServer.h"
#include <iostream>
#include <sstream>
using namespace std;

#define BUFFER_SIZE 1024

Session::Session(std::shared_ptr<NetworkStream> stream, std::shared_ptr<FTPServer> server) : _stream(stream), _server(server) {
	_commandHandlers.insert({ "OPTS",std::make_unique<OptionCommand>() });
	_commandHandlers.insert({ "USER",std::make_unique<UserCommand>() });
	_commandHandlers.insert({ "PASS",std::make_unique<PassCommand>() });
	_commandHandlers.insert({ "PASV",std::make_unique<PassiveCommand>() });
	_commandHandlers.insert({ "PORT",std::make_unique<PortCommand>() });
	_commandHandlers.insert({ "NLST",std::make_unique<NamelistCommand>() });
	_commandHandlers.insert({ "CWD",std::make_unique<CwdCommand>() });
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
		size_t endLinePos = command.find("\r\n");
		string sanitizedCommand = (endLinePos == string::npos) ? command : command.substr(0, endLinePos);

		size_t spacePos = sanitizedCommand.find(' ');
		std::string cmdName = (spacePos == std::string::npos) ? sanitizedCommand : sanitizedCommand.substr(0, spacePos);
		std::string args = (spacePos == std::string::npos) ? "" : sanitizedCommand.substr(spacePos + 1);

		auto handler = _commandHandlers.find(cmdName);
		if (handler != _commandHandlers.end()) {
			handler->second->Handle(shared_from_this(), args);
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

void Session::OpenDataConnection(string host, int port, DATA_CONNECTION_MODE connectionMode) {
	switch (connectionMode)
	{
	case Session::ACTIVE:
		_dataConnectionType = Session::ACTIVE;
		_activeDataClient = std::make_shared<TcpClient>(host, port);
		_dataConnectionSock = _activeDataClient->connectToServer();
		break;

	case Session::PASSIVE:
		_dataConnectionType = Session::PASSIVE;
		_passiveDataServer = std::make_shared<TcpServer>(host, port);
		_passiveDataServer->Start();
		thread(&Session::AcceptDataServerClient, this).detach();
		break;

	default:
		printf("invalid connection mode...\n");
		break;
	}
}

void Session::CloseDataConnection() {
	switch (_dataConnectionType)
	{
	case Session::ACTIVE:
		closesocket(_dataConnectionSock);
		_activeDataClient = NULL;
		break;

	case Session::PASSIVE:
		_passiveDataServer->Close(_dataConnectionSock);
		_passiveDataServer->Stop();
		_passiveDataServer = NULL;
		break;

	default:
		printf("invalid connection mode...\n");
		break;
	}
}

void Session::AcceptDataServerClient() {
	while (_passiveDataServer != nullptr) {
		SOCKET clientSocket = _passiveDataServer->Accept();
		if (clientSocket == NULL)
			break;

		_dataConnectionSock = clientSocket;
		break;
	}
}

pair<std::string, int> Session::parsePortCommand(const std::string& portCommandArgs) {
	std::vector<int> parts;
	std::stringstream ss(portCommandArgs);
	std::string item;

	// Split the input string by commas
	while (std::getline(ss, item, ',')) {
		parts.push_back(std::stoi(item));
	}

	// Ensure we have exactly 6 parts
	if (parts.size() != 6) {
		throw std::runtime_error("Invalid PORT command arguments.");
	}

	// Reconstruct the IP address
	std::string ipAddress = std::to_string(parts[0]) + "." +
		std::to_string(parts[1]) + "." +
		std::to_string(parts[2]) + "." +
		std::to_string(parts[3]);

	// Reconstruct the port number
	int port = (parts[4] << 8) + parts[5];

	return { ipAddress, port };
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

SOCKET Session::GetDataSocket() {
	return  _dataConnectionSock;
}

string Session::GetWorkingDirectory() {
	return _workingDirectory;
}

void Session::SetUser(shared_ptr<User> user) {
	_user = move(user);
}

void Session::SetAuthState(bool state) {
	_isAuthenticated = state;
}

void Session::SetWorkingDirectory(string workingDirectory) {
	_workingDirectory = workingDirectory;
}
