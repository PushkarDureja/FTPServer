#include "NetworkStream.h"

NetworkStream::NetworkStream(SOCKET clientSocket) : _socket(clientSocket) {};

NetworkStream::~NetworkStream() {

}

int NetworkStream::Read(vector<char>& buffer, int offset, int count) {
	buffer.resize(offset + count);
	int bytesRead = recv(_socket, buffer.data() + offset, count, 0);
	if (bytesRead == -1) {
		return 0;	
	}
	return bytesRead;
}

int NetworkStream::Write(vector<char>& buffer, int offset, int count) {
	return send(_socket, buffer.data() + offset, count, 0);
}

int NetworkStream::Close() {
	return closesocket(_socket);
}