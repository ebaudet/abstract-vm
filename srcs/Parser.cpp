/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 19:44:22 by ebaudet           #+#    #+#             */
/*   Updated: 2020/01/13 21:27:55 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"
#include <iostream>
#include "Lexer.hpp"

// -- Public members -----------------------------------------------------------



// -- Constructors -------------------------------------------------------------

Parser::Parser() {
	_openBracket = true;
	_typeNumber = eTokenType::Unknown;
	_nbParams = 0;
}

Parser::Parser(Parser const &src) {
	*this = src;
}

Parser::~Parser() {
}

// -- Operators ----------------------------------------------------------------

Parser &Parser::operator=(Parser const &rhs) {
	if (this != &rhs)
		;
	return *this;
}

// -- Methods ------------------------------------------------------------------

void Parser::parseType(std::vector<Token> tokenList, std::vector<Token>::iterator &it)
{
	if (it == tokenList.end() || it->GetType() != eTokenType::Type)
		throw ParserException("Type expected.", *it);
	++it;
}

void Parser::parseNumber(std::vector<Token> tokenList, std::vector<Token>::iterator &it)
{
	if (it == tokenList.end())
		throw ParserException("Number expected.", *it);
}

void Parser::parseBracket(std::vector<Token> tokenList, std::vector<Token>::iterator &it)
{
	parseSpace(tokenList, it, false);

	if (_openBracket) {
		if (it->GetType() != eTokenType::OpenPar)
			throw ParserException("Open Bracket expected.", *it);
	} else {
		if (it->GetType() != eTokenType::ClosePar)
			throw ParserException("Close Bracket expected.", *it);
	}
	_openBracket = !_openBracket;
}

void Parser::parseValue(std::vector<Token> tokenList, std::vector<Token>::iterator &it)
{
	parseSpace(tokenList, it, true);
	parseType(tokenList, it);

	parseBracket(tokenList, it);
	parseNumber(tokenList, it);
	parseBracket(tokenList, it);

	if (it->GetType() == eTokenType::Comment)
		throw ParserException("Arguments expected.", *it);
}

void Parser::parseSpace(std::vector<Token> tokenList, std::vector<Token>::iterator &it, bool expected)
{
	if (it == tokenList.end()) {
		if (expected)
			throw ParserException("Space expected.", *it);
		return ;
	}

	if (it->GetType() == eTokenType::Space) {
		++it;
	}
	else if (expected)
		throw ParserException("Space expected.", *it);
}

void Parser::parseToken(std::vector<Token> tokenList) {
	int params = 0;
	std::vector<Token>::iterator it = tokenList.begin();

	parseSpace(tokenList, it, false);

	if (it->GetType() == eTokenType::Comment)
		return;
	if (it->GetType() != eTokenType::InstructionName) {
		throw ParserException("Instruction expected.", *it);
	} else {
		std::map<std::string, int>::iterator it_inst;
		it_inst = Lexer::instrArg.find(it->GetValue());
		params = it_inst->second;
		++it;
		if (params > 0) {
			parseValue(tokenList, it);
		}
		parseSpace(tokenList, it, false);
		if (it->GetType() == eTokenType::Comment) {
			++it;
		}
	}
	if (it != tokenList.end())
		throw ParserException("No more argument exected.", *it);

	// if works, all good params have to be save in the private members in order
	// to launch them.
	// need :
	// - function (fonction's pointer of Instruction's class)
	// - value type (eOperandType)
	// - value value (string)
}

// -- Exceptions errors --------------------------------------------------------

Parser::ParserException::ParserException()
: std::runtime_error( "Parser Exception" ) {}

Parser::ParserException::ParserException( const char* what_arg )
: std::runtime_error( std::string(std::string("ParserError: ") + what_arg).c_str() ) {}

// >  int32
//    ^
// ParserError:2:1: Instruction expected.
Parser::ParserException::ParserException( const char* what_arg, Token token )
: std::runtime_error( std::string(
		std::string(token.GetPos() + 2, ' ')
		+ "^\nParserError:" + std::to_string(token.GetLine()) + ":"
		+ std::to_string(token.GetPos())+ " " + what_arg
		+ token.toString()
	).c_str() ) {}
