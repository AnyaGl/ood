#pragma once

#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class IInputDataStream
{
public:
	virtual bool IsEOF() const = 0;
	virtual uint8_t ReadByte() = 0;
	virtual std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) = 0;

	virtual ~IInputDataStream() = default;
};

class CFileInputStream : public IInputDataStream
{
public:
	CFileInputStream(const std::string& fileName)
	{
		m_stream.open(fileName, std::ios::binary);
		if (!m_stream.is_open())
		{
			throw std::ios_base::failure(fileName + " could not be opened");
		}
	}

	bool IsEOF() const override
	{
		return m_stream.eof();
	}

	uint8_t ReadByte() override
	{
		char byte;
		m_stream.get(byte);
		if (IsEOF())
		{
			throw std::ios_base::failure("Failed to read byte from file");
		}

		return (uint8_t)byte;
	}

	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override
	{
		m_stream.read(static_cast<char*>(dstBuffer), size);
		if (m_stream.bad())
		{
			throw std::ios_base::failure("Failed to read block from file");
		}
		return m_stream.gcount();
	}

private:
	std::ifstream m_stream;
};

using MemoryStream = std::vector<uint8_t>;

class CMemoryInputStream : public IInputDataStream
{
public:
	CMemoryInputStream(MemoryStream& memoryStream)
	{
	}

	bool IsEOF() const override
	{
		return true;
	}

	uint8_t ReadByte() override
	{
		return 0;
	}

	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override
	{
		return 0;
	}

private:
};