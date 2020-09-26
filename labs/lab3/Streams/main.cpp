#include "InputStreamDecorators.h"
#include "InputStreams.h"
#include "OutputStreamDecorators.h"
#include "OutputStreams.h"
#include <iostream>

bool CreateStreamsFromArgs(IInputDataStreamPtr& inputStream, IOutputDataStreamPtr& outputStream, int argc, char* argv[])
{
	int i = 1;
	while (i < argc - 2)
	{
		std::string option = argv[i];
		if (option == "--encrypt")
		{
			unsigned key = atoi(argv[++i]);
			outputStream = std::make_unique<CEncryptedOutputStream>(std::move(outputStream), key);
		}
		else if (option == "--decrypt")
		{
			unsigned key = atoi(argv[++i]);
			inputStream = std::make_unique<CDecryptedInputStream>(std::move(inputStream), key);
		}
		else if (option == "--compress")
		{
			outputStream = std::make_unique<CCompressedOutputStream>(std::move(outputStream));
		}
		else if (option == "--decompress")
		{
			inputStream = std::make_unique<CDecompressedInputStream>(std::move(inputStream));
		}
		else
		{
			std::cout << "Unknown option: " << argv[i] << std::endl;
			return false;
		}

		i++;
	}
	return true;
}

void CopyFile(IInputDataStreamPtr& inputStream, IOutputDataStreamPtr& outputStream)
{
	while (!inputStream->IsEOF())
	{
		try
		{
			outputStream->WriteByte(inputStream->ReadByte());
		}
		catch (const std::exception&)
		{
		}
	}
}

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		std::cout << "Invalid parameters\nUsage: "
				  << "streams.exe [<options>] <input file name> <output file name>" << std::endl;
		return 1;
	}

	std::string inputFileName = argv[argc - 2];
	std::string outputFileName = argv[argc - 1];

	IInputDataStreamPtr inputStream = std::make_unique<CFileInputStream>(inputFileName);
	IOutputDataStreamPtr outputStream = std::make_unique<CFileOutputStream>(outputFileName);

	if (!CreateStreamsFromArgs(inputStream, outputStream, argc, argv))
	{
		return 1;
	}

	CopyFile(inputStream, outputStream);

	return 0;
}