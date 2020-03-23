#pragma once
#include <string>
#include <unordered_map>
#include "tokenizer.hpp"

enum class mips_token_type
{
	invalid,
	symbol,
	space,
	comma,
	lparen,
	rparen,
	dollar
};

class mips_token
{
public:
	mips_token(const mips_token_type type, const std::string& text) : type(type), text(text) {}
	
	mips_token_type type;
	std::string		text;
};

const static mips_token token_space = { mips_token_type::space,   " " };
const static mips_token token_comma = { mips_token_type::comma,   "," };
const static mips_token token_lparen = { mips_token_type::lparen, "(" };
const static mips_token token_rparen = { mips_token_type::rparen, ")" };
const static mips_token token_dollar = { mips_token_type::dollar, "$" };

using mips_token_vector = token_vector<mips_token>;

static inline mips_token_vector tokens = {
	token_space, token_comma, token_lparen, token_rparen, token_dollar
};



inline mips_token_vector mips_tokenize(const std::string& raw)
{
	return tokenize<mips_token_type, mips_token>(raw, tokens, { mips_token_type::space });
}
