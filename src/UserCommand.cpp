#include "commands/UserCommand.h"

void UserCommand::Handle(std::shared_ptr<Session> session, const string& args) {
	shared_ptr<User> user = session->GetServer()->GetUser(args);
	if (user == nullptr) {
		session->SendResponse("530 Not logged in.");
		return;
	}
	session->SetUser(user);
	session->SendResponse("331 User name okay, need password");
}
