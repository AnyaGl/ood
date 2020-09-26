#include "AddDecorators.h"
#include "InputStreamDecorators.h"
#include "OutputStreamDecorators.h"
#include "catch2/catch.hpp"


TEST_CASE("After compression and decompression memory stream, the data must be the same")
{
	SECTION("writing and reading one byte at a time")
	{
		std::vector<uint8_t> memory{};
		{
			auto encryptedStream = make_unique<CMemoryOutputStream>(memory)
				<< AddFunctionality<CCompressedOutputStream>();

			encryptedStream->WriteByte('A');
			encryptedStream->WriteByte('\n');
			encryptedStream->WriteByte('2');
		}

		auto decryptedStream = make_unique<CMemoryInputStream>(memory)
			<< AddFunctionality<CDecompressedInputStream>();

		CHECK(decryptedStream->ReadByte() == 'A');
		CHECK(decryptedStream->ReadByte() == '\n');
		CHECK(decryptedStream->ReadByte() == '2');
	}

	SECTION("writing and reading block of bytes")
	{
		std::vector<uint8_t> memory{};
		char srcData[] = { 'A', '\n', '2' };
		{
			auto encryptedStream = make_unique<CMemoryOutputStream>(memory)
				<< AddFunctionality<CCompressedOutputStream>();

			encryptedStream->WriteBlock(srcData, 2);
		}

		auto decryptedStream = make_unique<CMemoryInputStream>(memory)
			<< AddFunctionality<CDecompressedInputStream>();

		char dstData[2];
		CHECK(decryptedStream->ReadBlock(dstData, 2) == 2);
		CHECK(dstData[0] == srcData[0]);
		CHECK(dstData[1] == srcData[1]);
	}
}

const std::string FILE_NAME = "data.txt";

TEST_CASE("After compression and decompression file stream, the data must be the same")
{
	SECTION("writing and reading one byte at a time")
	{
		{
			auto encryptedStream = make_unique<CFileOutputStream>(FILE_NAME)
				<< AddFunctionality<CCompressedOutputStream>();

			encryptedStream->WriteByte('A');
			encryptedStream->WriteByte('\n');
			encryptedStream->WriteByte('2');
		}
		{
			auto decryptedStream = make_unique<CFileInputStream>(FILE_NAME)
				<< AddFunctionality<CDecompressedInputStream>();

			CHECK(decryptedStream->ReadByte() == 'A');
			CHECK(decryptedStream->ReadByte() == '\n');
			CHECK(decryptedStream->ReadByte() == '2');
		}
	}

	SECTION("writing and reading block of bytes")
	{
		char srcData[] = { 'A', '\n', '2' };
		{
			auto encryptedStream = make_unique<CFileOutputStream>(FILE_NAME)
				<< AddFunctionality<CCompressedOutputStream>();

			encryptedStream->WriteBlock(srcData, 2);
		}
		{
			auto decryptedStream = make_unique<CFileInputStream>(FILE_NAME)
				<< AddFunctionality<CDecompressedInputStream>();

			char dstData[2];
			CHECK(decryptedStream->ReadBlock(dstData, 2) == 2);
			CHECK(dstData[0] == srcData[0]);
			CHECK(dstData[1] == srcData[1]);
		}
	}
}
