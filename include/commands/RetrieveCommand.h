#ifndef RETR_COMMAND_H
#define RETR_COMMAND_H

#include "commands\CommandHandler.h"

class RetreiveCommand :
	public CommandHandler
{
public:
	void Handle(std::shared_ptr<Session> session, const std::string& args) override;
};

#endif;
