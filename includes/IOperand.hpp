/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IOperand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 19:44:18 by ebaudet           #+#    #+#             */
/*   Updated: 2019/12/09 20:14:22 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(IOPERAND_HPP)
#define IOPERAND_HPP

#include <string>

enum eOperandType {Int8, Int16, Int32, Float, Double};

class IOperand {
public:
    virtual int getPrecision( void ) const = 0; // Precision of the type of the instance
    virtual eOperandType getType( void ) const = 0; // Type of the instance
    virtual IOperand const * operator+( IOperand const & rhs ) const = 0; // Sum
    virtual IOperand const * operator-( IOperand const & rhs ) const = 0; //open Difference
    virtual IOperand const * operator*( IOperand const & rhs ) const = 0; // Product
    virtual IOperand const * operator/( IOperand const & rhs ) const = 0; // Quotient
    virtual IOperand const * operator%( IOperand const & rhs ) const = 0; // Modulo
    virtual std::string const & toString( void ) const = 0; // String representation of the instance
    virtual ~IOperand( void ) {}
};

#endif // IOPERAND_HPP
