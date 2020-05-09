/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 19:36:12 by ebaudet           #+#    #+#             */
/*   Updated: 2020/05/09 16:49:46 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <regex>
#include <sstream>

#include "Lexer.hpp"
#include "Parser.hpp"
#include "Color.hpp"

void	p_error(std::string error) {
	std::cerr << error << std::endl;
}

// -- Public members -----------------------------------------------------------

std::map<std::string, Lexer::TypeArg>	Lexer::typeArg = {
	{"int8", {eTokenType::NVal, eOperandType::Int8}},
	{"int16", {eTokenType::NVal, eOperandType::Int16}},
	{"int32", {eTokenType::NVal, eOperandType::Int32}},
	{"float", {eTokenType::ZVal, eOperandType::Float}},
	{"double", {eTokenType::ZVal, eOperandType::Double}}
};

// -- Constructors -------------------------------------------------------------

Lexer::Lexer() {
	listToken = std::vector<Token>();
}

Lexer::Lexer(Lexer const &src) {
	*this = src;
}

Lexer::~Lexer() {
}

// -- Operators ----------------------------------------------------------------

Lexer &Lexer::operator=(Lexer const &rhs) {
	if (this != &rhs) {
	}
	return *this;
}

// -- Exceptions errors --------------------------------------------------------

Lexer::LexerException::LexerException(const char* what_arg)
: std::runtime_error(std::string(
	 what_arg
	).c_str()) {}

Lexer::LexerException::LexerException()
: std::runtime_error(RED "Lexer Exception" EOC) {}

// -- Methods ------------------------------------------------------------------

/**
 * @brief Create the parsing Regex in the same order that eTokenType (in
 * Token.hpp).
 *
 * @return std::string
 */
std::string Lexer::createRegex() {
	std::string comment = "(;.*)";
	std::string open_par = "(\\()";
	std::string close_par = "(\\))";
	std::string instruction = "(";
	for (auto &&s : Instruction::instrArgs)
		instruction += s.first + "|";

	if (instruction.back() == '|') instruction.pop_back();
	instruction += ")";
	std::string type = "(";
	for (auto &&s : Lexer::typeArg)
		type += s.first + "|";
	if (type.back() == '|') type.pop_back();
	type += ")";
	std::string zval = "([-|\\+]?[[:digit:]]+\\.[[:digit:]]+)";
	std::string nval = "([-|\\+]?[[:digit:]]+)";
	std::string space = "([^\\S\\r\\n]*)";

	return comment
		+ "|" + open_par
		+ "|" + close_par
		+ "|" + instruction
		+ "|" + type
		+ "|" + zval
		+ "|" + nval
		+ "|" + space;
}

/**
 * @brief Lexer for line. Throw a LexerException error if not passed.
 *
 * @param line
 * @param line_row
 */
void Lexer::lexLine(std::string line, int line_row) {
	std::string regexStr = createRegex();
	std::regex regex(regexStr);
	std::smatch match;
	std::string::const_iterator it = line.cbegin();
	size_t pos = 0;
	int found;

	listToken.erase(listToken.begin(), listToken.end());

	while ((it != line.cend())
		&& std::regex_search(it, line.cend(), match, regex) == true) {
		found = 0;
		for (unsigned long group_nb = 1; group_nb < match.size(); group_nb++) {
			if (!match[group_nb].str().empty()) {
				Token newToken = Token(static_cast<eTokenType>(group_nb),
					match.str(0), pos, line_row);
				listToken.push_back(newToken);
				it += match.length();
				pos += match.length();
				found++;
			}
		}
		if (!found) {
			std::ostringstream sstr;
			sstr << RED "LexerError:" << line_row << ":" << pos << ":" EOC
			" error: unknown expression \"" << &line[it - line.cbegin()]
			<< "\"\n" << line << "\n" << std::string(pos, ' ') << GREEN "^" EOC;
			throw Lexer::LexerException(sstr.str().c_str());
		}
	}
}
