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

typedef std::unique_ptr<IInputDataStream> IInputDataStreamPtr;

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

class CMemoryInputStream : public IInputDataStream
{
public:
	CMemoryInputStream(std::vector<uint8_t>& memoryStream)
		: m_stream(memoryStream)
	{
	}

	bool IsEOF() const override
	{
		return m_pos == m_stream.size();
	}

	uint8_t ReadByte() override
	{
		if (IsEOF())
		{
			throw std::ios_base::failure("Failed to read byte from memory stream");
		}
		return m_stream[m_pos++];
	}

	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override
	{
		if (size > m_stream.size() - m_pos)
		{
			size = m_stream.size() - m_pos;
		}

		auto buffer = static_cast<uint8_t*>(dstBuffer);
		for (std::streamsize i = 0; i < size; i++)
		{
			*buffer = m_stream[m_pos++];
			buffer++;
		}
		return size;
	}

private:
	std::vector<uint8_t>& m_stream;
	size_t m_pos = 0;
};