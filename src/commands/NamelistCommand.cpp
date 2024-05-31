#include "commands/NamelistCommand.h"
#include <memory>
#include <BinaryWriter.h>
#include <FileSystem.h>

void NamelistCommand::Handle(std::shared_ptr<Session> session, const string& args) {
	if (!isAuthenticated(session)) {
		session->SendResponse("530 Not logged in.");
		return;
	}

	SOCKET dataSocket = session->GetDataSocket();

	// since this command is dependent on the data connection, client is responsible to initiate appropriate command to open data connection
	if (!dataSocket)
		session->SendResponse("425 Can't open data connection");

	session->SendResponse("150 Starting data transfer.");
	std::shared_ptr<NetworkStream> stream = std::make_shared<NetworkStream>(dataSocket);
	std::shared_ptr<BinaryWriter> writer = std::make_shared<BinaryWriter>(stream);

	vector<string> listing = FileSystem::GetDirectoryListing(args.length() < 1 ? session->GetWorkingDirectory() : args);
	for (string listingName : listing)
	{
		writer->WriteString(listingName + "\r\n");
	}

	session->SendResponse("226 Operation successful");
	session->CloseDataConnection();
}
