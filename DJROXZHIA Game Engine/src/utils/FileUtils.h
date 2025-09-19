#ifndef DJROXZHIA_FILEUTILS
#define DJROXZHIA_FILEUTILS

#include <string>
#include <vector>

namespace DJROXZHIA {

	struct FileUtils
	{
		static std::string ReadFile(const char* path);

		//static std::string OpenFile(const char* filter);
		//static std::string SaveFile(const char* filter);
		//
		static bool CheckExtension(const std::string& path, const std::vector<const char*>& extensions);
	};

}

#endif // !DJROXZHIA_FILEUTILS