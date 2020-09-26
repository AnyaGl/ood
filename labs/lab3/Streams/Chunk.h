#pragma once
#include <stdint.h>

struct Chunk
{
	uint8_t numberOfBytes = 0;
	uint8_t byte{};

	void Reset()
	{
		numberOfBytes = 0;
	}

	bool IsEmpty()
	{
		return numberOfBytes == 0;
	}
};