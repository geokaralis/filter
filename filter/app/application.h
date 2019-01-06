#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>
#include "../base/command_line/command_line.h"

namespace app {

// Initialises the core application, taking user input and applying filters
// to a specified image.
void Init(int argc, char** argv);

// Parses a vector containing command line arguments. The method splits each
// argument by the delimiter i.e. -f, and returns the splited arguments in a
// vector.
// e.g.
// vector[-f linear -1 -1 -1 1 1 1 -f gamma 2.0]       // original arguments vector
// parsedVector[{linear -1 -1 -1 1 1 1}, {gamma 2.0}]  // return vector after parsing
std::vector<std::vector<std::string>> ParseFiltersFromArguments(std::vector<std::string>& args);

bool ArgumentsExist(int argc);
bool FilePresent(int argc);
void LoadFile(std::string & input);

} // namespace app

#endif // !APPLICATION_H