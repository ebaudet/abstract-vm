/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Factory.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 20:25:01 by ebaudet           #+#    #+#             */
/*   Updated: 2020/05/09 16:51:58 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits>
#include "Factory.hpp"
#include "Operand.hpp"
#include "Exception.hpp"

// -- Constructors -------------------------------------------------------------

Factory::Factory() {
}

Factory::Factory(Factory const &src) {
	*this = src;
}

Factory::~Factory() {
}

// -- Operators ----------------------------------------------------------------

Factory &Factory::operator=(Factory const &rhs) {
	if (this != &rhs) {
	}
	return *this;
}

// -- Public methods -----------------------------------------------------------

/**
 * @brief Factory method to create new operands.
 *
 * @param type
 * @param value
 * @return IOperand const*
 */
IOperand const * Factory::createOperand(eOperandType type, std::string const & value) const {
	IOperand const *(Factory::*func)(std::string const & value) const = NULL;

	switch (type) {
		case eOperandType::Int8:
			func = &Factory::createInt8;
			break;
		case eOperandType::Int16:
			func = &Factory::createInt16;
			break;
		case eOperandType::Int32:
			func = &Factory::createInt32;
			break;
		case eOperandType::Float:
			func = &Factory::createFloat;
			break;
		case eOperandType::Double:
			func = &Factory::createDouble;
			break;
		default:
			throw Exception::Factory();
			break;
	}

	return (this->*func)(value);
}

// -- Private methods ----------------------------------------------------------

IOperand const * Factory::createInt8(std::string const & value) const {
	std::string convertValue = this->_convertType<int8_t>(value);

	return new Operand<int8_t>(*this, eOperandType::Int8, convertValue);
}

IOperand const * Factory::createInt16(std::string const & value) const {
	std::string convertValue = this->_convertType<int16_t>(value);

	return new Operand<int16_t>(*this, eOperandType::Int16, convertValue);
}

IOperand const * Factory::createInt32(std::string const & value) const {
	std::string convertValue = this->_convertType<int32_t>(value);

	return new Operand<int32_t>(*this, eOperandType::Int32, convertValue);
}

IOperand const * Factory::createFloat(std::string const & value) const {
	std::string convertValue = this->_convertType<float>(value);

	return new Operand<float>(*this, eOperandType::Float, convertValue);
}

IOperand const * Factory::createDouble(std::string const & value) const {
	std::string convertValue = this->_convertType<double>(value);

	return new Operand<double>(*this, eOperandType::Double, convertValue);
}

template <typename T>
std::string Factory::_convertType(std::string const & value) const {
	double vald = std::stod(value);

	if (vald > std::numeric_limits<T>::max())
			throw Exception::Overflow();
	if (vald < std::numeric_limits<T>::lowest())
		throw Exception::Underflow();

	std::ostringstream strs;
	strs << +static_cast<T>(vald);
	return strs.str();
}
