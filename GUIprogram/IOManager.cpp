#include "IOManager.h"

#include <fstream>

bool IOManager::readFileToBuffer(std::string filePath, std::vector<char>& buffer) {
	//need a flag to read in files in binary format, reading in as binary gets the exact contents of the file, the raw data
	std::ifstream file(filePath,std::ios::binary);
	if (file.fail()) {
		perror(filePath.c_str()); //will be specific to the problem, after custom message is ": "
		return false;
	}

	//seek to the end of the file, seekg tells how many bytes in the file so that the vector knows the size
	file.seekg(0, std::ios::end); //byte offset; what byte is relative to (end of file)

	//Get the file size
	int fileSize = file.tellg(); //tellg returns an integer of how many bytes in the file
	file.seekg(0, std::ios::beg); //seek back to te beginning to read the file

	 
}