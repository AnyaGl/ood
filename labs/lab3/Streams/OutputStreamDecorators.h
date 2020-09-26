#pragma once
#include "OutputStreams.h"
#include <algorithm>
#include <numeric>
#include <random>

class COutputStreamDecorator : public IOutputDataStream
{
protected:
	COutputStreamDecorator(IOutputDataStreamPtr&& outputStream)
		: m_stream(std::move(outputStream))
	{
	}

	IOutputDataStreamPtr m_stream;
};

class CEncryptedOutputStream : public COutputStreamDecorator
{

public:
	CEncryptedOutputStream(IOutputDataStreamPtr&& stream, unsigned key)
		: COutputStreamDecorator(std::move(stream))
		, m_encryptionTable(256)
	{
		GenerateEncryptionTable(key);
	}

	void WriteByte(uint8_t data) override
	{
		m_stream->WriteByte(EncryptByte(data));
	}

	void WriteBlock(const void* srcData, std::streamsize size) override
	{
		auto data = static_cast<const uint8_t*>(srcData);
		uint8_t* encryptionData = new uint8_t[(unsigned int)size];

		for (std::streamsize i = 0; i < size; i++)
		{
			encryptionData[i] = EncryptByte(*data);
			data++;
		}
		m_stream->WriteBlock(encryptionData, size);

		delete[] encryptionData;
	}

private:
	void GenerateEncryptionTable(unsigned key)
	{
		std::iota(m_encryptionTable.begin(), m_encryptionTable.end(), 0);
		std::shuffle(m_encryptionTable.begin(), m_encryptionTable.end(), std::mt19937(key));
	}

	uint8_t EncryptByte(uint8_t byte) const
	{
		return m_encryptionTable[byte];
	}

	std::vector<uint8_t> m_encryptionTable;
};