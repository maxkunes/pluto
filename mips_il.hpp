#pragma once
#include "il.hpp"
#include "state.hpp"



class mips_il : public il_instruction
{
	virtual void emulate(cpu_state_pointer& state)
	{
		throw std::exception("can't emulate base instruction");
	}
};


