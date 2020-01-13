/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 19:27:25 by ebaudet           #+#    #+#             */
/*   Updated: 2020/01/13 11:37:14 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(LEXER_HPP)
#define LEXER_HPP
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

class Lexer {
	public:
		static std::vector<std::string> instructionStr;
		static std::vector<std::string> operandTypeStr;

		Lexer();
		Lexer(Lexer const &src);
		virtual ~Lexer();

		Lexer &operator=(Lexer const &rhs);

		void	readFromFile(char *file, Instruction &instruction);
		void	readFromStdin(Instruction &instruction);
		void	parseLine(std::string line, int line_row);
		bool	createToken(std::string line, int line_row, int i);

		// todo : check inherit
		class LexerException : public std::runtime_error {
		public:
			LexerException();
			LexerException( const char* what_arg );
		};

	private:
		static std::vector<std::string> _instructionsName;
		static std::vector<std::string> _typesName;
};

#endif // LEXER_HPP
