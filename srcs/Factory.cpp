/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Factory.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 20:25:01 by ebaudet           #+#    #+#             */
/*   Updated: 2019/12/11 19:25:09 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Factory.hpp"
#include "Operand.hpp"
#include "Exception.hpp"
#include <sstream>

Factory::Factory() {
}

Factory::Factory( Factory const &src ) {
	*this = src;
}

Factory::~Factory() {
}

Factory &Factory::operator=( Factory const &rhs ) {
	if ( this != &rhs )
		;
	return *this;
}

IOperand const * Factory::createOperand( eOperandType type, std::string const & value ) const {
	// (void *)func;
	(void)type;
	IOperand const *(Factory::*func)( std::string const & value ) const = &Factory::createInt8;
	return (this->*func)( value );
}

/***********************************************
	private functions
************************************************/

IOperand const * Factory::createInt8( std::string const & value ) const {
	std::string convertValue = this->_convertType<int8_t>( value );

	return new Operand<int8_t>( *this, eOperandType::Int8, convertValue );
}

IOperand const * Factory::createInt16( std::string const & value ) const {
	std::string convertValue = this->_convertType<int16_t>( value );

	return new Operand<int16_t>( *this, eOperandType::Int16, convertValue );
}

IOperand const * Factory::createInt32( std::string const & value ) const {
	std::string convertValue = this->_convertType<int32_t>( value );

	return new Operand<int32_t>( *this, eOperandType::Int32, convertValue );
}

IOperand const * Factory::createFloat( std::string const & value ) const {
	std::string convertValue = this->_convertType<float>( value );

	return new Operand<float>( *this, eOperandType::Float, convertValue );
}

IOperand const * Factory::createDouble( std::string const & value ) const {
	std::string convertValue = this->_convertType<double>( value );

	return new Operand<double>( *this, eOperandType::Double, convertValue );
}

template <typename T>
std::string Factory::_convertType( std::string const & value ) const {
	double vald = std::stod( value );

	if ( vald > std::numeric_limits<T>::max() )
			throw Exception::Overflow();
	if ( vald < std::numeric_limits<T>::min() )
		throw Exception::Underflow();

	std::ostringstream strs;
	strs << static_cast<T>( vald );
	return strs.str();
}
