/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Factory.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 20:25:01 by ebaudet           #+#    #+#             */
/*   Updated: 2019/12/10 22:19:24 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Factory.hpp"
#include "Operand.hpp"

Factory::Factory() {
}

Factory::Factory(Factory const &src) {
	*this = src;
}

Factory::~Factory() {
}

Factory &Factory::operator=(Factory const &rhs) {
	if (this != &rhs)
		;
	return *this;
}

IOperand const * Factory::createOperand( eOperandType type, std::string const & value ) const {
	// (void *)func;
	IOperand const *(Factory::*func)(std::string const & value) const = &Factory::createInt8;
	return (this->*func)(value);
}

/***********************************************
	private functions
************************************************/

IOperand const * Factory::createInt8( std::string const & value ) const {
	double vald = std::stod(value);

	return new Operand<int8_t>(*this, eOperandType::Int8, value);
}

IOperand const * Factory::createInt16( std::string const & value ) const {

}

IOperand const * Factory::createInt32( std::string const & value ) const {

}

IOperand const * Factory::createFloat( std::string const & value ) const {

}

IOperand const * Factory::createDouble( std::string const & value ) const {

}
