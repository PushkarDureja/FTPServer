#include "BinaryWriter.h"
using namespace std;

BinaryWriter::BinaryWriter(std::shared_ptr<Stream> stream) : _stream(stream) {};

int BinaryWriter::WriteInt8(int8_t val) {
	vector<char> inputBuff(sizeof(uint8_t));
	pushToByteVector(val, inputBuff);

	return _stream->Write(inputBuff, 0, sizeof(int8_t));
}

int BinaryWriter::WriteInt16(int16_t val) {
	vector<char> inputBuff(sizeof(int16_t));
	pushToByteVector(val, inputBuff);

	return _stream->Write(inputBuff, 0, sizeof(int16_t));
}

int BinaryWriter::WriteInt32(int32_t val) {
	vector<char> inputBuff(sizeof(int32_t));
	pushToByteVector(val, inputBuff);

	return _stream->Write(inputBuff, 0, sizeof(int32_t));
}

int BinaryWriter::WriteString(string val) {
	vector<char> inputBuff(val.begin(), val.end());

	return _stream->Write(inputBuff, 0, val.length());
}

template<typename T>
void BinaryWriter::pushToByteVector(T value, std::vector<char>& byteVector) {
	static_assert(std::is_integral<T>::value, "Only integral types are supported");
	uint8_t* bytePtr = reinterpret_cast<uint8_t*>(&value);
	for (size_t i = 0; i < sizeof(T); ++i) {
		byteVector[i] = (bytePtr[i]);
	}
}