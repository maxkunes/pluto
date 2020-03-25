#pragma once
#include <memory>
#include "register.hpp"

class cpu_state
{

public:
	reg zero{ 0x0, reg_usage::read };
	reg at;
	reg v0;
	reg v1;
	reg a0;
	reg a1;
	reg a2;
	reg a3;
	reg t0;
	reg t1;
	reg t2;
	reg t3;
	reg t4;
	reg t5;
	reg t6;
	reg t7;
	reg s0;
	reg s1;
	reg s2;
	reg s3;
	reg s4;
	reg s5;
	reg s6;
	reg s7;
	reg t8;
	reg t9;
	reg k0;
	reg k1;
	reg gp;
	reg sp;
	reg fp;
	reg ra;
};

using cpu_state_pointer = std::unique_ptr<cpu_state>;