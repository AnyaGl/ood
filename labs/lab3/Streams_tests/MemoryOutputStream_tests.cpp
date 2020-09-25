#include "OutputStreams.h"
#include "catch2/catch.hpp"

std::vector<uint8_t> OUTPUT_STREAM = { };

TEST_CASE("WriteByte() writes byte to output memory stream")
{
	CMemoryOutputStream file(OUTPUT_STREAM);

	CHECK_NOTHROW(file.WriteByte('A'));
	CHECK(OUTPUT_STREAM[0] == 'A');

	CHECK_NOTHROW(file.WriteByte('\n'));
	CHECK(OUTPUT_STREAM[1] == '\n');
}

TEST_CASE("WriteBlock() writes block of bytes to output memory stream")
{
	OUTPUT_STREAM = { };
	CMemoryOutputStream file(OUTPUT_STREAM);
	char srcData[] = { 'A', '2', '\n', 'b' };

	CHECK_NOTHROW(file.WriteBlock(srcData, 3));
	CHECK(OUTPUT_STREAM[0] == 'A');
	CHECK(OUTPUT_STREAM[1] == '2');
	CHECK(OUTPUT_STREAM[2] == '\n');

	CHECK_NOTHROW(file.WriteBlock(srcData, 1));
	CHECK(OUTPUT_STREAM[3] == 'A');
}
