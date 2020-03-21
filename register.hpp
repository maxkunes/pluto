#pragma once
#include <iostream>

enum class reg_type : std::uint8_t
{
	invalid,
	zero,
	at,
	v0,
	v1,
	a0,
	a1,
	a2,
	a3,
	t0,
	t1,
	t2,
	t3,
	t4,
	t5,
	t6,
	t7,
	s0,
	s1,
	s2,
	s3,
	s4,
	s5,
	s6,
	s7,
	t8,
	t9,
	k0,
	k1,
	gp,
	sp,
	fp,
	ra,
};

inline const char* to_string(const reg_type e)
{
	switch (e)
	{
	case reg_type::invalid: return "invalid";
	case reg_type::zero: return "zero";
	case reg_type::at: return "at";
	case reg_type::v0: return "v0";
	case reg_type::v1: return "v1";
	case reg_type::a0: return "a0";
	case reg_type::a1: return "a1";
	case reg_type::a2: return "a2";
	case reg_type::a3: return "a3";
	case reg_type::t0: return "t0";
	case reg_type::t1: return "t1";
	case reg_type::t2: return "t2";
	case reg_type::t3: return "t3";
	case reg_type::t4: return "t4";
	case reg_type::t5: return "t5";
	case reg_type::t6: return "t6";
	case reg_type::t7: return "t7";
	case reg_type::s0: return "s0";
	case reg_type::s1: return "s1";
	case reg_type::s2: return "s2";
	case reg_type::s3: return "s3";
	case reg_type::s4: return "s4";
	case reg_type::s5: return "s5";
	case reg_type::s6: return "s6";
	case reg_type::s7: return "s7";
	case reg_type::t8: return "t8";
	case reg_type::t9: return "t9";
	case reg_type::k0: return "k0";
	case reg_type::k1: return "k1";
	case reg_type::gp: return "gp";
	case reg_type::sp: return "sp";
	case reg_type::fp: return "fp";
	case reg_type::ra: return "ra";
	default: return "invalid";
	}
}

inline reg_type reg_type_from_index(const std::uint8_t index)
{
	if(index <= static_cast<std::uint8_t>(reg_type::ra) - 1)
	{
		return static_cast<reg_type>(index + 1);
	}

	return reg_type::invalid;
}

enum class reg_usage
{
	reserved,
	read,
	write,
	readwrite
};

class reg
{
public:

	reg(const reg_usage usage, const std::uint32_t default_value) : usage(usage), default_value(default_value)
	{
		
	}

	void reset()
	{
		value = default_value;
	}


	reg_usage usage;
	std::uint32_t value;
	std::uint64_t default_value;
};

