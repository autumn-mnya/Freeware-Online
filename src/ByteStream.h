#pragma once
#include <cstdint>
class ByteStream
{
	uint8_t* Stream;
	uint8_t* End;

public:
	ByteStream(uint8_t* stream, size_t size);

	void WriteLE32(uint32_t value);
	uint32_t ReadLE32();

	void Write(const void* data, size_t size, size_t num);
	void Read(void* ptr, size_t size, size_t maxnum);
};