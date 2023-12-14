#pragma once

#include <vector>
#include <string>

namespace GameEngine {
	class IOManager
	{
	public:
		static bool ReadFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer);
	};
}


