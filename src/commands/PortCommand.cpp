#include "commands/PortCommand.h"

void PortCommand::Handle(std::shared_ptr<Session> session, const string& args) {

	if (!isAuthenticated(session)) {
		session->SendResponse("530 Not logged in.");
		return;
	}

	int port;
	std::string ipAddress;

	try {
		auto result = session->parsePortCommand(args);
		ipAddress = result.first;
		port = result.second;
		printf("port %d\n", port);

		std::cout << "IP Address: " << ipAddress << std::endl;
		std::cout << "Port: " << port << std::endl;
	}
	catch (const std::runtime_error& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	session->OpenDataConnection(ipAddress, port, Session::DATA_CONNECTION_MODE::ACTIVE);
	session->SendResponse("200 Command Successfull");
}


