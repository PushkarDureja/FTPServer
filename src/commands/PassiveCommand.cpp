#include "commands/PassiveCommand.h"

void PassiveCommand::Handle(std::shared_ptr<Session> session, const string& args) {
	session->OpenDataConnection(args, 1234, Session::DATA_CONNECTION_MODE::PASSIVE);
}
