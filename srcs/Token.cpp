/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 10:22:38 by ebaudet           #+#    #+#             */
/*   Updated: 2020/01/13 11:50:14 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Token.hpp"

std::vector<std::string> Token::token_name = {
	"Unknown", "Comment","OpenPar", "ClosePar", "InstructionName", "Type", "ZVal", "NVal", "Space"
};

Token::Token() {
}

Token::Token( eTokenType type, std::string value, size_t pos )
:_type( type ), _value( value ), _pos( pos ) {
}

Token::Token( Token const &src ) {
	*this = src;
}

Token::~Token() {
}

Token &Token::operator=( Token const &rhs ) {
	if (this != &rhs) {
		_type = rhs._type;
		_value = rhs._value;
		_pos = rhs._pos;
	}
	return *this;
}

// Accessors
eTokenType Token::GetType() const { return this->_type; }
std::string Token::GetValue() const { return _value; }
size_t Token::GetPos() const { return _pos; }
void Token::SetType( eTokenType type ) { _type = type; }
void Token::SetValue( std::string value ) { _value = value; }
void Token::SetPos( size_t pos ) { _pos = pos; }

std::ostream &	operator<<( std::ostream & os, const Token &tolken ) {
	os << "{type:" << Token::token_name[tolken.GetType()] << ", value: \""
	<< tolken.GetValue() << "\", pos: " << tolken.GetPos() << "}";
	return (os);
}
