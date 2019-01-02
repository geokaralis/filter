#include "command_line.h"

namespace base {

const std::string header = "Filter [Build " + std::string(BUILD_VERSION) 
							+ "]\n" + "(c) 2019, George Kavalieros, George Karalis.\n";

void CommandLine::PrintHeader()
{
	std::cout << header;
	std::cout << std::endl;
}

// static
void CommandLine::Init(int argc, char** argv) {
	PrintHeader();
}

int CommandLine::Terminate() {
	std::cout << "Press any key to close..." << std::endl;
	std::cin.ignore();
	std::cin.get();
	return 0;
}

CommandLine::CommandLine() { }

CommandLine::CommandLine(int argc, char** argv) 
	: argc(argc), 
	  argv(argv) { }

CommandLine::~CommandLine() = default;

} // namespace base