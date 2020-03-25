#pragma once
#include <memory>
#include "register.hpp"

class cpu_state
{

public:

	std::unordered_map<reg_type, reg> reg_file = {
		{reg_type::zero, reg(0, reg_usage::read)},
		{reg_type::at,  reg()},
		{reg_type::v0,  reg()},
		{reg_type::v1,  reg()},
		{reg_type::a0,  reg()},
		{reg_type::a1, reg()},
		{reg_type::a2, reg()},
		{reg_type::a3, reg()},
		{reg_type::t0, reg()},
		{reg_type::t1, reg()},
		{reg_type::t2, reg()},
		{reg_type::t3, reg()},
		{reg_type::t4, reg()},
		{reg_type::t5, reg()},
		{reg_type::t6, reg()},
		{reg_type::t7, reg()},
		{reg_type::s0, reg()},
		{reg_type::s1, reg()},
		{reg_type::s2, reg()},
		{reg_type::s3, reg()},
		{reg_type::s4, reg()},
		{reg_type::s5, reg()},
		{reg_type::s6, reg()},
		{reg_type::s7, reg()},
		{reg_type::t8, reg()},
		{reg_type::t9, reg()},
		{reg_type::k0, reg()},
		{reg_type::k1, reg()},
		{reg_type::gp, reg()},
		{reg_type::sp, reg()},
		{reg_type::fp, reg()},
		{reg_type::ra, reg()}
	};
};

using cpu_state_pointer = std::unique_ptr<cpu_state>;