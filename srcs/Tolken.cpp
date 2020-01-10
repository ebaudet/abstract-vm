/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tolken.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 10:22:38 by ebaudet           #+#    #+#             */
/*   Updated: 2020/01/10 12:37:50 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Tolken.hpp"

std::vector<std::string> Tolken::token_name = {
	"Unknown", "InstructionNoArg", "InstructionArg", "Type", "OpenPar", "ClosePar", "NValue", "ZValue"
};

Tolken::Tolken( eTokenType type, std::string value, size_t pos )
:_type( type ), _value( value ), _pos( pos ) {
}

Tolken::Tolken( Tolken const &src ) {
	*this = src;
}

Tolken::~Tolken() {
}

Tolken &Tolken::operator=( Tolken const &rhs ) {
	if (this != &rhs) {
		_type = rhs._type;
		_value = rhs._value;
		_pos = rhs._pos;
	}
	return *this;
}

// Accessors
eTokenType Tolken::GetType() const { return this->_type; }
std::string Tolken::GetValue() const { return _value; }
size_t Tolken::GetPos() const { return _pos; }
void Tolken::SetType( eTokenType type ) { _type = type; }
void Tolken::SetValue( std::string value ) { _value = value; }
void Tolken::SetPos( size_t pos ) { _pos = pos; }

std::ostream &	operator<<( std::ostream & os, const Tolken &tolken ) {
	os << "{type:" << Tolken::token_name[tolken.GetType()] << ", value: \""
	<< tolken.GetValue() << "\", pos: " << tolken.GetPos() << "}";
	return (os);
}
