#pragma once
#include <spdlog/spdlog.h>
#include <array>
#include <sstream>
#include "instruction.hpp"
#include "register.hpp"


using byte = std::uint8_t;

template<std::uint32_t size>
using byte_array = std::array<byte, size>;
using byte_array4 = byte_array<4>;


class instruction_parser
{
public:

	explicit instruction_parser(const byte_array4& instruction) :
		byte_array(instruction),
		format(instruction_format::invalid),
		type(instruction_type::invalid),
		rs(reg_type::invalid),
		rt(reg_type::invalid),
		rd(reg_type::invalid),
		imm(-1),
		shamt(-1)
	{
		spdlog::info("New instruction created {}", to_uint32());
		parse_instruction_type();
	}
	
	void parse_instruction_type()
	{
		const std::uint8_t opcode = to_uint32(31, 26);

		if(opcode == 0)
		{
			parse_r_type_instruction();
		}
		else
		{
			parse_ij_type_instruction();
		}
	}

	void parse_r_type_instruction()
	{
		const std::uint8_t function	= to_uint32(5, 0);
		rs							= reg_type_from_index(to_uint32(25, 21));
		rt							= reg_type_from_index(to_uint32(20, 16));
		rd							= reg_type_from_index(to_uint32(15, 11));
		shamt						= to_uint32(10, 6);
		
		format = instruction_format::format_r;
		type = function_to_instruction_type(function);
	}

	void parse_ij_type_instruction()
	{
		const std::uint8_t opcode	= to_uint32(31, 26);
		rs							= reg_type_from_index(to_uint32(25, 21));
		rt							= reg_type_from_index(to_uint32(20, 16));
		rd							= reg_type_from_index(to_uint32(15, 11));

		format = is_valid_j_type(opcode) ? instruction_format::format_j : instruction_format::format_i;
		type = opcode_to_instruction_type(opcode);
	}
	
	std::uint32_t to_uint32(const std::uint32_t first_pos, const std::uint32_t last_pos) 
	{
		const std::uint32_t sll = 31 - first_pos;
		const std::uint32_t srl = last_pos + (sll) ;
		std::uint32_t out = to_uint32() << sll;
		out = out >> srl;
		return out;
	}
	
	std::uint32_t to_uint32()
	{
		std::uint32_t out = 0x0;
		std::uint32_t data = 0x0;

		data = std::uint32_t(byte_array[0]) << 24;
		out |= (data % 0xFF000000);

		data = std::uint32_t(byte_array[1]) << 16;
		out |= (data % 0x00FF0000);

		data = std::uint32_t(byte_array[2]) << 8;
		out |= (data % 0x0000FF00);

		data = std::uint32_t(byte_array[3]) << 0;
		out |= (data % 0x000000FF);

		return out;
	}
	
	byte_array4				byte_array;
	instruction_format		format;
	instruction_type		type;

	reg_type rs;
	reg_type rt;
	reg_type rd;
	std::uint32_t imm;
	std::uint32_t shamt;
};

inline std::string disassemble(const byte_array4& instruction)
{
	instruction_parser parsed(instruction);

	std::stringstream stream;
	
	if(parsed.format == instruction_format::format_r)
	{
		stream << to_string(parsed.type) << " ";

		bool need_comma = false;
		
		if (parsed.rd != reg_type::invalid) {
			stream << "$" << to_string(parsed.rd);
			need_comma = true;
		}
			
		if (parsed.rt != reg_type::invalid) {

			if (need_comma)
				stream << ", ";
			
			stream << "$" << to_string(parsed.rt);
			need_comma = true;
		}
		
		if (parsed.rs != reg_type::invalid) {
			
			if (need_comma)
				stream << ", ";
			
			stream << "$" << to_string(parsed.rs);
			need_comma = true;
		}
		
	}

	return stream.str(); 
}
