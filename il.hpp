#pragma once
#include <iostream>
#include <utility>
#include <vector>


enum class il_operand_type
{
	type_invalid,
	type_imm,
	type_reg,
};

enum class il_operand_size
{
	size_invalid,
	size_reg,
	size_8,
	size_16,
	size_32,
	size_64,
};


class il_operand
{
public:
	il_operand(const std::uint64_t value, const il_operand_type type, const il_operand_size size)
		:	value(value), type(type), size(size) {}
	
	std::uint64_t	value;
	il_operand_type type;
	il_operand_size size;
};

using operand_pointer = std::unique_ptr<il_operand>;
using operand_vector  = std::vector<operand_pointer>;

inline operand_pointer make_operand(const std::uint64_t value, const il_operand_type type, const il_operand_size size)
{
	return std::move(std::make_unique<il_operand>(value, type, size));
}

class il_instruction
{
public:
	virtual ~il_instruction() = default;
	il_instruction(std::string mnemonic = "il_instruction") : mnemonic(std::move(mnemonic)) {}

	
	operand_vector	operands;
	std::string		mnemonic;
};

using instruction_pointer = std::unique_ptr<il_instruction>;
using instruction_vector  = std::vector<instruction_pointer>;

class il_movr : public il_instruction
{
public:
	il_movr(operand_pointer dest, operand_pointer src) : il_instruction("movr")
	{
		if (dest->type != il_operand_type::type_reg)
			throw std::exception("invalid dest operand for movr - expecting %reg");

		if (src->type != il_operand_type::type_reg)
			throw std::exception("invalid src operand for movr - expecting %reg");
		
		operands.push_back(std::move(dest));
		operands.push_back(std::move(src));
	}
};

class il_loadi : public il_instruction
{
public:
	il_loadi(operand_pointer dest, operand_pointer src) : il_instruction("loadi")
	{
		if (dest->type != il_operand_type::type_reg)
			throw std::exception("invalid dest operand for loadi - expecting %reg");

		if (src->type != il_operand_type::type_imm)
			throw std::exception("invalid src operand for loadi - expecting %imm");
		
		operands.push_back(std::move(dest));
		operands.push_back(std::move(src));
	}
};

class il_syscall : public il_instruction
{
public:
	il_syscall() : il_instruction("syscall")
	{
	}
};


class il_addr : public il_instruction
{
public:
	il_addr(operand_pointer dest, operand_pointer src_a, operand_pointer src_b) : il_instruction("addr")
	{
		if (dest->type != il_operand_type::type_reg)
			throw std::exception("invalid dest operand for addr - expecting %reg");

		if (src_a->type != il_operand_type::type_reg)
			throw std::exception("invalid src operand for addr - expecting %reg");

		if (src_b->type != il_operand_type::type_reg)
			throw std::exception("invalid src operand for addr - expecting %reg");

		operands.push_back(std::move(dest));
		operands.push_back(std::move(src_a));
		operands.push_back(std::move(src_b));
	}
};
