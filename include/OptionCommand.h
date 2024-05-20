#ifndef OPTION_COMMAND_H
#define OPTION_COMMAND_H
#include "CommandHandler.h"

using namespace std;

class OptionCommand : public CommandHandler {
public:
    void Handle(Session& session, const std::string& args);
};

#endif