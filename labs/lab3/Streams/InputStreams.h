#pragma once

#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>

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
	std::ifstream m_stream;
};
