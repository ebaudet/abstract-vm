/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 19:36:12 by ebaudet           #+#    #+#             */
/*   Updated: 2019/12/09 19:36:32 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Lexer.hpp"

Lexer::Lexer() {
}

Lexer::Lexer(Lexer const &src) {
    *this = src;
}

Lexer::~Lexer() {
}

Lexer &Lexer::operator=(Lexer const &rhs) {
    if (this != &rhs)
        ;
    return *this;
}
