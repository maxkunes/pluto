#pragma once
#include <iostream>
#include <frozen/unordered_map.h>
#include <frozen/string.h>

#include "fnv1a.hpp"

enum class reg_type : std::int8_t
{
	invalid = -1,
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


/*
 *
 *	for(int i = (int)reg_type::invalid; i<= (int)reg_type::ra; i++)
	{
		std::string name = to_string(reg_type(i));

		std::cout << fmt::format("{{{}, \"{}\"}},",  i - 1, name) << std::endl;
	}
	
 * 
 */


static constexpr frozen::unordered_map<reg_type, const char*, 33> reg_type_to_string = {
	{reg_type::invalid, "invalid"},
	{reg_type::zero, "zero"},
	{reg_type::at, "at"},
	{reg_type::v0, "v0"},
	{reg_type::v1, "v1"},
	{reg_type::a0, "a0"},
	{reg_type::a1, "a1"},
	{reg_type::a2, "a2"},
	{reg_type::a3, "a3"},
	{reg_type::t0, "t0"},
	{reg_type::t1, "t1"},
	{reg_type::t2, "t2"},
	{reg_type::t3, "t3"},
	{reg_type::t4, "t4"},
	{reg_type::t5, "t5"},
	{reg_type::t6, "t6"},
	{reg_type::t7, "t7"},
	{reg_type::s0, "s0"},
	{reg_type::s1, "s1"},
	{reg_type::s2, "s2"},
	{reg_type::s3, "s3"},
	{reg_type::s4, "s4"},
	{reg_type::s5, "s5"},
	{reg_type::s6, "s6"},
	{reg_type::s7, "s7"},
	{reg_type::t8, "t8"},
	{reg_type::t9, "t9"},
	{reg_type::k0, "k0"},
	{reg_type::k1, "k1"},
	{reg_type::gp, "gp"},
	{reg_type::sp, "sp"},
	{reg_type::fp, "fp"},
	{reg_type::ra, "ra"}
};



/*
		for (int i = (int)reg_type::invalid; i <= (int)reg_type::ra; i++)
	{
		std::string name = reg_type_to_string.at((reg_type)i);

		std::cout << fmt::format("{{fnv1a(\"{}\"), reg_type::{}}},", name.c_str(), name) << std::endl;
	}

 */

static const frozen::unordered_map<std::uint64_t, reg_type, 33> reg_hash_to_type = {
	{fnv1a("invalid"), reg_type::invalid},
	{fnv1a("zero"), reg_type::zero},
	{fnv1a("at"), reg_type::at},
	{fnv1a("v0"), reg_type::v0},
	{fnv1a("v1"), reg_type::v1},
	{fnv1a("a0"), reg_type::a0},
	{fnv1a("a1"), reg_type::a1},
	{fnv1a("a2"), reg_type::a2},
	{fnv1a("a3"), reg_type::a3},
	{fnv1a("t0"), reg_type::t0},
	{fnv1a("t1"), reg_type::t1},
	{fnv1a("t2"), reg_type::t2},
	{fnv1a("t3"), reg_type::t3},
	{fnv1a("t4"), reg_type::t4},
	{fnv1a("t5"), reg_type::t5},
	{fnv1a("t6"), reg_type::t6},
	{fnv1a("t7"), reg_type::t7},
	{fnv1a("s0"), reg_type::s0},
	{fnv1a("s1"), reg_type::s1},
	{fnv1a("s2"), reg_type::s2},
	{fnv1a("s3"), reg_type::s3},
	{fnv1a("s4"), reg_type::s4},
	{fnv1a("s5"), reg_type::s5},
	{fnv1a("s6"), reg_type::s6},
	{fnv1a("s7"), reg_type::s7},
	{fnv1a("t8"), reg_type::t8},
	{fnv1a("t9"), reg_type::t9},
	{fnv1a("k0"), reg_type::k0},
	{fnv1a("k1"), reg_type::k1},
	{fnv1a("gp"), reg_type::gp},
	{fnv1a("sp"), reg_type::sp},
	{fnv1a("fp"), reg_type::fp},
	{fnv1a("ra"), reg_type::ra},
};

template<typename T, typename std::enable_if_t<std::is_integral<T>::value>* = nullptr>
reg_type reg_type_from_index(const T& index)
{
	return static_cast<reg_type>(index);
}


enum class reg_usage : std::uint8_t
{
	reserved,
	read,
	write,
};

inline reg_usage operator|(reg_usage a, reg_usage b)
{
	return static_cast<reg_usage>(static_cast<int>(a) | static_cast<int>(b));
}

class reg
{
public:

	reg(const std::uint32_t default_value = 0x0, const reg_usage usage = reg_usage::read | reg_usage::write) :  default_value(default_value), usage(usage), value(default_value)
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

