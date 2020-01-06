/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 20:20:36 by ebaudet           #+#    #+#             */
/*   Updated: 2020/01/06 18:55:01 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Factory.hpp"
#include "Operand.hpp"
#include "IOperand.hpp"
#include <iostream>

int main( int ac, char**av ) {
    (void)ac;
    (void)av;

    Factory F = Factory();

    const IOperand *A = F.createOperand(eOperandType::Int16, "15");
    const IOperand *B = F.createOperand(eOperandType::Float, "32");

    const IOperand *C;

    std::cout << "A: " << A->toString() << ", " << A->getType() << ", " << A->getPrecision() << std::endl;
    std::cout << "B: " << B->toString() << ", " << B->getType() << ", " << B->getPrecision() << std::endl;

    try {
        C = *A + *B;
        std::cout << "C: A + B = "  << A->toString() << " + " << B->toString() << " = " << C->toString() << ", " << C->getType() << ", " << C->getPrecision() << std::endl;
        delete C;
    } catch (std::exception &e) {
        std::cerr << "C: A + B = "  << A->toString() << " + " << B->toString() << " = " << e.what() << std::endl;
    }
    try {
        C = *A - *B;
        std::cout << "C: A - B = "  << A->toString() << " - " << B->toString() << " = " << C->toString() << ", " << C->getType() << ", " << C->getPrecision() << std::endl;
        delete C;
    } catch (std::exception &e) {
        std::cerr << "C: A - B = "  << A->toString() << " - " << B->toString() << " = " << e.what() << std::endl;
    }
    try {
        C = *A / *B;
        std::cout << "C: A / B = " << A->toString() << " / " << B->toString() << " = " << C->toString() << ", " << C->getType() << ", " << C->getPrecision() << std::endl;
        delete C;
    } catch(std::exception &e) {
        std::cerr << "C: A / B = " << A->toString() << " / " << B->toString() << " = " << e.what() << std::endl;
    }
    try {
        C = *A % *B;
        std::cout << "C: A % B = " << A->toString() << " % " << B->toString() << " = " << C->toString() << ", " << C->getType() << ", " << C->getPrecision() << std::endl;
        delete C;
    } catch (std::exception &e) {
        std::cerr << "C: A % B = " << A->toString() << " % " << B->toString() << " = " << e.what() << std::endl;
    }
    try {
        C = *A * *B;
        std::cout << "C: A x B = " << A->toString() << " x " << B->toString() << " = " << C->toString() << ", " << C->getType() << ", " << C->getPrecision() << std::endl;
        delete C;
    } catch (std::exception &e) {
        std::cerr << "C: A x B = " << A->toString() << " x " << B->toString() << " = " << e.what() << std::endl;
    }

    delete A;
    delete B;

    return 0;
}
