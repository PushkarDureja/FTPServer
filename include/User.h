#ifndef USER_H
#define USER_H

#include <string>

class User
{
public:
	User(std::string username, std::string password, std::string baseDirectoryPath);

	//getters
	std::string GetUsername();
	std::string GetPassword();
	std::string GetBaseDirectoryPath();

private:
	std::string _username;
	std::string _password;
	std::string _baseDirectoryPath;
};

#endif

