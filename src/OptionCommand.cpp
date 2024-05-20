#include "OptionCommand.h"

void OptionCommand::Handle(Session& session, const string& args) {
	session.SendResponse("200 Command okay\r\n");
}
