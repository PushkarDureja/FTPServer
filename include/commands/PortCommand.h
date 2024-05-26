#ifndef PORT_COMMAND_H
#define PORT_COMMAND_H

#include "commands/CommandHandler.h"
class PortCommand :
	public CommandHandler
{
public:
	void Handle(std::shared_ptr<Session> session, const std::string& args) override;
};

#endif
