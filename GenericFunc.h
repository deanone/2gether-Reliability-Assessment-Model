#ifndef GENERIC_FUNC_H
#define GENERIC_FUNC_H

#include <string>

namespace gnfnc
{
	/*!
	 * Returns the absolute path of the executable's directory.
	 * @return the absolute path of the executable's directory.
	 */
	std::string getExecutablePath();
	
	/*!
	 * Returns the absolute path a file located in the executable's directory.
	 * @param fileName the name of the file (e.g., file.txt)
	 * @return the absolute path of the file
	 */
	std::string getExecutablePathAndMatchItWithFilename(const std::string& fileName);
}

#endif	//	GENERIC_FUNC_H