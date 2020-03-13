/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 19:44:22 by ebaudet           #+#    #+#             */
/*   Updated: 2020/03/13 20:46:53 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Parser.hpp"
#include "Lexer.hpp"
#include "Color.hpp"

// -- Constructors -------------------------------------------------------------

Parser::Parser(std::string line) : _line(line) {
	_clear();
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

std::ostream &	operator<<(std::ostream & os, const Parser &parser) {
	os << "{type:" << Token::token_name[parser.getTypeNumber()]
	<< ", nbParams: \"" << parser.getNbParams() << "\", pos: "
	<< parser.getPos() << "\", line: " << parser.getLineRow() << "}";
	return (os);
}

// -- Accessors ----------------------------------------------------------------

eTokenType		Parser::getTypeNumber() const { return _typeNumber; }
int				Parser::getNbParams() const { return _nbParams; }
size_t			Parser::getPos() const { return _pos; }
size_t			Parser::getLineRow() const { return _lineRow; }
std::string		Parser::getLine() const { return _line; }
std::string		Parser::getVal() const { return _val; }
eOperandType	Parser::getOperantType() const { return _operandType; }

// -- Methods ------------------------------------------------------------------

/**
 * @brief Parse line. Throw a ParserException if not passed.
 *
 * @param token_list
 * @param line
 * @param line_row
 */
void Parser::parseToken(std::vector<Token> &token_list, std::string line,
int line_row)
{
	_tokenList = &token_list;
	std::vector<Token>::iterator it = _tokenList->begin();
	_line = line;
	_lineRow = line_row;

	if (_tokenList->size() == 0)
		return;

	_parseSpace(it);
	_parseComment(it);
	_parseInstruction(it);
	if (_nbParams > 0) {
		_parseValue(it);
	}
	_parseSpace(it);
	_parseComment(it);
	if (it != _tokenList->end())
		throw ParserException("No argument expected.", *it, _line);
}

// -- Private Methods ----------------------------------------------------------

/**
 * @brief Clear all members of Parser.
 */
void Parser::_clear() {
	_openBracket = true;
	_typeNumber = eTokenType::Unknown;
	_val = "";
	_nbParams = 0;
	instructionFuncPtr = NULL;
	_operandType = eOperandType::Int8;
	_lineRow = 0;
	_pos = 0;
	_tokenList = NULL;
	_line = "";
}

void Parser::_parseType(std::vector<Token>::iterator &it)
{
	if (it == _tokenList->end())
		throw ParserException("Argument expected.", *this);

	if (it->GetType() == eTokenType::Comment)
		throw ParserException("Argument expected.", *it, _line);
	if (it->GetType() != eTokenType::Type)
		throw ParserException("Type expected.", *it, _line);

	std::map<std::string, Lexer::TypeArg>::iterator it_typeArg;
	it_typeArg = Lexer::typeArg.find(it->GetValue());
	_typeNumber = it_typeArg->second.tokenType;
	_operandType = it_typeArg->second.operandType;

	_iteratorInc(it);
}

void Parser::_parseNumber(std::vector<Token>::iterator &it)
{
	_parseSpace(it);

	if (it == _tokenList->end())
		throw ParserException("Number expected.", *this);

	if (it->GetType() != _typeNumber) {
		std::ostringstream sstr;
		sstr << "Type " << Token::token_name[_typeNumber] << " expected.";
		throw ParserException(sstr.str().c_str(), *it, _line);
	}

	_val = it->GetValue();

	_iteratorInc(it);
}

void Parser::_parseBracket(std::vector<Token>::iterator &it)
{
	_parseSpace(it);
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

	_iteratorInc(it);
}

void Parser::_parseValue(std::vector<Token>::iterator &it)
{
	if (it == _tokenList->end())
		throw ParserException("Argument expected.", *this);

	if (it->GetType() == eTokenType::Comment)
		throw ParserException("Argument expected.", *it, _line);

	_parseSpace(it, true);
	_parseType(it);
	_parseBracket(it);
	_parseNumber(it);
	_parseBracket(it);
}

void Parser::_parseInstruction(std::vector<Token>::iterator &it)
{
	if (it == _tokenList->end())
		return ;
	if (it->GetType() != eTokenType::InstructionName)
		throw ParserException("Instruction expected.", *it, _line);

	std::map<std::string, Instruction::InstructionArg>::iterator it_inst;
	it_inst = Instruction::instrArgs.find(it->GetValue());
	_nbParams = it_inst->second.nbArg;
	instructionFuncPtr = it_inst->second.instruction;

	_iteratorInc(it);
}

void Parser::_parseSpace(std::vector<Token>::iterator &it, bool expected)
{
	if (it == _tokenList->end()) {
		if (expected)
			throw ParserException("Space expected.", *this);
		return ;
	}

	if (it->GetType() == eTokenType::Space) {
		_iteratorInc(it);
	}
	else if (expected)
		throw ParserException("Space expected.", *it, _line);
}

bool	Parser::_parseComment(std::vector<Token>::iterator &it) {
	if (it == _tokenList->end()) {
		return false;
	}

	if (it->GetType() == eTokenType::Comment) {
		_iteratorInc(it);
		return true;
	}
	return false;
}

int		Parser::_iteratorInc(std::vector<Token>::iterator &it, bool expected)
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

const std::string Parser::_getMessageError(const char *what_arg) {
	std::ostringstream sstr;

	sstr << RED "ParserError:" << _lineRow << ":"
	<< _pos << ":" EOC " " << what_arg << "\n" << _line << "\n"
	<< std::string(_pos, ' ') << GREEN "^" EOC;

	return sstr.str().c_str();
}

// -- Exceptions errors --------------------------------------------------------

Parser::ParserException::ParserException()
: std::runtime_error("Parser Exception") {}

Parser::ParserException::ParserException(const char* what_arg)
: std::runtime_error(std::string(std::string("ParserError: ") + what_arg).c_str()) {}

// ParserError:5:10: Type NVal expected.
// push int8(127.5)
//           ^
Parser::ParserException::ParserException(const char* what_arg, Token &token, std::string line)
: std::runtime_error(std::string(
		RED "ParserError:" + std::to_string(token.GetLine()) + ":"
		+ std::to_string(token.GetPos())+ ":" EOC " " + what_arg + "\n" + line
		+ "\n" + std::string(token.GetPos(), ' ') + GREEN "^" EOC
	).c_str()) {}

// ParserError:5:10: Type NVal expected.
// push int8(127.5)
//           ^
Parser::ParserException::ParserException(const char* what_arg, Parser &parser)
: std::runtime_error(parser._getMessageError(what_arg)) {}
