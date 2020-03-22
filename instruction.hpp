#pragma once
#include <memory>
#include <fmt/format.h>

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

enum class operand_order_pos : std::int8_t
{
	pos_invalid = -1,
	pos_first,
	pos_second,
	pos_third,
	pos_fourth
};


class operand_order
{
public:

	operand_order()
		:	rs_pos(operand_order_pos::pos_invalid),
			rt_pos(operand_order_pos::pos_invalid),
			rd_pos(operand_order_pos::pos_invalid),
			imm_pos(operand_order_pos::pos_invalid),
			shamt_pos(operand_order_pos::pos_invalid)
	{
	}
	
	operand_order(const operand_order_pos rs_pos, const operand_order_pos rt_pos, const operand_order_pos rd_pos)
		:	rs_pos(rs_pos),
			rt_pos(rt_pos),
			rd_pos(rd_pos),
			imm_pos(operand_order_pos::pos_invalid),
			shamt_pos(operand_order_pos::pos_invalid)
	{
	}

	operand_order(const operand_order_pos rs_pos, const operand_order_pos rt_pos, const operand_order_pos rd_pos, const operand_order_pos imm_pos, const operand_order_pos shamt_pos)
		:	rs_pos(rs_pos),
			rt_pos(rt_pos),
			rd_pos(rd_pos),
			imm_pos(imm_pos),
			shamt_pos(shamt_pos)
	{
	}

	operand_order_pos rs_pos;
	operand_order_pos rt_pos;
	operand_order_pos rd_pos;
	operand_order_pos imm_pos;
	operand_order_pos shamt_pos;
};

const static auto order_none = std::make_shared<operand_order>();

/* R Type */
const static auto order_rs = std::make_shared<operand_order>(operand_order_pos::pos_first, operand_order_pos::pos_invalid, operand_order_pos::pos_invalid);
const static auto order_rt = std::make_shared<operand_order>(operand_order_pos::pos_invalid, operand_order_pos::pos_first, operand_order_pos::pos_invalid);
const static auto order_rd = std::make_shared<operand_order>(operand_order_pos::pos_invalid, operand_order_pos::pos_invalid, operand_order_pos::pos_first);

const static auto order_rs_rt = std::make_shared<operand_order>(operand_order_pos::pos_first, operand_order_pos::pos_second, operand_order_pos::pos_invalid);
const static auto order_rt_rs = std::make_shared<operand_order>(operand_order_pos::pos_second, operand_order_pos::pos_first, operand_order_pos::pos_invalid);

const static auto order_rd_rt_rs = std::make_shared<operand_order>(operand_order_pos::pos_third, operand_order_pos::pos_second, operand_order_pos::pos_first);
const static auto order_rd_rs_rt = std::make_shared<operand_order>(operand_order_pos::pos_second, operand_order_pos::pos_third, operand_order_pos::pos_first);

const static auto order_rd_rt_shamt = std::make_shared<operand_order>(operand_order_pos::pos_invalid, operand_order_pos::pos_second, operand_order_pos::pos_first, operand_order_pos::pos_invalid, operand_order_pos::pos_third);


/* I and J Type */

const static auto order_imm = std::make_shared<operand_order>(operand_order_pos::pos_invalid, operand_order_pos::pos_invalid, operand_order_pos::pos_invalid, operand_order_pos::pos_first, operand_order_pos::pos_invalid);
const static auto order_rs_imm = std::make_shared<operand_order>(operand_order_pos::pos_first, operand_order_pos::pos_invalid, operand_order_pos::pos_invalid, operand_order_pos::pos_second, operand_order_pos::pos_invalid);
const static auto order_rt_imm = std::make_shared<operand_order>(operand_order_pos::pos_invalid, operand_order_pos::pos_first, operand_order_pos::pos_invalid, operand_order_pos::pos_second, operand_order_pos::pos_invalid);
const static auto order_rs_rt_imm = std::make_shared<operand_order>(operand_order_pos::pos_first, operand_order_pos::pos_second, operand_order_pos::pos_invalid, operand_order_pos::pos_third, operand_order_pos::pos_invalid);
const static auto order_rt_rs_imm = std::make_shared<operand_order>(operand_order_pos::pos_second, operand_order_pos::pos_first, operand_order_pos::pos_invalid, operand_order_pos::pos_third, operand_order_pos::pos_invalid);

const static auto order_rt_imm_rs = std::make_shared<operand_order>(operand_order_pos::pos_third, operand_order_pos::pos_first, operand_order_pos::pos_invalid, operand_order_pos::pos_second, operand_order_pos::pos_invalid);


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

	return false;
}


class instruction_info
{
public:
	instruction_info(const instruction_type type, const instruction_format format, const uint8_t opcode_function, const std::shared_ptr<operand_order> p_operand_order)
		:	type(type), format(format), opcode_function(opcode_function), p_operand_order(p_operand_order)
	{
		
	}

	std::string pretty_print(const std::string& rs = "$rs", const std::string& rt = "$rt", const std::string& rd = "$rd", const std::string& imm = "imm", const std::string& shamt = "shamt")
	{

		const auto opcode = to_string(type);
		std::string operands[4];

		const auto rs_pos		= static_cast<std::int32_t>(p_operand_order->rs_pos);
		const auto rt_pos		= static_cast<std::int32_t>(p_operand_order->rt_pos);
		const auto rd_pos		= static_cast<std::int32_t>(p_operand_order->rd_pos);
		const auto imm_pos		= static_cast<std::int32_t>(p_operand_order->imm_pos);
		const auto shamt_pos	= static_cast<std::int32_t>(p_operand_order->shamt_pos);
		auto max_index			= std::int32_t(0);
		bool deref				= false;
		
		
		if (rs_pos != static_cast<std::int32_t>(operand_order_pos::pos_invalid)) {
			operands[rs_pos] = rs;
			max_index = std::max(max_index, rs_pos);
		}

		if (rt_pos != static_cast<std::int32_t>(operand_order_pos::pos_invalid)) {
			operands[rt_pos] = rt;
			max_index = std::max(max_index, rt_pos);
		}

		if (rd_pos != static_cast<std::int32_t>(operand_order_pos::pos_invalid)) {
			operands[rd_pos] = rd;
			max_index = std::max(max_index, rd_pos);
		}

		if (imm_pos != static_cast<std::int32_t>(operand_order_pos::pos_invalid)) {
			operands[imm_pos] = imm;
			max_index = std::max(max_index, imm_pos);
		}

		if (shamt_pos != static_cast<std::int32_t>(operand_order_pos::pos_invalid)) {
			operands[shamt_pos] = shamt;
			max_index = std::max(max_index, shamt_pos);
		}

		// lhu $rt, imm($rs)
		if(imm_pos != static_cast<std::int32_t>(operand_order_pos::pos_invalid) && imm_pos < rs_pos)
		{
			deref = true;
		}

		if (!deref) {
			switch (max_index + 1)
			{
			case 0:
				return fmt::format("{}", opcode);
				break;
			case 1:
				return fmt::format("{} {}", opcode, operands[0]);
				break;
			case 2:
				return fmt::format("{} {}, {}", opcode, operands[0], operands[1]);
				break;
			case 3:
				return fmt::format("{} {}, {}, {}", opcode, operands[0], operands[1], operands[2]);
				break;
			default:
				return "Error pretty printing instruction!";
			}
		}
		else
		{
			switch (max_index + 1)
			{
			case 2:
				return fmt::format("{} {}({})", opcode, operands[0], operands[1]);
				break;
			case 3:
				return fmt::format("{} {}, {}({})", opcode, operands[0], operands[1], operands[2]);
				break;
			default:
				return "Error pretty printing instruction!";
			}
		}

		return "Error pretty printing instruction!";
	}

	instruction_type type;
	instruction_format format;
	uint8_t opcode_function;
	std::shared_ptr<operand_order> p_operand_order;
};

static std::shared_ptr<instruction_info> info_sll = std::make_shared<instruction_info>
(
	instruction_type::type_sll,
	instruction_format::format_r,
	0,
	order_rd_rt_shamt
	);

static std::shared_ptr<instruction_info> info_srl = std::make_shared<instruction_info>
(
	instruction_type::type_srl,
	instruction_format::format_r,
	2,
	order_rd_rt_shamt
	);

static std::shared_ptr<instruction_info> info_sra = std::make_shared<instruction_info>
(
	instruction_type::type_sra,
	instruction_format::format_r,
	3,
	order_rd_rt_shamt
	);


static std::shared_ptr<instruction_info> info_sllv = std::make_shared<instruction_info>
(
	instruction_type::type_sllv,
	instruction_format::format_r,
	4,
	order_rd_rt_rs
	);

static std::shared_ptr<instruction_info> info_srlv = std::make_shared<instruction_info>
(
	instruction_type::type_srlv,
	instruction_format::format_r,
	6,
	order_rd_rt_rs
	);

static std::shared_ptr<instruction_info> info_srav = std::make_shared<instruction_info>
(
	instruction_type::type_srav,
	instruction_format::format_r,
	7,
	order_rd_rt_rs
	);

static std::shared_ptr<instruction_info> info_jr = std::make_shared<instruction_info>
(
	instruction_type::type_jr,
	instruction_format::format_r,
	8,
	order_rs
	);

static std::shared_ptr<instruction_info> info_jalr = std::make_shared<instruction_info>
(
	instruction_type::type_jalr,
	instruction_format::format_r,
	9,
	order_rs
	);

static std::shared_ptr<instruction_info> info_syscall = std::make_shared<instruction_info>
(
	instruction_type::type_syscall,
	instruction_format::format_r,
	12,
	order_none
	);

static std::shared_ptr<instruction_info> info_mfhi = std::make_shared<instruction_info>
(
	instruction_type::type_mfhi,
	instruction_format::format_r,
	16,
	order_rd
	);

static std::shared_ptr<instruction_info> info_mthi = std::make_shared<instruction_info>
(
	instruction_type::type_mthi,
	instruction_format::format_r,
	17,
	order_rs
	);

static std::shared_ptr<instruction_info> info_mflo = std::make_shared<instruction_info>
(
	instruction_type::type_mflo,
	instruction_format::format_r,
	18,
	order_rd
	);

static std::shared_ptr<instruction_info> info_mtlo = std::make_shared<instruction_info>
(
	instruction_type::type_mtlo,
	instruction_format::format_r,
	19,
	order_rs
	);

static std::shared_ptr<instruction_info> info_mult = std::make_shared<instruction_info>
(
	instruction_type::type_mult,
	instruction_format::format_r,
	24,
	order_rs_rt
	);

static std::shared_ptr<instruction_info> info_multu = std::make_shared<instruction_info>
(
	instruction_type::type_multu,
	instruction_format::format_r,
	25,
	order_rs_rt
	);

static std::shared_ptr<instruction_info> info_div = std::make_shared<instruction_info>
(
	instruction_type::type_div,
	instruction_format::format_r,
	26,
	order_rs_rt
	);

static std::shared_ptr<instruction_info> info_divu = std::make_shared<instruction_info>
(
	instruction_type::type_divu,
	instruction_format::format_r,
	27,
	order_rs_rt
	);

static std::shared_ptr<instruction_info> info_add = std::make_shared<instruction_info>
(
	instruction_type::type_add,
	instruction_format::format_r,
	32,
	order_rd_rs_rt
	);

static std::shared_ptr<instruction_info> info_addu = std::make_shared<instruction_info>
(
	instruction_type::type_addu,
	instruction_format::format_r,
	33,
	order_rd_rs_rt
	);

static std::shared_ptr<instruction_info> info_sub = std::make_shared<instruction_info>
(
	instruction_type::type_sub,
	instruction_format::format_r,
	34,
	order_rd_rs_rt
	);

static std::shared_ptr<instruction_info> info_subu = std::make_shared<instruction_info>
(
	instruction_type::type_subu,
	instruction_format::format_r,
	35,
	order_rd_rs_rt
	);

static std::shared_ptr<instruction_info> info_and = std::make_shared<instruction_info>
(
	instruction_type::type_and,
	instruction_format::format_r,
	36,
	order_rd_rs_rt
	);


static std::shared_ptr<instruction_info> info_or = std::make_shared<instruction_info>
(
	instruction_type::type_or,
	instruction_format::format_r,
	37,
	order_rd_rs_rt
	);


static std::shared_ptr<instruction_info> info_xor = std::make_shared<instruction_info>
(
	instruction_type::type_xor,
	instruction_format::format_r,
	38,
	order_rd_rs_rt
	);

static std::shared_ptr<instruction_info> info_nor = std::make_shared<instruction_info>
(
	instruction_type::type_nor,
	instruction_format::format_r,
	39,
	order_rd_rs_rt
	);

static std::shared_ptr<instruction_info> info_slt = std::make_shared<instruction_info>
(
	instruction_type::type_slt,
	instruction_format::format_r,
	42,
	order_rd_rs_rt
	);

static std::shared_ptr<instruction_info> info_sltu = std::make_shared<instruction_info>
(
	instruction_type::type_sltu,
	instruction_format::format_r,
	43,
	order_rd_rs_rt
	);

static std::shared_ptr<instruction_info> info_j = std::make_shared<instruction_info>
(
	instruction_type::type_j,
	instruction_format::format_j,
	2,
	order_imm
	);


static std::shared_ptr<instruction_info> info_jal = std::make_shared<instruction_info>
(
	instruction_type::type_jal,
	instruction_format::format_j,
	3,
	order_imm
	);

static std::shared_ptr<instruction_info> info_beq = std::make_shared<instruction_info>
(
	instruction_type::type_beq,
	instruction_format::format_i,
	4,
	order_rs_rt_imm
	);

static std::shared_ptr<instruction_info> info_bne = std::make_shared<instruction_info>
(
	instruction_type::type_bne,
	instruction_format::format_i,
	5,
	order_rs_rt_imm
	);

static std::shared_ptr<instruction_info> info_blez = std::make_shared<instruction_info>
(
	instruction_type::type_blez,
	instruction_format::format_i,
	6,
	order_rs_imm
	);

static std::shared_ptr<instruction_info> info_bgtz = std::make_shared<instruction_info>
(
	instruction_type::type_bgtz,
	instruction_format::format_i,
	7,
	order_rs_imm
	);

static std::shared_ptr<instruction_info> info_addi = std::make_shared<instruction_info>
(
	instruction_type::type_addi,
	instruction_format::format_i,
	8,
	order_rt_rs_imm
	);

static std::shared_ptr<instruction_info> info_addiu = std::make_shared<instruction_info>
(
	instruction_type::type_addiu,
	instruction_format::format_i,
	9,
	order_rt_rs_imm
	);
static std::shared_ptr<instruction_info> info_slti = std::make_shared<instruction_info>
(
	instruction_type::type_slti,
	instruction_format::format_i,
	10,
	order_rt_rs_imm
	);

static std::shared_ptr<instruction_info> info_sltiu = std::make_shared<instruction_info>
(
	instruction_type::type_sltiu,
	instruction_format::format_i,
	11,
	order_rt_rs_imm
	);

static std::shared_ptr<instruction_info> info_andi = std::make_shared<instruction_info>
(
	instruction_type::type_andi,
	instruction_format::format_i,
	12,
	order_rt_rs_imm
	);

static std::shared_ptr<instruction_info> info_ori = std::make_shared<instruction_info>
(
	instruction_type::type_ori,
	instruction_format::format_i,
	13,
	order_rt_rs_imm
	);

static std::shared_ptr<instruction_info> info_xori = std::make_shared<instruction_info>
(
	instruction_type::type_xori,
	instruction_format::format_i,
	14,
	order_rt_rs_imm
	);

static std::shared_ptr<instruction_info> info_lui = std::make_shared<instruction_info>
(
	instruction_type::type_lui,
	instruction_format::format_i,
	15,
	order_rt_imm
	);

static std::shared_ptr<instruction_info> info_lb = std::make_shared<instruction_info>
(
	instruction_type::type_lb,
	instruction_format::format_i,
	32,
	order_rt_imm_rs
	);

static std::shared_ptr<instruction_info> info_lh = std::make_shared<instruction_info>
(
	instruction_type::type_lh,
	instruction_format::format_i,
	33,
	order_rt_imm_rs
	);

static std::shared_ptr<instruction_info> info_lw = std::make_shared<instruction_info>
(
	instruction_type::type_lw,
	instruction_format::format_i,
	34,
	order_rt_imm_rs
	);

static std::shared_ptr<instruction_info> info_lbu = std::make_shared<instruction_info>
(
	instruction_type::type_lbu,
	instruction_format::format_i,
	36,
	order_rt_imm_rs
	);

static std::shared_ptr<instruction_info> info_lhu = std::make_shared<instruction_info>
(
	instruction_type::type_lhu,
	instruction_format::format_i,
	37,
	order_rt_imm_rs
	);

static std::shared_ptr<instruction_info> info_sb = std::make_shared<instruction_info>
(
	instruction_type::type_sb,
	instruction_format::format_i,
	40,
	order_rt_imm_rs
	);

static std::shared_ptr<instruction_info> info_sh = std::make_shared<instruction_info>
(
	instruction_type::type_sh,
	instruction_format::format_i,
	41,
	order_rt_imm_rs
	);

static std::shared_ptr<instruction_info> info_sw = std::make_shared<instruction_info>
(
	instruction_type::type_sw,
	instruction_format::format_i,
	43,
	order_rt_imm_rs
	);

/*
 * key = instruction function field
*/
std::map<std::uint8_t, std::shared_ptr<instruction_info>> r_instruction_info = {

	{info_sll->opcode_function, info_sll},
	{info_srl->opcode_function, info_srl},
	{info_sra->opcode_function, info_sra},
	{info_sllv->opcode_function, info_sllv},
	{info_srlv->opcode_function, info_srlv},
	{info_srav->opcode_function, info_srav},
	{info_jr->opcode_function, info_jr},
	{info_jalr->opcode_function, info_jalr},
	{info_syscall->opcode_function, info_syscall},
	{info_mfhi->opcode_function, info_mfhi},
	{info_mthi->opcode_function, info_mthi},
	{info_mflo->opcode_function, info_mflo},
	{info_mtlo->opcode_function, info_mtlo},
	{info_mult->opcode_function, info_mult},
	{info_multu->opcode_function, info_multu},
	{info_div->opcode_function, info_div},
	{info_divu->opcode_function, info_divu},
	{info_add->opcode_function, info_add},
	{info_addu->opcode_function, info_addu},
	{info_sub->opcode_function, info_sub},
	{info_subu->opcode_function, info_subu},
	{info_and->opcode_function, info_and},
	{info_or->opcode_function, info_or},
	{info_xor->opcode_function, info_xor},
	{info_nor->opcode_function, info_nor},
	{info_slt->opcode_function, info_slt},
	{info_sltu->opcode_function, info_sltu}
};


/*
 * key = instruction opcode field
*/
std::map<std::uint8_t, std::shared_ptr<instruction_info>> j_instruction_info = {

	{info_j->opcode_function, info_j},
	{info_jal->opcode_function, info_jal}
};

/*
 * key = instruction opcode field
*/
std::map<std::uint8_t, std::shared_ptr<instruction_info>> i_instruction_info = {

	{info_beq->opcode_function, info_beq},
	{info_bne->opcode_function, info_bne},
	{info_blez->opcode_function, info_blez},
	{info_bgtz->opcode_function, info_bgtz},
	{info_addi->opcode_function, info_addi},
	{info_addiu->opcode_function, info_addiu},
	{info_slti->opcode_function, info_slti},
	{info_sltiu->opcode_function, info_sltiu},
	{info_andi->opcode_function, info_andi},
	{info_ori->opcode_function, info_ori},
	{info_xori->opcode_function, info_xori},
	{info_lui->opcode_function, info_lui},
	{info_lb->opcode_function, info_lb},
	{info_lh->opcode_function, info_lh},
	{info_lw->opcode_function, info_lw},
	{info_lbu->opcode_function, info_lbu},
	{info_lhu->opcode_function, info_lhu},
	{info_sb->opcode_function, info_sb},
	{info_sh->opcode_function, info_sh},
	{info_sw->opcode_function, info_sw},
};

inline std::shared_ptr<instruction_info> get_instruction_info(const std::uint8_t opcode, const std::uint8_t function)
{

	if(opcode == 0)
	{
		if (r_instruction_info.count(function))
			return r_instruction_info[function];

		return nullptr;
	}
	else
	{
		if (j_instruction_info.count(opcode))
			return j_instruction_info[opcode];
		
		if (i_instruction_info.count(opcode))
			return i_instruction_info[opcode];
		
		return nullptr;
	}

	return nullptr;
}