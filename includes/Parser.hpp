/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 19:44:15 by ebaudet           #+#    #+#             */
/*   Updated: 2020/03/13 20:35:15 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP_
#define PARSER_HPP_

#include <vector>
#include <sstream>
#include "Token.hpp"
#include "Instruction.hpp"

class Parser {
	public:
		// Members
		int (Instruction::*instructionFuncPtr)(const IOperand *);

		// Constructors
		Parser(std::string line);
		Parser(Parser const &src);
		virtual ~Parser();

		// Operators
		Parser &operator=(Parser const &rhs);
		friend std::ostream& operator<<(std::ostream& os, const Token& tolken);

		// Methods
		void	parseToken(std::vector<Token> &token_list, std::string line, int line_row);

		// Accessors
		eTokenType		getTypeNumber() const;
		int				getNbParams() const;
		size_t			getPos() const;
		size_t			getLineRow() const;
		std::string		getLine() const;
		std::string		getVal() const;
		eOperandType	getOperantType() const;

		class ParserException : public std::runtime_error {
		public:
			ParserException();
			ParserException(const char* what_arg);
			ParserException(const char* what_arg, Token &token, std::string line);
			ParserException(const char* what_arg, Parser &parser);
		};

	private:
		// Members
		bool				_openBracket;
		eTokenType			_typeNumber;
		size_t				_pos;
		std::vector<Token>*	_tokenList;
		size_t				_lineRow;
		std::string			_line;
		std::string			_val;
		eOperandType		_operandType;
		int					_nbParams;

		// Methods
		void	_clear();
		void	_parseInstruction(std::vector<Token>::iterator &it);
		void	_parseValue(std::vector<Token>::iterator &it);
		void	_parseSpace(std::vector<Token>::iterator &it, bool expected = false);
		void	_parseType(std::vector<Token>::iterator &it);
		void	_parseBracket(std::vector<Token>::iterator &it);
		void	_parseNumber(std::vector<Token>::iterator &it);
		bool	_parseComment(std::vector<Token>::iterator &it);
		int		_iteratorInc(std::vector<Token>::iterator &it, bool expected = false);
		const std::string	_getMessageError(const char *what_arg);
};

#endif  // PARSER_HPP_
