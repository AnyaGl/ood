#define CATCH_CONFIG_MAIN
#include "InputStreams.h"
#include "catch2/catch.hpp"

std::string NON_EXISTENT_FILE_NAME = "not-existent.txt";
std::string EMPTY_FILE_NAME = "empty.txt";
std::string INPUT_FILE_NAME = "input.txt";

TEST_CASE("if constructor accepted non-existent file, exception must be thrown")
{
	CHECK_THROWS_AS(CFileInputStream(NON_EXISTENT_FILE_NAME), std::ios_base::failure);
}

TEST_CASE("Reading a byte returns the byte that have been read")
{
	CFileInputStream file(INPUT_FILE_NAME);

	CHECK(file.ReadByte() == 'A');
	CHECK(file.ReadByte() == '\r');
	CHECK(file.ReadByte() == '\n');
	CHECK(file.ReadByte() == '2');
	CHECK(file.ReadByte() == 'B');
	CHECK_THROWS_AS(file.ReadByte(), std::ios_base::failure);

	SECTION("When reading a byte from an empty file, exception must be thrown")
	{
		CFileInputStream empty(EMPTY_FILE_NAME);
		CHECK_THROWS_AS(empty.ReadByte(), std::ios_base::failure);
	}
}

TEST_CASE("Reading a block returns the number of characters that have been read")
{
	CFileInputStream file(INPUT_FILE_NAME);
	char buffer[2];

	CHECK(file.ReadBlock(buffer, 2) == 2);
	CHECK(buffer[0] == 'A');
	CHECK(buffer[1] == '\r');

	CHECK(file.ReadBlock(buffer, 1) == 1);
	CHECK(buffer[0] == '\n');

	SECTION("When reading a block from an empty file, zero characters must be read")
	{
		CFileInputStream empty(EMPTY_FILE_NAME);
		char buffer[1];
		CHECK(empty.ReadBlock(buffer, 1) == 0);
	}
}

TEST_CASE("IsEOF returns true if the last read operation failed")
{
	CFileInputStream file(INPUT_FILE_NAME);
	char buffer[5];
	file.ReadBlock(buffer, 5);

	CHECK_FALSE(file.IsEOF());
	CHECK_THROWS(file.ReadByte());
	CHECK(file.IsEOF());
}