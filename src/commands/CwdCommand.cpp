#include "commands\CwdCommand.h"
#include <FileSystem.h>

void CwdCommand::Handle(std::shared_ptr<Session> session, const string& args) {

	if (!isAuthenticated(session)) {
		session->SendResponse("530 Not logged in.");
		return;
	}

	string resolvedPath = FileSystem::GetCombinedPath(session->GetWorkingDirectory(), args);
	resolvedPath = FileSystem::SanitizePath(resolvedPath);

	string sessionBaseDirectory = session->GetUser()->GetBaseDirectoryPath();

 	if (!FileSystem::IsPathWithinAllowed(sessionBaseDirectory, resolvedPath)) {
		resolvedPath = sessionBaseDirectory;
	}

	if (!FileSystem::CheckExists(resolvedPath)) {
		session->SendResponse("550 Could not open directory");
		return;
	}

	//TODO check permissions here

	session->SetWorkingDirectory(resolvedPath);

	session->SendResponse("200 Command Successfull");
}
