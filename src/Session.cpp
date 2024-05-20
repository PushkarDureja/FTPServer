#include "Session.h"
#include <thread>
#include "UserCommand.h"
#include "OptionCommand.h"
#include <iostream>

#define BUFFER_SIZE 1024

Session::Session(NetworkStream& stream) : _stream(stream) {

	_commandHandlers.insert({ "USER",std::make_unique<UserCommand>() });
	_commandHandlers.insert({ "OPTS",std::make_unique<OptionCommand>() });
};

void Session::StartReadingAsync() {

	SendResponse("220 Service Ready for new user.\r\n");

	while (true) {
		string command = ReadLine();

		if (command.length() < 1) {
			_stream.Close();
			return;
		}

		//find and execute command handler
		auto spacePos = command.find(' ');
		std::string cmdName = (spacePos == std::string::npos) ? command : command.substr(0, spacePos);
		std::string args = (spacePos == std::string::npos) ? "" : command.substr(spacePos + 1);

		auto handler = _commandHandlers.find(cmdName);
		if (handler != _commandHandlers.end()) {
			handler->second->Handle(*this, args);
		}
		else {
			SendResponse("502 Command not implemented.\r\n");
		}
	}
}

string Session::ReadLine() {

	string command = "";
	string endline = "\r\n";

	while (true) {
		vector<char> commandBuffer(BUFFER_SIZE);
		int bytesRead = _stream.Read(commandBuffer, 0, BUFFER_SIZE);
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
	vector<char> buff(responseString.begin(), responseString.end());
	_stream.Write(buff, 0, (int)buff.size());
}
