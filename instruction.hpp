#pragma once

enum class instruction_format
{
	invalid,
	format_r,
	format_i,
	format_j
};

inline const char* to_string(const instruction_format e)
{
	switch (e)
	{
	case instruction_format::invalid: return "invalid";
	case instruction_format::format_r: return "format_r";
	case instruction_format::format_i: return "format_i";
	case instruction_format::format_j: return "format_j";
	default: return "unknown";
	}
}

enum class instruction_type
{
	invalid,

	/* R TYPE */
	type_add,
	type_addu,
	type_and,
	type_div,
	type_divu,
	type_mult,
	type_multu,
	type_nor,
	type_or,
	type_xor,
	type_sll,
	type_sllv,
	type_sra,
	type_srav,
	type_srl,
	type_srlv,
	type_sub,
	type_subu,
	type_jr,
	type_jalr,
	type_syscall,
	type_mfhi,
	type_mthi,
	type_mflo,
	type_mtlo,
	type_slt,
	type_sltu,

	/* J TYPE */
	type_j,
	type_jal,


	/* I TYPE */
	type_beq,
	type_bne,
	type_blez,
	type_bgtz,
	type_addi,
	type_addiu,
	type_slti,
	type_sltiu,
	type_andi,
	type_ori,
	type_xori,
	type_lui,
	type_lb,
	type_lh,
	type_lw,
	type_lbu,
	type_lhu,
	type_sb,
	type_sh,
	type_sw
};

inline const char* to_string(const instruction_type e)
{
	switch (e)
	{
	case instruction_type::invalid: return "invalid";
	case instruction_type::type_add: return "add";
	case instruction_type::type_addu: return "addu";
	case instruction_type::type_and: return "and";
	case instruction_type::type_div: return "div";
	case instruction_type::type_divu: return "divu";
	case instruction_type::type_mult: return "mult";
	case instruction_type::type_multu: return "multu";
	case instruction_type::type_nor: return "nor";
	case instruction_type::type_or: return "or";
	case instruction_type::type_xor: return "xor";
	case instruction_type::type_sll: return "sll";
	case instruction_type::type_sllv: return "sllv";
	case instruction_type::type_sra: return "sra";
	case instruction_type::type_srav: return "srav";
	case instruction_type::type_srl: return "srl";
	case instruction_type::type_srlv: return "srlv";
	case instruction_type::type_sub: return "sub";
	case instruction_type::type_subu: return "subu";
	case instruction_type::type_jr: return "jr";
	case instruction_type::type_jalr: return "jalr";
	case instruction_type::type_syscall: return "syscall";
	case instruction_type::type_mfhi: return "mfhi";
	case instruction_type::type_mthi: return "mthi";
	case instruction_type::type_mflo: return "mflo";
	case instruction_type::type_mtlo: return "mtlo";
	case instruction_type::type_slt: return "slt";
	case instruction_type::type_sltu: return "sltu";
	case instruction_type::type_j: return "j";
	case instruction_type::type_jal: return "jal";
	case instruction_type::type_beq: return "beq";
	case instruction_type::type_bne: return "bne";
	case instruction_type::type_blez: return "blez";
	case instruction_type::type_bgtz: return "bgtz";
	case instruction_type::type_addi: return "addi";
	case instruction_type::type_addiu: return "addiu";
	case instruction_type::type_slti: return "slti";
	case instruction_type::type_sltiu: return "sltiu";
	case instruction_type::type_andi: return "andi";
	case instruction_type::type_ori: return "ori";
	case instruction_type::type_xori: return "xori";
	case instruction_type::type_lui: return "lui";
	case instruction_type::type_lb: return "lb";
	case instruction_type::type_lh: return "lh";
	case instruction_type::type_lw: return "lw";
	case instruction_type::type_lbu: return "lbu";
	case instruction_type::type_lhu: return "lhu";
	case instruction_type::type_sb: return "sb";
	case instruction_type::type_sh: return "sh";
	case instruction_type::type_sw: return "sw";
	default: return "invalid";
	}
}



inline instruction_type function_to_instruction_type (const std::uint16_t function)
{
	instruction_type type = instruction_type::invalid;
	
	switch (function)
	{
	case 0:
		type = instruction_type::type_sll;
		break;
	case 2:
		type = instruction_type::type_srl;
		break;
	case 3:
		type = instruction_type::type_sra;
		break;
	case 4:
		type = instruction_type::type_sllv;
		break;
	case 6:
		type = instruction_type::type_srlv;
		break;
	case 7:
		type = instruction_type::type_srav;
		break;
	case 8:
		type = instruction_type::type_jr;
		break;
	case 9:
		type = instruction_type::type_jalr;
		break;
	case 12:
		type = instruction_type::type_syscall;
		break;
	case 16:
		type = instruction_type::type_mfhi;
		break;
	case 17:
		type = instruction_type::type_mthi;
		break;
	case 18:
		type = instruction_type::type_mflo;
		break;
	case 19:
		type = instruction_type::type_mtlo;
		break;
	case 24:
		type = instruction_type::type_mult;
		break;
	case 25:
		type = instruction_type::type_multu;
		break;
	case 26:
		type = instruction_type::type_div;
		break;
	case 27:
		type = instruction_type::type_divu;
		break;
	case 32:
		type = instruction_type::type_add;
		break;
	case 33:
		type = instruction_type::type_addu;
		break;
	case 34:
		type = instruction_type::type_sub;
		break;
	case 35:
		type = instruction_type::type_subu;
		break;
	case 36:
		type = instruction_type::type_and;
		break;
	case 37:
		type = instruction_type::type_or;
		break;
	case 38:
		type = instruction_type::type_xor;
		break;
	case 39:
		type = instruction_type::type_nor;
		break;
	case 42:
		type = instruction_type::type_slt;
		break;
	case 43:
		type = instruction_type::type_sltu;
		break;
	default:
		type = instruction_type::invalid;
	}

	return type;
}

inline bool is_valid_r_type(const std::uint16_t function)
{
	return function_to_instruction_type(function) != instruction_type::invalid;
}

inline instruction_type opcode_to_instruction_type(const std::uint16_t opcode)
{
	instruction_type type = instruction_type::invalid;

	switch (opcode)
	{
	case 2:
		type = instruction_type::type_j;
		break;
	case 3:
		type = instruction_type::type_jal;
		break;

		
	case 4:
		type = instruction_type::type_beq;
		break;
	case 5:
		type = instruction_type::type_bne;
		break;
	case 6:
		type = instruction_type::type_blez;
		break;
	case 7:
		type = instruction_type::type_bgtz;
		break;
	case 8:
		type = instruction_type::type_addi;
		break;
	case 9:
		type = instruction_type::type_addiu;
		break;
	case 10:
		type = instruction_type::type_slti;
		break;
	case 11:
		type = instruction_type::type_sltiu;
		break;
	case 12:
		type = instruction_type::type_andi;
		break;
	case 13:
		type = instruction_type::type_ori;
		break;
	case 14:
		type = instruction_type::type_xori;
		break;
	case 15:
		type = instruction_type::type_lui;
		break;
	case 32:
		type = instruction_type::type_lb;
		break;
	case 33:
		type = instruction_type::type_lh;
		break;
	case 34:
		type = instruction_type::type_lw;
		break;
	case 36:
		type = instruction_type::type_lbu;
		break;
	case 37:
		type = instruction_type::type_lhu;
		break;
	case 40:
		type = instruction_type::type_sb;
		break;
	case 41:
		type = instruction_type::type_sh;
		break;
	case 43:
		type = instruction_type::type_sw;
		break;
	default:
		type = instruction_type::invalid;
	}

	return type;
}

inline bool is_valid_j_type(const std::uint16_t opcode)
{
	instruction_type type = opcode_to_instruction_type(opcode);

	if (type == instruction_type::invalid) return false;

	if (type != instruction_type::type_j && type != instruction_type::type_jal) return false;

	return true;
}

inline bool is_valid_i_type(const std::uint16_t opcode)
{
	instruction_type type = opcode_to_instruction_type(opcode);

	if (type == instruction_type::invalid) return false;

	if (type != instruction_type::type_j && type != instruction_type::type_jal) return true;

	return false;
}

inline bool is_valid_opcode_function(const std::uint16_t opcode_function)
{
	if (is_valid_r_type(opcode_function)) return true;
	if (is_valid_j_type(opcode_function)) return true;
	if (is_valid_i_type(opcode_function)) return true;
}

