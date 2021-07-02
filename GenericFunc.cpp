#include "GenericFunc.h"
#include "dirent.h"

#include <unistd.h>
#include <limits.h>
#include <sstream>

std::string gnfnc::getExecutablePath()
{
	char result[PATH_MAX];
	size_t found;
	size_t count = readlink("/proc/self/exe", result, PATH_MAX);
	found = std::string(result).find_last_of("/");
	return(std::string(result).substr(0,found) + "/");
}

std::string gnfnc::getExecutablePathAndMatchItWithFilename(const std::string& fileName)
{
	std::string execPath = getExecutablePath();
	size_t found = execPath.find_last_of("/");
	execPath = execPath.substr(0, found);
	std::stringstream ss;
	ss << execPath << "/" << fileName;
	return ss.str();
}