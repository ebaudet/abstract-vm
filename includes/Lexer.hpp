/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 19:27:25 by ebaudet           #+#    #+#             */
/*   Updated: 2020/03/13 19:06:29 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_HPP_
#define LEXER_HPP_

/*
**
BNF (Backus–Naur form) grammar :

S := INSTR [SEP INSTR]* #

INSTR :=
	push VALUE
	| pop
	| dump
	| assert VALUE
	| add
	| sub
	| mul
	| div
	| mod
	| print
	| exit

VALUE :=
	int8(N)
	| int16(N)
	| int32(N)
	| float(Z)
	| double(Z)

N := [-]?[0..9]+

Z := [-]?[0..9]+.[0..9]+

SEP := '\n'+
*/

#include "Instruction.hpp"
#include "IOperand.hpp"
#include "Token.hpp"
#include <vector>
#include <map>

class Lexer {
	public:
		struct TypeArg
		{
			eTokenType		tokenType;
			eOperandType	operandType;
		};
		// public Members
		static std::map<std::string, TypeArg>	typeArg;
		std::vector<Token>						listToken;

		// Constructors
		Lexer();
		Lexer(Lexer const &src);
		virtual ~Lexer();

		// Operators
		Lexer &operator=(Lexer const &rhs);

		// Methods
		void		lexLine(std::string line, int line_row);
		std::string	createRegex();

		class LexerException : public std::runtime_error {
		public:
			LexerException();
			LexerException(const char* what_arg);
		};
};

template <class T>
std::ostream &	operator<<(std::ostream &os, std::vector<T> const &vector_list)
{
	os << "{" << std::endl;
	for (auto &&i : vector_list)
		os << "\t" << i << "," << std::endl;
	os << "}" << std::endl;
	return (os);
};

#endif  // LEXER_HPP_
