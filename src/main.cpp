#include <iostream>
#include "FTPServer.h"
#include "NetworkStream.h"
using namespace std;

int main() {
	std::shared_ptr<FTPServer> server = std::make_shared<FTPServer>();
	server->AddUser("user", "zxcv", "C:\\Users\\PUSHKAR\\Documents");
	server->Start();

	int x;
	cin >> x;
}