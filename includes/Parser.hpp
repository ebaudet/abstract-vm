/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 19:44:15 by ebaudet           #+#    #+#             */
/*   Updated: 2020/01/14 19:58:15 by ebaudet          ###   ########.fr       */
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
		// Constructors
		Parser( std::string line );
		Parser( Parser const &src );
		virtual ~Parser();

		// Operators
		Parser &operator=( Parser const &rhs );
		friend std::ostream& operator<<( std::ostream& os, const Token& tolken );

		// Methods
		void	clear();
		int		iteratorInc( std::vector<Token>::iterator &it, bool expected = false );
		void	parseToken( std::vector<Token> &tokenList, std::string line );
		void	parseInstruction(std::vector<Token>::iterator &it );
		void	parseValue( std::vector<Token>::iterator &it );
		void	parseSpace( std::vector<Token>::iterator &it, bool expected = false );
		void	parseType( std::vector<Token>::iterator &it );
		void	parseBracket( std::vector<Token>::iterator &it );
		void	parseNumber( std::vector<Token>::iterator &it );
		const std::string	getMessageError( const char *what_arg );
		void	execute( Factory &factory, Instruction &instruction );

		// Accessors
		eTokenType	GetTypeNumber() const;
		int			GetNbParams() const;
		size_t		GetPos() const;
		size_t		GetLineRow() const;

		// todo : check inherit
		class ParserException : public std::runtime_error {
		public:
			ParserException();
			ParserException( const char* what_arg );
			ParserException( const char* what_arg, Token &token, std::string line );
			ParserException( const char* what_arg, Parser &parser );
		};

	private:
		// private Members
		bool				_openBracket;
		eTokenType			_typeNumber;
		std::string			_val;
		int					_nbParams;
		void (Instruction::*_instruction)(const IOperand *);
		eOperandType		_operandType;
		size_t				_lineRow;
		size_t				_pos;
		std::vector<Token>*	_tokenList;
		std::string			_line;

};

#endif  // PARSER_HPP_
