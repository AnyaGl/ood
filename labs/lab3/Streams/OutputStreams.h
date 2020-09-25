#pragma once

#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class IOutputDataStream
{
public:
	virtual void WriteByte(uint8_t data) = 0;
	virtual void WriteBlock(const void* srcData, std::streamsize size) = 0;

	virtual ~IOutputDataStream() = default;
};

class CFileOutputStream : public IOutputDataStream
{

public:
	CFileOutputStream(const std::string& fileName)
		: m_stream(fileName, std::ios::binary)
	{
		if (!m_stream.is_open())
		{
			throw std::ios_base::failure(fileName + " could not be opened or created");
		}
	}

	void WriteByte(uint8_t data) override
	{
		WriteBlock(&data, 1);
	}

	void WriteBlock(const void* srcData, std::streamsize size) override
	{
		m_stream.write(static_cast<const char*>(srcData), size);
		if (m_stream.fail() || m_stream.bad())
		{
			throw std::ios_base::failure("Failed to write block of bytes to file");
		}
		m_stream.flush();
	}

private:
	std::ofstream m_stream;
};

class CMemoryOutputStream : public IOutputDataStream
{

public:
	CMemoryOutputStream(std::vector<uint8_t>& memoryStream)
		: m_stream(memoryStream)
	{
	}

	void WriteByte(uint8_t data) override
	{
		try
		{
			m_stream.push_back(data);
		}
		catch (std::exception&)
		{
			throw std::ios_base::failure("Failed to write to memory output stream");
		}
	}

	void WriteBlock(const void* srcData, std::streamsize size) override
	{
		auto buffer = static_cast<const uint8_t*>(srcData);
		for (std::streamsize i = 0; i < size; i++)
		{
			WriteByte(*buffer);
			buffer++;
		}
	}

private:
	std::vector<uint8_t>& m_stream;
};
