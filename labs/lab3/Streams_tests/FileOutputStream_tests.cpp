#include "GetDataFromFile.h"
#include "OutputStreams.h"
#include "catch2/catch.hpp"

std::string IMPOSSIBLE_FILE_NAME = "J:\\fail.txt";
std::string OUTPUT_FILE_NAME = "output.txt";

TEST_CASE("If constructor accepted a file that cannot be created or opened, exception must be thrown")
{
	CHECK_THROWS_AS(CFileOutputStream(IMPOSSIBLE_FILE_NAME), std::ios_base::failure);
}

TEST_CASE("WriteByte() writes byte to output file stream")
{
	CFileOutputStream file(OUTPUT_FILE_NAME);

	CHECK_NOTHROW(file.WriteByte('A'));
	CHECK(GetDataFromFile(OUTPUT_FILE_NAME) == "A");

	CHECK_NOTHROW(file.WriteByte('\n'));
	CHECK_NOTHROW(file.WriteByte('2'));
	CHECK(GetDataFromFile(OUTPUT_FILE_NAME) == "A\n2");
}

TEST_CASE("WriteBlock() writes block of bytes to output file stream")
{
	CFileOutputStream file(OUTPUT_FILE_NAME);
	char srcData[] = { 'A', '2', '\n', 'b' };

	CHECK_NOTHROW(file.WriteBlock(srcData, 3));
	CHECK(GetDataFromFile(OUTPUT_FILE_NAME) == "A2\n");

	CHECK_NOTHROW(file.WriteBlock(srcData, 1));
	CHECK(GetDataFromFile(OUTPUT_FILE_NAME) == "A2\nA");
}
