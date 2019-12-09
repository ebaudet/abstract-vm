/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 19:44:22 by ebaudet           #+#    #+#             */
/*   Updated: 2019/12/09 19:44:22 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"

Parser::Parser() {
}

Parser::Parser(Parser const &src) {
    *this = src;
}

Parser::~Parser() {
}

Parser &Parser::operator=(Parser const &rhs) {
    if (this != &rhs)
        ;
    return *this;
}
