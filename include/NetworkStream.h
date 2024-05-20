#ifndef NETWORK_STREAM_H
#define NETWORK_STREAM_H

#include "Stream.h"
#include <WinSock2.h>

class NetworkStream : public Stream {

private:
	SOCKET _socket;

public:
	NetworkStream(SOCKET socket);
	~NetworkStream();

	int Read(vector<char>& buffer, int offset, int count);
	int Write(vector<char>& buffer, int offset, int count);
	int Close();
};

#endif