#include "InputStreamDecorators.h"
#include "OutputStreamDecorators.h"
#include "catch2/catch.hpp"

template <typename Functionality, typename... Args>
auto AddFunctionality(const Args&... args)
{
	return [=](auto&& b) {
		return make_unique<Functionality>(forward<decltype(b)>(b), args...);
	};
}

template <typename Component, typename Decorator>
auto operator<<(Component&& component, const Decorator& decorate)
{
	return decorate(forward<Component>(component));
}

TEST_CASE("After encryption and decryption memory stream, the data must be the same")
{
	SECTION("writing and reading one byte at a time")
	{
		std::vector<uint8_t> memory{};

		auto encryptedStream = make_unique<CMemoryOutputStream>(memory)
			<< AddFunctionality<CEncryptedOutputStream>(100500)
			<< AddFunctionality<CEncryptedOutputStream>(3);

		encryptedStream->WriteByte('A');
		encryptedStream->WriteByte('\n');
		encryptedStream->WriteByte('2');

		auto decryptedStream = make_unique<CMemoryInputStream>(memory)
			<< AddFunctionality<CDecryptedInputStream>(100500)
			<< AddFunctionality<CDecryptedInputStream>(3);

		CHECK(decryptedStream->ReadByte() == 'A');
		CHECK(decryptedStream->ReadByte() == '\n');
		CHECK(decryptedStream->ReadByte() == '2');
	}

	SECTION("writing and reading block of bytes")
	{
		std::vector<uint8_t> memory{};

		auto encryptedStream = make_unique<CMemoryOutputStream>(memory)
			<< AddFunctionality<CEncryptedOutputStream>(100500)
			<< AddFunctionality<CEncryptedOutputStream>(3);

		char srcData[] = { 'A', '\n', '2' };
		encryptedStream->WriteBlock(srcData, 2);

		auto decryptedStream = make_unique<CMemoryInputStream>(memory)
			<< AddFunctionality<CDecryptedInputStream>(100500)
			<< AddFunctionality<CDecryptedInputStream>(3);

		char dstData[2];
		CHECK(decryptedStream->ReadBlock(dstData, 2) == 2);
		CHECK(dstData[0] == srcData[0]);
		CHECK(dstData[1] == srcData[1]);
	}
}

const std::string FILE_NAME = "data.txt";

TEST_CASE("After encryption and decryption file stream, the data must be the same")
{
	SECTION("writing and reading one byte at a time")
	{
		{
			auto encryptedStream = make_unique<CFileOutputStream>(FILE_NAME)
				<< AddFunctionality<CEncryptedOutputStream>(100500)
				<< AddFunctionality<CEncryptedOutputStream>(3);

			encryptedStream->WriteByte('A');
			encryptedStream->WriteByte('\n');
			encryptedStream->WriteByte('2');
		}
		{
			auto decryptedStream = make_unique<CFileInputStream>(FILE_NAME)
				<< AddFunctionality<CDecryptedInputStream>(100500)
				<< AddFunctionality<CDecryptedInputStream>(3);

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
				<< AddFunctionality<CEncryptedOutputStream>(100500)
				<< AddFunctionality<CEncryptedOutputStream>(3);

			encryptedStream->WriteBlock(srcData, 2);
		}
		{
			auto decryptedStream = make_unique<CFileInputStream>(FILE_NAME)
				<< AddFunctionality<CDecryptedInputStream>(100500)
				<< AddFunctionality<CDecryptedInputStream>(3);

			char dstData[2];
			CHECK(decryptedStream->ReadBlock(dstData, 2) == 2);
			CHECK(dstData[0] == srcData[0]);
			CHECK(dstData[1] == srcData[1]);
		}
	}
}