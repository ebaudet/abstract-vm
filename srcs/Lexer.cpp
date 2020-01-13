/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 19:36:12 by ebaudet           #+#    #+#             */
/*   Updated: 2020/01/13 11:59:49 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Lexer.hpp"
#include <iostream>
#include <regex>
#include <sstream>

void	p_error(std::string error) {
	std::cerr << "\x1B[31m" << error << "\x1B[0m" << std::endl;
}

// -- Public members -----------------------------------------------------------

std::vector<std::string> Lexer::instructionStr = {
	"push" ,"pop", "dump", "assert", "add", "sub", "mul", "div", "mod", "print",
	"exit"
};
std::vector<std::string> Lexer::operandTypeStr = {
	"int8", "int16", "int32", "float", "double"
};

// -- Constructors -------------------------------------------------------------

Lexer::Lexer() {
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
	(void)instruction;
	std::string line;
	std::cout << "> ";
	for (int line_row = 1; std::getline(std::cin, line); line_row++) {
		try {
			parseLine(line, line_row);
		} catch (std::exception &e) {
			p_error(e.what());
		}
		std::cout << "> ";
	}
}
bool	Lexer::createToken(std::string line, int line_row, int i) {
	(void)line;
	(void)line_row;
	(void)i;

	std::string comment = "(?<comment>(;.*))";
	std::string open_par = "(?<open_par>(\\())";
	std::string close_par = "(?<close_par>(\\)))";
	std::string instruction = "(?<instruction>(push|add))";
	std::string type = "(?<type>(int32|float))";
	std::string zval = "(?<zval>([-|\\+]?[[:digit:]]+\\.[[:digit:]]+))";
	std::string nval = "(?<nval>([-|\\+]?[[:digit:]]+))";

	// std::string regexStr =

	return (true);
}

void Lexer::parseLine(std::string line, int line_row) {

	std::cout << "line " << line_row << ": " << line << std::endl;

	std::string comment = "(;.*)";
	std::string open_par = "(\\()";
	std::string close_par = "(\\))";
	std::string instruction = "(";
	for (const std::string &s : Lexer::instructionStr) {
		instruction += s + "|";
	}
	if (instruction.back() == '|') instruction.pop_back();
	instruction += ")";
	// std::cout << "instruction:" << instruction << std::endl;
	std::string type = "(";
		for (const std::string &s : Lexer::operandTypeStr) {
		type += s + "|";
	}
	if (type.back() == '|') type.pop_back();
	type += ")";
	// std::cout << "type:" << type << std::endl;
	std::string zval = "([-|\\+]?[[:digit:]]+\\.[[:digit:]]+)";
	std::string nval = "([-|\\+]?[[:digit:]]+)";
	std::string space = "([^\\S\\r\\n]*)";

	std::string regexStr =	comment
					+ "|" + open_par
					+ "|" + close_par
					+ "|" + instruction
					+ "|" + type
					+ "|" + zval
					+ "|" + nval
					+ "|" + space;

	std::vector<std::string>token_type = {"comment", "open_par", "close_par", "instruction", "type", "zval", "nval", "space"};
	std::regex r(regexStr);
	std::smatch m;

	std::vector<Token> listToken;
	size_t pos = 0;
	std::string::const_iterator it = line.cbegin();
	while ((it != line.cend()) && std::regex_search(it, line.cend(), m, r) == true) {
		// std::cout << "size:" << m.size() << ", position:" << m.position() <<
		// ", length: " << m.length() << ", str0:" << m.str(0) << ", position:" << m.position(1) << std::endl;

		int found = 0;
		for (unsigned long group_nb = 1; group_nb < m.size(); group_nb++) {
			if (!m[group_nb].str().empty()) {
				std::cout << "found: " << Token::token_name[group_nb] << " '"<< m.str(0) << "' pos: " << pos << std::endl;
				Token newToken = Token(static_cast<eTokenType>(group_nb), m.str(0), pos);
				std::cout << newToken << std::endl;
				listToken.push_back(newToken);
				// todo : create new token.
				it += m.length();
				pos += m.length();
				found++;
				// todo : add it to the list of tokens
			}
		}
		if (!found) {
			std::ostringstream sstr;
			sstr << "Lexeror:" << line_row << ":" << pos << " error:" << &line[it - line.cbegin()];
			throw Lexer::LexerException(sstr.str().c_str());
			break;
		}
	}
	std::cout << "listVector {" << std::endl;
	for (auto &&i : listToken) {
		std::cout << "\t" << i << "," << std::endl;
	}
	std::cout << "}" << std::endl;

}

// -- Private members initialisation -------------------------------------------

std::vector<std::string> Lexer::_instructionsName {
	"push",
	"pop",
	"dump",
	"assert",
	"add",
	"sub",
	"mul",
	"div",
	"mod",
	"print",
	"exit"
};

std::vector<std::string> Lexer::_typesName {
	"int8",
	"int16",
	"int32",
	"float",
	"double"
};
