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

	static void Init(int argc, char** argv);
	static int Terminate();
		
	CommandLine();
	CommandLine(int argc, char** argv);
	~CommandLine();

private:
	int argc;
	char** argv;

	static void PrintHeader();
};

} //namespace base

#endif // !COMMAND_LINE_H

