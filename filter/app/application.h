#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>
#include "../base/command_line/command_line.h"

namespace app {

bool ArgumentsExist(int argc);
bool FilePresent(int argc);
void LoadFile(std::string & input);
std::vector<std::vector<std::string>> ParseFiltersFromArguments(std::vector<std::string>& args);
void Init(int argc, char** argv);

} // namespace app

#endif // !APPLICATION_H