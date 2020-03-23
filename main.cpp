#include <spdlog/spdlog.h>
#include <CLI11.hpp>

#include "assembler.hpp"
#include "settings.hpp"
#include "disassembler.hpp"
#include "tokenizer.hpp"

using namespace pluto;


settings env_settings;

int main(int argc, char* argv[])
{

	auto info = get_instruction_info(0x0, 0x0);

	try {

		assemble("test");

	}
	catch(const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}
	
	//spdlog::info("{}", info->pretty_print("$rs", "$t1", "$t2", "", "12"));
	
	//auto tokens = tokenizer::tokenize("lbu $rt, imm($rs)");
	
	byte_array4 add = { 0x95, 0x49, 00, 0x32 };
	
	spdlog::info("{}", disassemble(add));
	
	return 0;
}