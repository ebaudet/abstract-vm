/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exception.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 22:07:53 by ebaudet           #+#    #+#             */
/*   Updated: 2020/01/07 16:14:41 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(EXCEPTION_HPP)
#define EXCEPTION_HPP

#include <exception>
#include <stdexcept>

class Exception {
	public:
		class ConceptionException: public std::exception {};
		class RuntimeException: public std::exception {};

		// __ConceptionException____________

		class Factory : public ConceptionException {
			public:
				virtual const char* what() const throw();
		};
		class Operand : public ConceptionException {
			public:
				virtual const char* what() const throw();
		};

		// __RuntimeException_______________

		class Overflow : public RuntimeException {
			public:
				virtual const char* what() const throw();
		};
		class Underflow : public RuntimeException {
			public:
				virtual const char* what() const throw();
		};

	private:
		Exception();
		~Exception();
};

#endif // EXCEPTION_HPP
