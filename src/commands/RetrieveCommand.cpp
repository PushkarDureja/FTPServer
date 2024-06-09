#include "commands\RetrieveCommand.h"
#include <FileSystem.h>
#include <fstream> 
#include <BinaryWriter.h>

void RetreiveCommand::Handle(std::shared_ptr<Session> session, const string& filePath) {

	if (!isAuthenticated(session)) {
		session->SendResponse("530 Not logged in.");
		return;
	}

	string resolvedPath = FileSystem::GetCombinedPath(session->GetWorkingDirectory(), filePath);
	resolvedPath = FileSystem::SanitizePath(resolvedPath);

	if (!FileSystem::CheckExists(resolvedPath)) {
		session->SendResponse("550 Could not open file");
		return;
	}

	string sessionBaseDirectory = session->GetUser()->GetBaseDirectoryPath();
	if (!FileSystem::IsPathWithinAllowed(sessionBaseDirectory, resolvedPath)) {
		session->SendResponse("550 Permission Denied");
	}

	std::ifstream file(resolvedPath, std::ios::binary);
	if (!file.is_open()) {
		session->SendResponse("550 Could not open file");
		return;
	}

	session->SendResponse("150 Starting data transfer.");
	SOCKET dataSocket = session->GetDataSocket();

	if (!dataSocket)
		session->SendResponse("425 Can't open data connection");

	session->SendResponse("150 Starting data transfer.");
	std::shared_ptr<NetworkStream> stream = std::make_shared<NetworkStream>(dataSocket);
	std::shared_ptr<BinaryWriter> writer = std::make_shared<BinaryWriter>(stream);

	const int BUFFER_SIZE = 4096;
	std::vector<char> buffer(BUFFER_SIZE);
	while (!file.eof()) {
		file.read(buffer.data(), BUFFER_SIZE);
		std::streamsize bytesRead = file.gcount();
		writer->Write(buffer, 0, bytesRead);
	}

	session->SendResponse("226 Operation successful");
	session->CloseDataConnection();
}
