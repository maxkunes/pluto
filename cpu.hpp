#pragma once
#include "state.hpp"
#include "il.hpp"

class mips_cpu
{
public:

	
	void emulate(const instruction_vector& instructions)
	{
		for (auto& instruction : instructions) {

			auto mips_instruction = dynamic_cast<mips_il*>(instruction.get());

			mips_instruction->emulate(state);

			continue;
		}
	}
private:
	cpu_state state;
};
