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
	{
	}

	void WriteByte(uint8_t data) override
	{
	}

	void WriteBlock(const void* srcData, std::streamsize size) override
	{
	}
};

class CMemoryOutputStream : public IOutputDataStream
{

public:
	CMemoryOutputStream(std::vector<uint8_t>& memoryStream)
	{
	}

	void WriteByte(uint8_t data) override
	{
	}

	void WriteBlock(const void* srcData, std::streamsize size) override
	{
	}
};
