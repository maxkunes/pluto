#pragma once
#include "il.hpp"
#include "state.hpp"

// il   ->  mips_il -> run
// text ->  il  ->  mips_asss   -> bin
// bin  ->  il  ->  mips_diss -> text


// text -> bin
// bin  -> bin

// bin  -> text

// bin -> il
// il  -> run

class mips_il
{
public:
	virtual ~mips_il() = default;

	virtual void emulate(cpu_state& state)
	{
		throw std::exception("can't emulate base instruction");
	}
};


class mips_il_add : public mips_il, public il_addr
{
public:
	mips_il_add(operand_pointer dest, operand_pointer src_a, operand_pointer src_b)
		: il_addr(std::move(dest), std::move(src_a), std::move(src_b)) {}
	
	virtual void emulate(cpu_state& state)
	{
		auto dst   = static_cast<reg_type>(operands[0]->value);
		auto src_a = static_cast<reg_type>(operands[1]->value);
		auto src_b = static_cast<reg_type>(operands[2]->value);

		state.reg_file[dst].value = state.reg_file[src_a].value + state.reg_file[src_b].value;
	}
};


class mips_il_loadi : public mips_il, public il_loadi
{
public:
	mips_il_loadi(operand_pointer dest, operand_pointer src)
		: il_loadi(std::move(dest), std::move(src)) {}

	virtual void emulate(cpu_state& state)
	{
		auto dst = static_cast<reg_type>(operands[0]->value);
		auto src = static_cast<std::uint32_t>(operands[1]->value);

		state.reg_file[dst].value = src;
	}
};

class mips_il_mov : public mips_il, public il_movr
{
public:
	mips_il_mov(operand_pointer dest, operand_pointer src)
		: il_movr(std::move(dest), std::move(src)) {}

	virtual void emulate(cpu_state& state)
	{
		auto dst = static_cast<reg_type>(operands[0]->value);
		auto src = static_cast<reg_type>(operands[1]->value);

		state.reg_file[dst].value = state.reg_file[src].value;
	}
};
