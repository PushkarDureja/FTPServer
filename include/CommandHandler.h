#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include "Session.h"
#include <string>

class Session;

class CommandHandler
{
public:

	virtual ~CommandHandler() {}
	virtual void Handle(Session& session, const std::string& args) = 0;
};

#endif