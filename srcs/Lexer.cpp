/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 19:36:12 by ebaudet           #+#    #+#             */
/*   Updated: 2020/01/13 21:19:26 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Lexer.hpp"
#include "Parser.hpp"
#include <iostream>
#include <regex>
#include <sstream>
#include <fstream>

void	p_error(std::string error) {
	std::cerr << "\x1B[31m" << error << "\x1B[0m" << std::endl;
}

// -- Public members -----------------------------------------------------------

std::map<std::string, int>	Lexer::instrArg = {
	{"push", 1},
	{"pop", 0},
	{"dump", 0},
	{"assert", 1},
	{"add", 0},
	{"sub", 0},
	{"mul", 0},
	{"div", 0},
	{"mod", 0},
	{"print", 0},
	{"exit", 0}
};

std::map<std::string, eTokenType>	Lexer::typeArg = {
	{"int8", eTokenType::NVal},
	{"int16", eTokenType::NVal},
	{"int32", eTokenType::NVal},
	{"float", eTokenType::ZVal},
	{"double", eTokenType::ZVal}
};

// std::vector<std::string> Lexer::instructionStr = {
// 	"push" ,"pop", "dump", "assert", "add", "sub", "mul", "div", "mod", "print",
// 	"exit"
// };

// std::vector<int> Lexer::instructionArg {
// 	1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0
// };

// std::vector<std::string> Lexer::operandTypeStr = {
// 	"int8", "int16", "int32", "float", "double"
// };

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
	if (this != &rhs)
		;
	return *this;
}

// -- Exceptions errors --------------------------------------------------------

Lexer::LexerException::LexerException(const char* what_arg)
: std::runtime_error( what_arg ) {}

Lexer::LexerException::LexerException()
: std::runtime_error( "Lexer Exception" ) {}

// -- Methods ------------------------------------------------------------------

void Lexer::readFromFile(char *file, Instruction &instruction) {
	(void)instruction;
	(void)file;
	// TODO;
}

void Lexer::readFromStdin(Instruction &instruction) {
	Parser parser;
	std::string line;

	std::cout << "> ";
	for (int line_row = 1; std::getline(std::cin, line); line_row++) {
		try {
			listToken.erase( listToken.begin(), listToken.end() );
			lexLine(line, line_row);
			std::cout << "listVector " << listToken << std::endl;

			parser.parseToken(listToken);

		} catch (std::exception &e) {
			std::cout << "\x1B[34m" << "$ " << line << "\x1B[0m" << std::endl;
			p_error(e.what());
			if (!instruction.continue_error)
				return ;
		}
		std::cout << "> ";
	}
}

/**
 * Create the parsing Regex in the same order that eTokenType (in Token.hpp).
 */
std::string Lexer::parsingRegex() {
	std::string comment = "(;.*)";
	std::string open_par = "(\\()";
	std::string close_par = "(\\))";
	std::string instruction = "(";
	for (auto &&s : Lexer::instrArg)
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

void Lexer::lexLine(std::string line, int line_row) {
	std::string regexStr = parsingRegex();
	std::regex r(regexStr);
	std::smatch m;
	std::string::const_iterator it = line.cbegin();
	size_t pos = 0;
	int found;

	while ((it != line.cend())
		&& std::regex_search(it, line.cend(), m, r) == true) {
		found = 0;
		for (unsigned long group_nb = 1; group_nb < m.size(); group_nb++) {
			if (!m[group_nb].str().empty()) {
				Token newToken = Token( static_cast<eTokenType>(group_nb),
					m.str(0), pos, line_row );
				listToken.push_back( newToken );
				it += m.length();
				pos += m.length();
				found++;
			}
		}
		if (!found) {
			std::ostringstream sstr;
			sstr << std::string(pos + 2, ' ') << "^" << std::endl;
			sstr << "LexerError:" << line_row << ":" << pos << " error:"
				<< &line[it - line.cbegin()];
			throw Lexer::LexerException(sstr.str().c_str());
		}
	}
}
