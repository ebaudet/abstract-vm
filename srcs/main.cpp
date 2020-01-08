/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 20:20:36 by ebaudet           #+#    #+#             */
/*   Updated: 2020/01/08 18:16:20 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Factory.hpp"
#include "Instruction.hpp"
#include "Operand.hpp"
#include "IOperand.hpp"
#include <iostream>

void print_error(std::string error) {
	std::cerr << "\x1B[31m" << error << "\x1B[0m" << std::endl;
}

int test();

int main( int ac, char**av ) {
	(void)ac;
	(void)av;

	test();
	return 0;
}

int test() {
	Factory factory = Factory();

	const IOperand *A = factory.createOperand(eOperandType::Int8, "15");
	const IOperand *B = factory.createOperand(eOperandType::Float, "0");

	const IOperand *C;

	std::cout << "A: " << A->toString() << ", " << A->getType() << ", " << A->getPrecision() << std::endl;
	std::cout << "B: " << B->toString() << ", " << B->getType() << ", " << B->getPrecision() << std::endl;

	try {
		C = *A + *B;
		std::cout << "C: A + B = "  << A->toString() << " + " << B->toString() << " = " << C->toString() << ", " << C->getType() << ", " << C->getPrecision() << std::endl;
		delete C;
	} catch (std::exception &e) {
		print_error("C: A + B = " + A->toString() + " + " + B->toString() + " = " + e.what());
	}
	try {
		C = *A - *B;
		std::cout << "C: A - B = "  << A->toString() << " - " << B->toString() << " = " << C->toString() << ", " << C->getType() << ", " << C->getPrecision() << std::endl;
		delete C;
	} catch (std::exception &e) {
		print_error("C: A - B = " + A->toString() + " - " + B->toString() + " = " + e.what());
	}
	try {
		C = *A / *B;
		std::cout << "C: A / B = " << A->toString() << " / " << B->toString() << " = " << C->toString() << ", " << C->getType() << ", " << C->getPrecision() << std::endl;
		delete C;
	} catch(std::exception &e) {
		print_error("C: A / B = " + A->toString() + " / " + B->toString() + " = " + e.what());
	}
	try {
		C = *A % *B;
		std::cout << "C: A % B = " << A->toString() << " % " << B->toString() << " = " << C->toString() << ", " << C->getType() << ", " << C->getPrecision() << std::endl;
		delete C;
	} catch (std::exception &e) {
		print_error("C: A % B = " + A->toString() + " % " + B->toString() + " = " + e.what());
	}
	try {
		C = *A * *B;
		std::cout << "C: A x B = " << A->toString() << " x " << B->toString() << " = " << C->toString() << ", " << C->getType() << ", " << C->getPrecision() << std::endl;
		delete C;
	} catch (std::exception &e) {
		print_error("C: A x B = " + A->toString() + " x " + B->toString() + " = " + e.what());
	}

	delete A;
	delete B;


	// sample.avm
	Instruction *instruction = new Instruction();
	instruction->debug = true;

	/**
	 * Test 1
	 */
	std::cout << ">>>>> TEST 1" << std::endl;
	try {
		// push int32(2)
		instruction->push(factory.createOperand(eOperandType::Int32, "2"));
		// push int32(3)
		instruction->push(factory.createOperand(eOperandType::Int32, "3"));
		// add
		instruction->add();
		// assert int32(5)
		instruction->assert_val(factory.createOperand(eOperandType::Int32, "5"));
		// dump
		instruction->dump();

	} catch (std::exception &e) {
		print_error(e.what());
	}
	// exit
	instruction->exit();

	/**
	 * Test 2
	 */
	std::cout << ">>>>> TEST 2" << std::endl;
	// pop
	try {
		instruction->pop();
	} catch (std::exception &e) {
		print_error(e.what());
	}
	instruction->exit();

	/**
	 * Test 3
	 */
	std::cout << ">>>>> TEST 3" << std::endl;
	// push int32(2)
	instruction->push(factory.createOperand(eOperandType::Int32, "42"));

	// add
	try {
		instruction->add();
	} catch (std::exception &e) {
		print_error(e.what());
	}

	// push int32(33)
	instruction->push(factory.createOperand(eOperandType::Int32, "33"));

	// add
	try {
		instruction->add();
	} catch (std::exception &e) {
		print_error(e.what());
	}

	// push float(44.55)
	try {
		instruction->push(factory.createOperand(eOperandType::Float, "44.55"));
	} catch (std::exception &e) {
		print_error(e.what());
	}

	// mul
	try {
		instruction->mul();
	} catch (std::exception &e) {
		print_error(e.what());
	}

	// push double(42.42)
	try {
		instruction->push(factory.createOperand(eOperandType::Double, "42.42"));
	} catch (std::exception &e) {
		print_error(e.what());
	}

	// push int32(42)
	try {
		instruction->push(factory.createOperand(eOperandType::Int32, "42"));
	} catch (std::exception &e) {
		print_error(e.what());
	}

	// dump
	try {
		instruction->dump();
	} catch (std::exception &e) {
		print_error(e.what());
	}

	// pop
	try {
		instruction->pop();
	} catch (std::exception &e) {
		print_error(e.what());
	}

	// assert double(42.42)
	try {
		instruction->assert_val(factory.createOperand(eOperandType::Double, "42.42"));
	} catch (std::exception &e) {
		print_error(e.what());
	}


	try {
		instruction->push(factory.createOperand(eOperandType::Int8, "42"));
	} catch (std::exception &e) {
		print_error(e.what());
	}

	instruction->print();

	// exit
	instruction->exit();
	try {
		instruction->test_exit();
	} catch (std::exception &e) {
		print_error(e.what());
	}
	return (0);
}
