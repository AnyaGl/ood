#pragma once
#include <string>
#include <fstream>

std::string GetDataFromFile(std::string const& fileName)
{
	std::ifstream stream(fileName);
	if (!stream)
	{
		throw std::ios_base::failure(fileName + " could not be opened");
	}
	return std::string((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
}