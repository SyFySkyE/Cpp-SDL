#include "IOManager.h"

#include <fstream>

namespace GameEngine {
	bool IOManager::ReadFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer)
	{
		std::ifstream file(filePath, std::ios::binary);

		if (file.fail()) {
			perror(filePath.c_str());
			return false;
		}

		// seek to end
		file.seekg(0, std::ios::end);

		// get file size
		int fileSize = file.tellg();

		// be kind, rewind
		file.seekg(0, std::ios::beg);

		// take out any header data
		fileSize -= file.tellg();

		buffer.resize(fileSize);
		file.read((char*)&(buffer[0]), fileSize);
		file.close();

		return true;
	}

}
