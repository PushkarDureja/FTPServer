#ifndef OPTION_COMMAND_H
#define OPTION_COMMAND_H

#include "CommandHandler.h"

class OptionCommand : public CommandHandler {
public:
    void Handle(std::shared_ptr<Session> session, const std::string& args) override;
};

#endif