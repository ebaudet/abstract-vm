/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exception.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 20:47:24 by ebaudet           #+#    #+#             */
/*   Updated: 2020/03/13 20:47:25 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Exception.hpp"

Exception::Exception() {}

Exception::~Exception() {}
// __ConceptionException____________
const char* Exception::Factory::what() const throw() {
	return ("Unexpected event");
}
const char* Exception::Operand::what() const throw() {
	return ("Unexpected event");
}

// __RuntimeException_______________
const char* Exception::Overflow::what() const throw() {
	return ("Overflow on a value");
}
const char* Exception::Underflow::what() const throw() {
	return ("Underflow on a value");
}
