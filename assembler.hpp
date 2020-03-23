#pragma once
#include <iostream>
#include <string>
#include "mips_tokenizer.hpp"
#include "instruction.hpp"



inline void assemble(const std::string& input)
{	
	auto tokens = mips_tokenize("lbu $t1, imm($t2)");

	if (tokens.begin() == tokens.end())
		throw std::exception("input missing mnemonic");


	auto mnemonic = tokens.front();
	tokens.pop_front();

	if (mnemonic_to_instruction.count(mnemonic.text) == 0)
		throw std::exception(fmt::format("unknown instruction \"{}\"", mnemonic.text).c_str());

	auto instruction_info = mnemonic_to_instruction[mnemonic.text];

	auto& operand_order = instruction_info->p_operand_order;


	while(tokens.begin() != tokens.end())
	{

		auto token = tokens.front();
		tokens.pop_front();

		if(token.type == mips_token_type::dollar)
		{
			// expecting register

			auto reg = tokens.front();
			tokens.pop_front();
			
		}
		

		
	}
	
	
	return;
}
