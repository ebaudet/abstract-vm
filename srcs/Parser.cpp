/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 19:44:22 by ebaudet           #+#    #+#             */
/*   Updated: 2020/01/14 16:50:35 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"
#include <iostream>
#include "Lexer.hpp"
#include "Color.hpp"

// -- Constructors -------------------------------------------------------------

Parser::Parser( std::string line ) : _line( line ) {
	_openBracket = true;
	_typeNumber = eTokenType::Unknown;
	_val = "";
	_nbParams = 0;
	_pos = 0;
	_lineRow = 0;
	_tokenList = NULL;
}

Parser::Parser(Parser const &src) {
	_tokenList = src._tokenList;
	*this = src;
}

Parser::~Parser() {
}

// -- Operators ----------------------------------------------------------------

Parser &Parser::operator=(Parser const &rhs) {
	if (this != &rhs) {
		_openBracket = rhs._openBracket;
		_typeNumber = rhs._typeNumber;
		_nbParams = rhs._nbParams;
		_pos = rhs._pos;
		_lineRow = rhs._lineRow;
		_tokenList = rhs._tokenList;
		_line = rhs._line;
	}
	return *this;
}

std::ostream &	operator<<( std::ostream & os, const Parser &parser ) {
	os << "{type:" << Token::token_name[parser.GetTypeNumber()]
	<< ", nbParams: \"" << parser.GetNbParams() << "\", pos: "
	<< parser.GetPos() << "\", line: " << parser.GetLineRow() << "}";
	return (os);
}

// -- Accessors ----------------------------------------------------------------

eTokenType Parser::GetTypeNumber() const {
	return _typeNumber;
}
int Parser::GetNbParams() const {
	return _nbParams;
}
size_t Parser::GetPos() const {
	return _pos;
}
size_t Parser::GetLineRow() const {
	return _lineRow;
}

// -- Methods ------------------------------------------------------------------

void Parser::parseType(std::vector<Token>::iterator &it)
{
	if ( it == _tokenList->end() )
		throw ParserException("Type expected.", *this);

	if ( it->GetType() != eTokenType::Type )
		throw ParserException("Type expected.", *it, _line);

	std::map<std::string, eTokenType>::iterator it_typeArg;
	it_typeArg = Lexer::typeArg.find(it->GetValue());
	_typeNumber = it_typeArg->second;

	iteratorInc(it);
}

void Parser::parseNumber(std::vector<Token>::iterator &it)
{
	parseSpace(it);

	if (it == _tokenList->end())
		throw ParserException("Number expected.", *this);

	if (it->GetType() != _typeNumber) {
		std::ostringstream sstr;
		sstr << "Type " << Token::token_name[_typeNumber] << " expected.";
		throw ParserException(sstr.str().c_str(), *it, _line);
	}

	_val = it->GetValue();

	iteratorInc(it);
}

void Parser::parseBracket(std::vector<Token>::iterator &it)
{
	parseSpace(it);
	if (it == _tokenList->end())
		throw ParserException("Bracket expected.", *this);

	if (_openBracket) {
		if (it->GetType() != eTokenType::OpenPar)
			throw ParserException("Open Bracket expected.", *it, _line);
	} else {
		if (it->GetType() != eTokenType::ClosePar)
			throw ParserException("Close Bracket expected.", *it, _line);
	}

	_openBracket = !_openBracket;

	iteratorInc(it);
}

void Parser::parseValue(std::vector<Token>::iterator &it)
{
	if (it == _tokenList->end())
		throw ParserException("Value expected.", *this);

	if (it->GetType() == eTokenType::Comment)
		throw ParserException("Arguments expected.", *it, _line);

	parseSpace(it, true);
	parseType(it);
	parseBracket(it);
	parseNumber(it);
	parseBracket(it);
}

void Parser::parseInstruction(std::vector<Token>::iterator &it)
{
	if (it == _tokenList->end())
		return ;
	if (it->GetType() != eTokenType::InstructionName)
		throw ParserException("Instruction expected.", *it, _line);

	std::map<std::string, int>::iterator it_inst;
	it_inst = Lexer::instrArg.find(it->GetValue());
	_nbParams = it_inst->second;

	iteratorInc(it);
}

void Parser::parseSpace(std::vector<Token>::iterator &it, bool expected)
{
	if (it == _tokenList->end()) {
		if (expected)
			throw ParserException("Space expected.", *this);
		return ;
	}

	if (it->GetType() == eTokenType::Space) {
		iteratorInc(it);
	}
	else if (expected)
		throw ParserException("Space expected.", *it, _line);
}

void Parser::parseToken(std::vector<Token> &tokenList) {
	_tokenList = &tokenList;
	std::vector<Token>::iterator it = tokenList.begin();

	// std::cout << "Test: " << tokenList << std::endl;
	// std::cout << "Parser : " << *this << std::endl;
	// std::cout << "<parseToken>" << std::endl;

	parseSpace(it);
	if (it->GetType() == eTokenType::Comment)
		return ;
	parseInstruction(it);
	if (_nbParams > 0) {
		parseValue(it);
	}
	parseSpace(it);
	if (it->GetType() == eTokenType::Comment) {
		iteratorInc(it);
	}

	if (it != tokenList.end())
		throw ParserException("No argument exected.", *it, _line);

	// if works, all good params have to be save in the private members in order
	// to launch them.
	// need :
	// - function (fonction's pointer of Instruction's class)
	// - value type (eOperandType)
	// - value value (string)
}

int		Parser::iteratorInc( std::vector<Token>::iterator &it, bool expected )
{
	if (it == _tokenList->end())
		throw ParserException("Unexpected end.", *this);

	_pos += it->GetLength();
	++it;
	if (it == _tokenList->end()) {
		if (expected)
			throw ParserException("Unexpected end.", *this);
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

const std::string Parser::getMessageError( const char *what_arg ) {
	std::ostringstream sstr;

	sstr << RED "ParserError:" << _lineRow << ":"
	<< _pos << EOC " " << what_arg << "\n" << _line << "\n"
	<< std::string(_pos, ' ') << GREEN "^" EOC;

	return sstr.str().c_str();
}

// -- Exceptions errors --------------------------------------------------------

Parser::ParserException::ParserException()
: std::runtime_error( "Parser Exception" ) {}

Parser::ParserException::ParserException( const char* what_arg )
: std::runtime_error( std::string(std::string("ParserError: ") + what_arg).c_str() ) {}

// >  int32
//    ^
// ParserError:2:1: Instruction expected.
Parser::ParserException::ParserException( const char* what_arg, Token &token, std::string line )
: std::runtime_error( std::string(
		RED "ParserError:" + std::to_string(token.GetLine()) + ":"
		+ std::to_string(token.GetPos())+ EOC " " + what_arg + "\n" + line + "\n"
		+ std::string(token.GetPos(), ' ') + GREEN "^" EOC
	).c_str() ) {}

// >  int32
//    ^
// ParserError:2:1: Instruction expected.
Parser::ParserException::ParserException( const char* what_arg, Parser &parser )
: std::runtime_error( parser.getMessageError( what_arg ) ) {}

