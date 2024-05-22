#include "commands/CommandHandler.h"

using namespace std;

bool CommandHandler::isAuthenticated(shared_ptr<Session> session) {
	return session->GetUser() != NULL && session->GetAuthState();
}
