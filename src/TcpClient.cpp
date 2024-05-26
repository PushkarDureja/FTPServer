#include "TcpClient.h"

TcpClient::TcpClient(const std::string& server_address, int server_port)
    : server_address_(server_address), server_port_(server_port), socket_fd_(INVALID_SOCKET) {
    WSADATA wsData;
    WORD ver = MAKEWORD(2, 2);
    int wsOK = WSAStartup(ver, &wsData);
    if (wsOK != 0) {
        throw std::runtime_error("Can't initialize Winsock!");
    }

    socket_fd_ = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd_ == INVALID_SOCKET) {
        WSACleanup();
        throw std::runtime_error("Can't create socket!");
    }

    server_addr_.sin_family = AF_INET;
    server_addr_.sin_port = htons(server_port_);
    inet_pton(AF_INET, server_address_.c_str(), &server_addr_.sin_addr);
}

TcpClient::~TcpClient() {
    if (socket_fd_ != INVALID_SOCKET) {
        closesocket(socket_fd_);
    }
    WSACleanup();
}

SOCKET TcpClient::connectToServer() {
    int connResult = connect(socket_fd_, (sockaddr*)&server_addr_, sizeof(server_addr_));
    if (connResult == SOCKET_ERROR) {
        closesocket(socket_fd_);
        WSACleanup();
        throw std::runtime_error("Can't connect to server!");
    }
    return socket_fd_;
}
