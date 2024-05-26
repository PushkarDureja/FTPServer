#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <string>
#include <stdexcept>
#include <iostream>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

class TcpClient {
public:
    TcpClient(const std::string& server_address, int server_port);
    ~TcpClient();

    SOCKET connectToServer();

private:
    std::string server_address_;
    int server_port_;
    SOCKET socket_fd_;
    sockaddr_in server_addr_;
};

#endif // TCPCLIENT_H