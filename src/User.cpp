#include "User.h"

using namespace std;

User::User(string username, string password, string baseDirectoryPath) {
	_username = username;
	_password = password;
	_baseDirectoryPath = baseDirectoryPath;
}

string User::GetUsername() {
	return _username;
}

string User::GetPassword() {
	return _password;
}

string User::GetBaseDirectoryPath() {
	return _baseDirectoryPath;
}