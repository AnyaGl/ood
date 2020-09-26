#pragma once
#include "Chunk.h"
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

class CCompressedOutputStream : public COutputStreamDecorator
{

public:
	CCompressedOutputStream(IOutputDataStreamPtr&& stream)
		: COutputStreamDecorator(std::move(stream))
	{
	}

	~CCompressedOutputStream()
	{
		FlushChunk();
	}

	void WriteByte(uint8_t data) override
	{
		if (m_chunk.IsEmpty())
		{
			m_chunk = { 1, data };
			return;
		}
		if (m_chunk.byte == data && m_chunk.numberOfBytes < std::numeric_limits<uint8_t>::max())
		{
			m_chunk.numberOfBytes++;
			return;
		}
		FlushChunk();
		m_chunk = { 1, data };
	}

	void WriteBlock(const void* srcData, std::streamsize size) override
	{
		auto data = static_cast<const uint8_t*>(srcData);
		for (std::streamsize i = 0; i < size; i++)
		{
			WriteByte(*data);
			data++;
		}
	}

private:
	void FlushChunk()
	{
		uint8_t chunk[] = { m_chunk.numberOfBytes, m_chunk.byte };
		m_stream->WriteBlock(chunk, 2);
		m_chunk.Reset();
	}

	Chunk m_chunk;
};
