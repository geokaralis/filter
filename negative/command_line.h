#pragma once
#include <iostream>
#include <fstream>
#include <string>

#include "negative.h"
#include "string"

#define LOG(x) std::cout << x << std::endl;

namespace CommandLine {
	void PrintLogo();
	bool FilePresent(int argc);

	char* PromptUser(std::string &input);

	int Init(int argc, char** argv);
}

