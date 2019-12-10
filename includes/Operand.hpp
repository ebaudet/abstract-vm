/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 19:57:26 by ebaudet           #+#    #+#             */
/*   Updated: 2019/12/10 22:19:51 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(OPERAND_HPP)
#define OPERAND_HPP

#include "IOperand.hpp"
#include "Factory.hpp"
#include "Exception.hpp"
#include <string>

template <typename T>
class Operand : public IOperand {
private:
	Factory const &_factory;
	eOperandType _type;
	std::string _value;

public:
	/***********************************************
		Constructors // Destructors
	************************************************/

	Operand<T>(Factory const &fact, eOperandType type, std::string value)
	: _factory(fact), _type(type), _value(value) {
	}

	// Operand<T>() {
	// 	throw Exception::NullOperand();
	// }

	Operand<T>(Operand const &instance) {
		*this = instance;
	}

	Operand<T> &operator=(Operand const &rhs) {
		if (this != &rhs) {
			this->_factory = rhs.getFactory();
			this->_type = rhs.getType();
			this->_value = rhs.getValue();
		}
		return *this;
	}

	virtual ~Operand<T>() {}

	/***********************************************
		Publics Methods
	************************************************/

	// Precision of the type of the instance
	int				getPrecision( void ) const override {
		return (int)this->_type;
	}

	// Type of the instance
	eOperandType	getType( void ) const override {
		return this->_type;
	}

	std::string getValue() {
		return this->_value;
	}


};

#endif // OPERAND_HPP
