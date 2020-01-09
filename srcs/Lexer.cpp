/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 19:36:12 by ebaudet           #+#    #+#             */
/*   Updated: 2020/01/09 21:22:30 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Lexer.hpp"

Lexer::Lexer() {
}

Lexer::Lexer(Lexer const &src) {
	*this = src;
}

Lexer::~Lexer() {
}

Lexer &Lexer::operator=(Lexer const &rhs) {
	if (this != &rhs)
		;
	return *this;
}

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
		parseLine(line, line_row);
		std::cout << "> ";
	}
}

void Lexer::parseLine(std::string line, int line_row) {
	std::cout << "line " << line_row << ": " << line << std::endl;
}


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
