/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 19:44:15 by ebaudet           #+#    #+#             */
/*   Updated: 2020/01/13 21:28:42 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP_
#define PARSER_HPP_

#include <vector>
#include <sstream>
#include "Token.hpp"

class Parser {
	public:
		static std::vector<int> instructionNbArg;
		Parser();
		Parser(Parser const &src);
		virtual ~Parser();

		Parser &operator=(Parser const &rhs);

		void parseToken( std::vector<Token> tokenList );
		void parseValue( std::vector<Token> tokenList, std::vector<Token>::iterator &it );
		void parseSpace( std::vector<Token> tokenList, std::vector<Token>::iterator &it, bool expected );
		void parseType( std::vector<Token> tokenList, std::vector<Token>::iterator &it );
		void parseBracket( std::vector<Token> tokenList, std::vector<Token>::iterator &it );
		void parseNumber( std::vector<Token> tokenList, std::vector<Token>::iterator &it );

		// todo : check inherit
		class ParserException : public std::runtime_error {
		public:
			ParserException();
			ParserException( const char* what_arg );
			ParserException( const char* what_arg, Token token );
		};

	private:
		bool _openBracket;
		eTokenType _typeNumber;
		int _nbParams;
};

#endif  // PARSER_HPP_
