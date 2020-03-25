#pragma once
#include <iostream>
#include <string>
#include "mips_tokenizer.hpp"
#include "instruction.hpp"
#include "fnv1a.hpp"
#include "il.hpp"
#include "mips_il.hpp"
#include "register.hpp"


inline operand_pointer make_reg_operand(const std::string& reg)
{
	const auto reg_type = reg_hash_to_type.at(fnv1a(reg.c_str()));
	return make_operand(static_cast<std::uint64_t>(reg_type), il_operand_type::type_reg, il_operand_size::size_reg);
}

inline operand_pointer make_imm_operand(const std::string& imm, const il_operand_size size = il_operand_size::size_32)
{
	std::uint64_t imm_value = 0;

	try
	{
		imm_value = std::stoull(imm);
	}
	catch(const std::invalid_argument& ex)
	{
		throw std::exception(fmt::format("failed to convert expected integral immediate string {} into an integral type", imm).c_str());
	}
	
	return make_operand(imm_value, il_operand_type::type_imm, il_operand_size::size_32);
}

void assemble_move(mips_token_vector& tokens, instruction_vector& instructions);
void assemble_loadi(mips_token_vector& tokens, instruction_vector& instructions);
void assemble_syscall(mips_token_vector& tokens, instruction_vector& instructions);
void assemble_add(mips_token_vector& tokens, instruction_vector& instructions);

template <std::uint32_t size>
inline instruction_vector mips_il_assemble(const std::array<std::string, size>& lines)
{
	instruction_vector instructions;

	for (auto& line : lines) {

		auto tokens = mips_tokenize(line);

		if (tokens.begin() == tokens.end())
			throw std::exception("input missing mnemonic");


		const auto mnemonic_str = pop_front_token(tokens).text;
		const auto mnemonic = fnv1a(mnemonic_str.c_str());

		switch (mnemonic)
		{
		case fnv1a("move"):
			assemble_move(tokens, instructions);
			break;
		case fnv1a("li"):
			assemble_loadi(tokens, instructions);
			break;
		case fnv1a("syscall"):
			assemble_syscall(tokens, instructions);
			break;
		case fnv1a("add"):
			assemble_add(tokens, instructions);
			break;
		default:
			throw std::exception(fmt::format("mnemonic {} not recognized", mnemonic_str).c_str());
		}

	}

	return instructions;
}

void assemble_move(mips_token_vector& tokens, instruction_vector& instructions)
{

	if (pop_front_token(tokens).type != mips_token_type::dollar)
		throw std::exception("mov expects 1st operand to be reg type");

	const auto dst = pop_front_token(tokens);

	if (pop_front_token(tokens).type != mips_token_type::comma)
		throw std::exception("mov expects 2 operands");
	
	if (pop_front_token(tokens).type != mips_token_type::dollar)
		throw std::exception("mov expects 2nd operand to be reg type");

	const auto src = pop_front_token(tokens);

	if (src.invalid())
		throw std::exception("mov src operand not found");

	if (dst.invalid())
		throw std::exception("mov dst operand not found");

	auto src_operand = make_reg_operand(src.text);
	auto dst_operand = make_reg_operand(dst.text);

	instructions.push_back(std::make_unique<mips_il_mov>(std::move(dst_operand), std::move(src_operand)));
}

void assemble_loadi(mips_token_vector& tokens, instruction_vector& instructions)
{

	if (pop_front_token(tokens).type != mips_token_type::dollar)
		throw std::exception("loadi expects 1st operand to be reg type");

	const auto dst = pop_front_token(tokens);

	if (pop_front_token(tokens).type != mips_token_type::comma)
		throw std::exception("loadi expects 2 operands");

	const auto src = pop_front_token(tokens);
	
	if (src.type != mips_token_type::symbol)
		throw std::exception("loadi expects 2nd operand to be imm type");


	if (src.invalid())
		throw std::exception("loadi src operand not found");

	if (dst.invalid())
		throw std::exception("loadi dst operand not found");

	auto src_operand = make_imm_operand(src.text);
	auto dst_operand = make_reg_operand(dst.text);

	instructions.push_back(std::make_unique<mips_il_loadi>(std::move(dst_operand), std::move(src_operand)));
}

void assemble_syscall(mips_token_vector& tokens, instruction_vector& instructions)
{
	instructions.push_back(std::make_unique<il_syscall>());
}

void assemble_add(mips_token_vector& tokens, instruction_vector& instructions)
{

	if (pop_front_token(tokens).type != mips_token_type::dollar)
		throw std::exception("add expects 1st operand to be reg type");

	const auto dst = pop_front_token(tokens);

	if (pop_front_token(tokens).type != mips_token_type::comma)
		throw std::exception("add expects 2 operands");

	if (pop_front_token(tokens).type != mips_token_type::dollar)
		throw std::exception("add expects 2nd operand to be reg type");

	const auto src_a = pop_front_token(tokens);

	if(src_a.type != mips_token_type::symbol)
		throw std::exception("add expects 2nd operand to be reg type");

	if (pop_front_token(tokens).type != mips_token_type::comma)
		throw std::exception("add expects 3 operands");
	
	if (pop_front_token(tokens).type != mips_token_type::dollar)
		throw std::exception("add expects 3rd operand to be reg type");
	
	const auto src_b = pop_front_token(tokens);

	if (src_b.type != mips_token_type::symbol)
		throw std::exception("add expects 2nd operand to be reg type");

	if (src_b.invalid())
		throw std::exception("add second operand not found");

	if (dst.invalid())
		throw std::exception("add first operand not found");

	auto src_a_operand = make_reg_operand(src_a.text);
	auto src_b_operand = make_reg_operand(src_b.text);
	auto dst_operand = make_reg_operand(dst.text);

	instructions.push_back(std::make_unique<mips_il_add>(std::move(dst_operand), std::move(src_a_operand), std::move(src_b_operand)));
}
