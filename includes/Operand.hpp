/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 19:57:26 by ebaudet           #+#    #+#             */
/*   Updated: 2020/01/06 18:55:50 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(OPERAND_HPP)
#define OPERAND_HPP

#include "IOperand.hpp"
#include "Factory.hpp"
#include "Exception.hpp"
#include <string>
#include <sstream>
#include <cmath>
#include <stdexcept>

enum eOperationType { Multiplication, Division, Addition, Substration, Modulo };

template <typename T>
class Operand : public IOperand {

public:
	/***********************************************
		Constructors // Destructors
	************************************************/

	Operand<T>( Factory const &fact, eOperandType type, std::string value )
	: _factory( fact ), _type( type ), _value( value ) {
	}

	Operand<T>( Operand const &instance ) {
		*this = instance;
	}

	Operand<T> &operator=( Operand const &rhs ) {
		if ( this != &rhs ) {
			_factory = rhs.getFactory();
			_type = rhs.getType();
			_value = rhs.toString();
		}
		return *this;
	}

	virtual ~Operand<T>() {}

	/***********************************************
		overload operators pour Operand
	************************************************/

	// Product
	IOperand const *	operator*( IOperand const & rhs ) const {
		return _operation( rhs, eOperationType::Multiplication );
	}

	// Quotient
	IOperand const *	operator/( IOperand const & rhs ) const {
		return _operation( rhs, eOperationType::Division );
	}

	// Sum
	IOperand const *	operator+( IOperand const & rhs ) const {
		return _operation( rhs, eOperationType::Addition );
	}
	//open Difference
	IOperand const *	operator-( IOperand const & rhs ) const {
		return _operation( rhs, eOperationType::Substration );
	}
	// Modulo
	IOperand const *	operator%( IOperand const & rhs ) const {
		return _operation( rhs, eOperationType::Modulo );
	}

	/***********************************************
		Getters & Setters
	************************************************/

	// Precision of the type of the instance
	int				getPrecision( void ) const {
		return static_cast<int>( _type );
	}

	// Type of the instance
	eOperandType	getType( void ) const {
		return _type;
	}

	std::string getValue() {
		return _value;
	}

	// String representation of the instance
	std::string const & toString( void ) const {
		return _value;
	}

	class DivideByZeroException : public std::runtime_error {
		public:
			DivideByZeroException() : std::runtime_error( "Divide by zero exception." ) {}
	};
	class OverflowException : public std::overflow_error {
		public:
			OverflowException() : std::overflow_error( "Overflow on a value" ) {}
	};
	class UnderflowException : public std::overflow_error {
		public:
			UnderflowException() : std::overflow_error( "Underflow on a value" ) {}
	};

private:

	/***********************************************
		private members
	************************************************/

	const Factory	&_factory;
	eOperandType	_type;
	std::string		_value;

	/***********************************************
		private Methods
	************************************************/

	Operand<T>() {} // constructeur sans argument non accessible.

	IOperand const *	_operation( IOperand const & rhs, eOperationType operation ) const {
		double rval = std::stod( rhs.toString() );
		double lval = std::stod( _value );
		double result = 0;
		switch ( operation ) {
			case eOperationType::Multiplication:
				result = lval * rval;
				break;
			case eOperationType::Division:
				if (rval == 0)
					throw Operand::DivideByZeroException();
				result = lval / rval;
				break;
			case eOperationType::Addition:
				result = lval + rval;
				break;
			case eOperationType::Substration:
				result = lval - rval;
				break;
			case eOperationType::Modulo:
				if (rval == 0)
					throw Operand::DivideByZeroException();
				result = std::fmod( lval, rval );
				break;
			default:
				throw Exception::Operand();
				break;
		}
		if (result > std::numeric_limits<double>::max())
			throw Operand::OverflowException();
		if (result < std::numeric_limits<double>::lowest())
			throw Operand::UnderflowException();

		int precision = std::max( rhs.getPrecision(), this->getPrecision() );
		eOperandType type = static_cast<eOperandType>( precision );
		std::ostringstream strs;
		strs << result;
		return _factory.createOperand( type, strs.str() );
	}
};

#endif // OPERAND_HPP
