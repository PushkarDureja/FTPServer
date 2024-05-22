#ifndef USER_COMMAND_H
#define USER_COMMAND_H

#include "CommandHandler.h"

using namespace std;

class UserCommand : public CommandHandler{
public:
    void Handle(std::shared_ptr<Session> session, const std::string& args) override;
};

#endif