/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 20:20:36 by ebaudet           #+#    #+#             */
/*   Updated: 2020/01/08 11:34:10 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Factory.hpp"
#include "Operand.hpp"
#include "IOperand.hpp"
#include <iostream>
#include <stack>
#include "Instruction.hpp"
// #include <stdexcept>

// class StackException : public std::runtime_error {
// 	public:
// 		StackException() : std::runtime_error( "Stack exception" ) {}
// 		StackException(const char* what_arg) : std::runtime_error( what_arg ) {}
// };

// void     add(std::stack<const IOperand *> *stack) {
// 	if (stack->size() < 2)
// 		throw StackException( "Add: Stack is lower 2." );
// 	const IOperand *A = stack->top();
// 	stack->pop();
// 	const IOperand *B = stack->top();
// 	stack->pop();
// 	const IOperand *C;
// 	C = *A + *B;
// 	stack->push(C);
// }

int main( int ac, char**av ) {
	(void)ac;
	(void)av;

	Factory F = Factory();

	const IOperand *A = F.createOperand(eOperandType::Int16, "15");
	const IOperand *B = F.createOperand(eOperandType::Float, "0");

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


	// sample.avm
	Instruction *I = new Instruction();
	// std::stack<const IOperand *> *stack = new std::stack<const IOperand *>();

	// push int32(2)
	I->push(F.createOperand(eOperandType::Int32, "2"));
	// add
	try {
		I->add();
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	// push int32(33)
	I->push(F.createOperand(eOperandType::Int32, "33"));
	// add
	try {
		I->add();
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}

	// push float(44.55)
	try {
		I->push(F.createOperand(eOperandType::Float, "44.55"));
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}

	// mul
	try {
		I->mul();
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}

	// push double(42.42)
	try {
		I->push(F.createOperand(eOperandType::Double, "42.42"));
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}

	// push int32(42)
	try {
		I->push(F.createOperand(eOperandType::Int32, "42"));
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}

	// dump
	try {
		I->dump();
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}

	// pop
	try {
		I->pop();
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}

	// assert double(42.42)
	try {
		I->assert_val(F.createOperand(eOperandType::Double, "42.42"));
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}


	// exit

	return 0;
}
