#ifndef COMMAND_LINE_H
#define COMMAND_LINE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "../build.h"

namespace base {

class CommandLine
{
public:
	int getArgc() const { return argc; }
	char** getArgv() const { return argv; }

	static int Init(int argc, char** argv);
		
	CommandLine();
	CommandLine(int argc, char** argv);
	~CommandLine();

private:
	int argc;
	char** argv;

	static void PrintHeader();
	static void LoadFile(std::string& input);
	static bool ArgumentsExist(int argc);

	static void A(std::string filename, std::vector<std::vector<std::string>> filters);

	static bool FilePresent(int argc);
	static std::vector<std::vector<std::string>> ReadFilters(std::vector<std::string> &args);
};

} //namespace base

#endif // !COMMAND_LINE_H

