#ifndef STREAM_H
#define STREAM_H
#include <vector>

using namespace std;
class Stream {
public:
	virtual ~Stream() {}

	virtual int Read(vector<char>& buffer, int offset, int count) = 0;
	virtual int Write(vector<char>& buffer, int offset, int count) = 0;
};

#endif

