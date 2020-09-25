#include "InputStreams.h"
#include "catch2/catch.hpp"

std::vector<uint8_t> EMPTY_STREAM = {};
std::vector<uint8_t> INPUT_STREAM = { 'A', '\n', '2', 'b' };

TEST_CASE("Reading a byte returns the byte that have been read from input memory stream")
{
	CMemoryInputStream stream(INPUT_STREAM);

	CHECK(stream.ReadByte() == 'A');
	CHECK(stream.ReadByte() == '\n');
	CHECK(stream.ReadByte() == '2');
	CHECK(stream.ReadByte() == 'b');
	CHECK_THROWS_AS(stream.ReadByte(), std::ios_base::failure);

	SECTION("When reading a byte from an empty stream, exception must be thrown")
	{
		CMemoryInputStream empty(EMPTY_STREAM);
		CHECK_THROWS_AS(empty.ReadByte(), std::ios_base::failure);
	}
}

TEST_CASE("Reading a block returns the number of characters that have been read from input memory stream")
{
	CMemoryInputStream stream(INPUT_STREAM);
	char buffer[2];

	CHECK(stream.ReadBlock(buffer, 2) == 2);
	CHECK(buffer[0] == 'A');
	CHECK(buffer[1] == '\n');

	CHECK(stream.ReadBlock(buffer, 1) == 1);
	CHECK(buffer[0] == '2');

	SECTION("When reading a block from an empty memory stream, zero characters must be read")
	{
		CMemoryInputStream empty(EMPTY_STREAM);
		char buffer[1];
		CHECK(empty.ReadBlock(buffer, 1) == 0);
	}
}

TEST_CASE("IsEOF returns true if the next read operation from input memory stream will be fail")
{
	CMemoryInputStream stream(INPUT_STREAM);
	char buffer[3];
	stream.ReadBlock(buffer, 3);

	CHECK_FALSE(stream.IsEOF());
	CHECK_NOTHROW(stream.ReadByte());
	CHECK(stream.IsEOF());
	CHECK_THROWS_AS(stream.ReadByte(), std::ios_base::failure);
}