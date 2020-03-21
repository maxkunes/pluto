#include <spdlog/spdlog.h>
#include <cxxopts/cxxopts.hpp>
#include "settings.hpp"
#include "disassembler.hpp"

using namespace pluto;

cxxopts::Options options("Pluto", "Mips Assembler and Debugger");
settings env_settings;

void process_command_line(int argc, char* argv[])
{
	options.add_options()
		("ips", "Instructions Per Second", cxxopts::value<int>()->default_value("-1"));

	try {
		const auto parse_result = options.parse(argc, argv);

		env_settings.instructions_per_second = parse_result["ips"].as<int>();
	}
	catch(const cxxopts::OptionParseException& ex)
	{
		spdlog::error("Failed to parse command line arguments with error {}", ex.what());
	}
}

int main(int argc, char* argv[])
{
	process_command_line(argc, argv);

	byte_array4 add = { 2, 0x32, 0x80, 0x20 };
	
	spdlog::info("{}", disassemble(add));
	
	return 0;
}