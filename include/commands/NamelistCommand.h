#ifndef NLST_COMMAND_H
#define NLST_COMMAND_H

#include "CommandHandler.h"

class NamelistCommand : public CommandHandler {
public:
    void Handle(std::shared_ptr<Session> session, const std::string& args) override;
};

#endif