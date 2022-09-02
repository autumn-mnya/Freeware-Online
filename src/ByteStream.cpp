#include "ByteStream.h"

#include <cstring>

ByteStream::ByteStream(uint8_t* stream, size_t size) : Stream(stream), End(stream + size)
{
}

void ByteStream::WriteLE32(uint32_t i)
{
	if (sizeof(uint32_t) <= End - Stream)
	{
		*((uint32_t*)Stream) = i;
		//memcpy(Stream, &i, sizeof(uint32_t));
		Stream += sizeof(uint32_t);
	}
}

uint32_t ByteStream::ReadLE32()
{
	uint32_t val = -1;
	if (sizeof(uint32_t) <= End - Stream)
	{
		val = *((uint32_t*)Stream);
		Stream += sizeof(uint32_t);
	}
	return val;
}

void ByteStream::Write(const void* data, size_t size, size_t num)
{
	size_t s = size * num;
	if (s > End - Stream)
		s = End - Stream;
	if (0 < s && s <= End - Stream)
	{
		memcpy(Stream, data, s);
		Stream += s;
	}
}
void ByteStream::Read(void* ptr, size_t size, size_t maxnum)
{
	size_t s = size * maxnum;
	if (s > End - Stream)
		s = End - Stream;
	if (0 < s && s <= End - Stream)
	{
		memcpy(ptr, Stream, s);
		Stream += s;
	}
}