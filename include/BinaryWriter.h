#ifndef BINARY_WRITER_H
#define BINARY_WRITER_H

#include "Stream.h"
#include <type_traits>

class BinaryWriter {
public:
	explicit BinaryWriter(Stream& stream);

	int WriteInt8(int8_t val);
	int WriteInt16(int16_t val);
	int WriteInt32(int32_t val);

private:
	Stream& _stream;

	template<typename T>
	void pushToByteVector(T value, vector<char>& byteVector);
};

#endif

