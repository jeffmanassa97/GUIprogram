#pragma once

#include <vector>

class IOManager //making it a static class instead of instance
{
public:
	static bool readFileToBuffer(std::string filePath, std::vector<char>& buffer); //a vector is a dynamically sized array
};

