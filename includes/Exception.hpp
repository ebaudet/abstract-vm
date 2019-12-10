/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exception.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 22:07:53 by ebaudet           #+#    #+#             */
/*   Updated: 2019/12/10 22:13:44 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(EXCEPTION_HPP)
#define EXCEPTION_HPP

#include <exception>

class Exception {
    public:
        class RuntimeException: public std::exception {};

        // __RuntimeException_______________

        class NullOperand : public RuntimeException {
            public:
                virtual const char* what() const throw();
        };
    private:
        Exception();
        ~Exception();
};

#endif // EXCEPTION_HPP
