#ifndef BINARY_READER_H
#define BINARY_READER_H

#include "Stream.h"

class BinaryReader {
public:
	explicit BinaryReader(Stream& stream);

	int8_t ReadInt8();
	int16_t ReadInt16();
	int32_t ReadInt32();
	
private:
	Stream& _stream;
};

#endif

