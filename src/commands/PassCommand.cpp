#include "commands/PassCommand.h"

void PassCommand::Handle(std::shared_ptr<Session> session, const string& args) {
	shared_ptr<User> user = session->GetUser();
	if (user == nullptr) {
		session->SendResponse("530 Not logged in.");
		return;
	}

	bool isPassMatch = strcmp(user->GetPassword().c_str(), args.c_str());
	if (isPassMatch != 0) {
		session->SendResponse("530 Not logged in.");
		return;
	}

	session->SetAuthState(true);
	session->SendResponse("230 User logged in, proceed.");
}
