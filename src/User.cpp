#include "User.h"

using namespace std;

User::User(string username, string password) {
	_username = username;
	_password = password;
}

string User::GetUsername() {
	return _username;
}

string User::GetPassword() {
	return _password;
}
