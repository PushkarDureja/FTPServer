#include "BinaryReader.h"

BinaryReader::BinaryReader(Stream& stream) : _stream(stream) {};

int8_t BinaryReader::ReadInt8() {
	int8_t* value;
	vector<char> outputBuff(sizeof(int8_t));

	int bytesRead = _stream.Read(outputBuff, 0, sizeof(int8_t));
	if (bytesRead < 1)
		return 0;

	value = reinterpret_cast<int8_t*>(outputBuff.data());
	return *value;
}

int16_t BinaryReader::ReadInt16() {
	int16_t* value;
	vector<char> outputBuff(sizeof(int16_t));

	int bytesRead = _stream.Read(outputBuff, 0, sizeof(int16_t));
	if (bytesRead < 1)
		return 0;

	value = reinterpret_cast<int16_t*>(outputBuff.data());
	return *value;
}

int32_t BinaryReader::ReadInt32() {
	int32_t* value;
	vector<char> outputBuff(sizeof(int32_t));

	int bytesRead = _stream.Read(outputBuff, 0, sizeof(int32_t));
	if (bytesRead < 1)
		return 0;

	value = reinterpret_cast<int32_t*>(outputBuff.data());
	return *value;
}