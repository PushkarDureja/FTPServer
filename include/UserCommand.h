#ifndef USER_COMMAND_H
#define USER_COMMAND_H
#include "CommandHandler.h"

using namespace std;

class UserCommand : public CommandHandler{
public:
    void Handle(Session& session, const std::string& args);
};

#endif