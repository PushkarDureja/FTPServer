#ifndef PASS_COMMAND_H
#define PASS_COMMAND_H

#include "commands/CommandHandler.h"

class PassCommand :
	public CommandHandler
{
public:
	void Handle(std::shared_ptr<Session> session, const std::string& args) override;
};

#endif

