#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include "Session.h"
#include <string>
#include <memory>

class Session;

class CommandHandler
{
public:

	virtual ~CommandHandler() {}
	virtual void Handle(std::shared_ptr<Session>, const std::string& args) = 0;
};

#endif