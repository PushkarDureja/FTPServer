#include "UserCommand.h"

void UserCommand::Handle(Session &session, const string& args) {
	session.SendResponse("200 Command okay\r\n");
}
