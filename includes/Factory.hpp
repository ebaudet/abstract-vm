/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Factory.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 20:25:39 by ebaudet           #+#    #+#             */
/*   Updated: 2019/12/09 20:33:52 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(FACTORY_HPP)
#define FACTORY_HPP

#include "IOperand.hpp"

class Factory {
    public:
        Factory();
        Factory(Factory const &src);
        virtual ~Factory();

        Factory &operator=(Factory const &rhs);

        IOperand const * createOperand( eOperandType type, std::string const & value ) const;
    private:
        IOperand const * createInt8( std::string const & value ) const;
        IOperand const * createInt16( std::string const & value ) const;
        IOperand const * createInt32( std::string const & value ) const;
        IOperand const * createFloat( std::string const & value ) const;
        IOperand const * createDouble( std::string const & value ) const;
};

#endif // FACTORY_HPP
