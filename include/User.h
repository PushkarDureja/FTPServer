#ifndef USER_H
#define USER_H

#include <string>

class User
{
public:
	User(std::string username, std::string password);

	//getters
	std::string GetUsername();
	std::string GetPassword();

private:
	std::string _username;
	std::string _password;
};

#endif

