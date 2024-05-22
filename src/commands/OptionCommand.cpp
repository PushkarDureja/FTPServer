#include "OptionCommand.h"

void OptionCommand::Handle(std::shared_ptr<Session> session, const string& args) {
	session->SendResponse("200 Command okay");
}
