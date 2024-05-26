#ifndef PASSIVE_COMMAND_H
#define PASSIVE_COMMAND_H

#include "commands/CommandHandler.h"
class PassiveCommand :
	public CommandHandler
{
public:
	void Handle(std::shared_ptr<Session> session, const std::string& args) override;
};

#endif
