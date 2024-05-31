#ifndef CWD_COMMAND_H
#define CWD_COMMAND_H

#include "commands\CommandHandler.h"

class CwdCommand :
	public CommandHandler
{
public:
	void Handle(std::shared_ptr<Session> session, const std::string& args) override;
};

#endif;
