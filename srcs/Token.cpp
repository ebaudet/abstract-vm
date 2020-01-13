/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 10:22:38 by ebaudet           #+#    #+#             */
/*   Updated: 2020/01/13 21:01:08 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Token.hpp"
#include <sstream>

// -- Public members -----------------------------------------------------------

std::vector<std::string> Token::token_name = {
	"Unknown", "Comment", "OpenPar", "ClosePar", "InstructionName", "Type",
	"ZVal", "NVal", "Space"
};

// -- Constructors -------------------------------------------------------------

Token::Token() {
}

Token::Token( eTokenType type, std::string value, size_t pos , size_t line )
:_type( type ), _value( value ), _pos( pos ), _line( line ){
}

Token::Token( Token const &src ) {
	*this = src;
}

Token::~Token() {
}

// -- Operators ----------------------------------------------------------------

Token &Token::operator=( Token const &rhs ) {
	if (this != &rhs) {
		_type = rhs.GetType();
		_value = rhs.GetValue();
		_pos = rhs.GetPos();
		_line = rhs.GetLine();
	}
	return *this;
}

std::ostream &	operator<<( std::ostream & os, const Token &tolken ) {
	os << "{type:" << Token::token_name[tolken.GetType()] << ", value: \""
	<< tolken.GetValue() << "\", pos: " << tolken.GetPos() << "}";
	return (os);
}

// -- Accessors ----------------------------------------------------------------

eTokenType Token::GetType() const { return this->_type; }
std::string Token::GetValue() const { return _value; }
size_t Token::GetPos() const { return _pos; }
size_t Token::GetLine() const { return _line; }
size_t Token::GetLength() const { return _value.length(); }
void Token::SetType( eTokenType type ) { _type = type; }
void Token::SetValue( std::string value ) { _value = value; }
void Token::SetPos( size_t pos ) { _pos = pos; }
void Token::SetLine( size_t line ) { _line = line; }

// -- Method -------------------------------------------------------------------

std::string Token::toString() {
	std::ostringstream sstr;
	sstr << *this;
	return sstr.str();
}
