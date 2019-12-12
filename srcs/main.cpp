/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 20:20:36 by ebaudet           #+#    #+#             */
/*   Updated: 2019/12/12 15:03:23 by ebaudet          ###   ########.fr       */
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

    const IOperand *A = F.createOperand(eOperandType::Int16, "175");
    const IOperand *B = F.createOperand(eOperandType::Int32, "0");

    const IOperand *C = *A + *B;

    std::cout << "A: " << A->toString() << ", " << A->getType() << ", " << A->getPrecision() << std::endl;
    std::cout << "B: " << B->toString() << ", " << B->getType() << ", " << B->getPrecision() << std::endl;
    std::cout << "C: A + B = " << C->toString() << ", " << C->getType() << ", " << C->getPrecision() << std::endl;
    delete C;
    C = *A - *B;
    std::cout << "C: A - B = " << C->toString() << ", " << C->getType() << ", " << C->getPrecision() << std::endl;
    delete C;
    try{
        C = *A / *B;
        std::cout << "C: A / B = " << C->toString() << ", " << C->getType() << ", " << C->getPrecision() << std::endl;
     delete C;
    }
    catch(std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    C = *A % *B;
    std::cout << "C: A % B = " << C->toString() << ", " << C->getType() << ", " << C->getPrecision() << std::endl;
    delete C;
    C = *A * *B;
    std::cout << "C: A x B = " << C->toString() << ", " << C->getType() << ", " << C->getPrecision() << std::endl;



    delete A;
    delete B;
    delete C;


    return 0;
}
