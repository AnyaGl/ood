#pragma once
#include "InputStreams.h"
#include <algorithm>
#include <numeric>
#include <random>
#include "Chunk.h"

class CInputStreamDecorator : public IInputDataStream
{
public:
	bool IsEOF() const override
	{
		return m_stream->IsEOF();
	}

protected:
	CInputStreamDecorator(IInputDataStreamPtr&& inputStream)
		: m_stream(std::move(inputStream))
	{
	}

	IInputDataStreamPtr m_stream;
};

class CDecryptedInputStream : public CInputStreamDecorator
{

public:
	CDecryptedInputStream(IInputDataStreamPtr&& stream, unsigned key)
		: CInputStreamDecorator(std::move(stream))
		, m_decryptionTable(256)
	{
		GenerateDecryptionTable(key);
	}

	uint8_t ReadByte() override
	{
		return DecryptByte(m_stream->ReadByte());
	}

	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override
	{
		std::streamsize numberOfReadedBytes = m_stream->ReadBlock(dstBuffer, size);

		auto decryptedBuffer = static_cast<uint8_t*>(dstBuffer);
		for (auto i = 0; i < numberOfReadedBytes; i++)
		{
			*decryptedBuffer = DecryptByte(*decryptedBuffer);
			decryptedBuffer++;
		}

		return numberOfReadedBytes;
	}

private:
	void GenerateDecryptionTable(unsigned key)
	{
		std::vector<uint8_t> encryptionTable(256);
		std::iota(encryptionTable.begin(), encryptionTable.end(), 0);
		std::shuffle(encryptionTable.begin(), encryptionTable.end(), std::mt19937(key));

		for (size_t i = 0; i < 256; i++)
		{
			m_decryptionTable[encryptionTable[i]] = (uint8_t)i;
		}
	}

	uint8_t DecryptByte(uint8_t byte) const
	{
		return m_decryptionTable[byte];
	}

	std::vector<uint8_t> m_decryptionTable;
};

class CDecompressedInputStream : public CInputStreamDecorator
{

public:
	CDecompressedInputStream(IInputDataStreamPtr&& stream)
		: CInputStreamDecorator(std::move(stream))
	{
	}

	uint8_t ReadByte() override
	{
		if (m_chunk.IsEmpty())
		{
			m_chunk.numberOfBytes = m_stream->ReadByte();
			m_chunk.byte = m_stream->ReadByte();
		}

		m_chunk.numberOfBytes--;
		return m_chunk.byte;
	}

	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override
	{
		auto data = static_cast<uint8_t*>(dstBuffer);
		for (std::streamsize i = 0; i < size; i++)
		{
			try
			{
				*data = ReadByte();
			}
			catch (std::exception&)
			{
				return i + 1;
			}
			data++;
		}
		return size;
	}

private:
	Chunk m_chunk;
};
