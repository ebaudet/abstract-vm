/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Factory.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 20:25:01 by ebaudet           #+#    #+#             */
/*   Updated: 2019/12/09 20:33:56 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Factory.hpp"

Factory::Factory() {
}

Factory::Factory(Factory const &src) {
    *this = src;
}

Factory::~Factory() {
}

Factory &Factory::operator=(Factory const &rhs) {
    if (this != &rhs)
        ;
    return *this;
}
