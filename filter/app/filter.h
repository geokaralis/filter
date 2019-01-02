#ifndef APP_FILTER_H
#define APP_FILTER_H

#include <iostream>
#include "../base/command_line/command_line.h"

namespace filter {
	bool ArgumentsExist(int argc);
	bool FilePresent(int argc);
	void LoadFile(std::string & input);
	std::vector<std::vector<std::string>> ParseFiltersFromArguments(std::vector<std::string>& args);
	void InitApplication(int argc, char** argv);

} // namespace filter

#endif // !FILTER_H

