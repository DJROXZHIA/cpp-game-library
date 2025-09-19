#include "FileUtils.h"

#include <fstream>
#include <sstream>
#include <iostream>

namespace DJROXZHIA {

	std::string FileUtils::ReadFile(const char* path)
	{
		std::ifstream in(path, std::ios::binary);
		if (in)
		{
			std::string contents;
			in.seekg(0, std::ios::end);
			contents.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&contents[0], contents.size());
			in.close();
			return(contents);
		}
		std::cout << "ERROR::FILEUTILS::FILE NOT FOUND! PATH=" << path << "\n";
		return "";
	}

	bool FileUtils::CheckExtension(const std::string& path, const std::vector<const char*>& extensions)
	{
		std::string file_name = path.substr(path.find_last_of("/") + 1);
		std::string file_extension = file_name.substr(file_name.find_last_of(".") + 1);

		for (const char* extension : extensions)
		{
			if (file_extension == extension)
				return true;
		}
		return false;
	}

}