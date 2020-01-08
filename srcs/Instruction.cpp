/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Instruction.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 16:50:19 by ebaudet           #+#    #+#             */
/*   Updated: 2020/01/08 18:01:00 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Instruction.hpp"
#include <iostream>

Instruction::Instruction() {
	deque = new std::deque<const IOperand *>();
	debug = false;
	instruction_exited = false;
}

Instruction::Instruction( Instruction const &src ) {
	*this = src;
}

Instruction &Instruction::operator=( Instruction const &rhs ) {
	if ( this != &rhs )
		deque = new std::deque<const IOperand *>(*rhs.deque);
	return *this;
}

Instruction::~Instruction() {
	delete deque;
}

Instruction::StackException::StackException() : std::runtime_error( "Stack exception" ) {}
Instruction::StackException::StackException(const char* what_arg) : std::runtime_error( what_arg ) {}

Instruction::AssertException::AssertException() : std::runtime_error( "Assert exception" ) {}
Instruction::ExitException::ExitException() : std::runtime_error( "Exit instruction is missing." ) {}

/**
 * Pushes the value v at the top of the stack. The value v must have one of
 * the following form:
 * ◦ int8(n) : Creates an 8-bit integer with value n.
 * ◦ int16(n) : Creates a 16-bit integer with value n.
 * ◦ int32(n) : Creates a 32-bit integer with value n.
 * ◦ float(z) : Creates a float with value z.
 * ◦ double(z) : Creates a double with value z.
 */
void Instruction::push(const IOperand *value) {
	deque->push_front(value);
}

/**
 * Unstacks the value from the top of the stack. If the stack is empty, the
 * program execution must stop with an error.
 */
void Instruction::pop() {
	if (deque->size() == 0)
		throw Instruction::StackException( "Pop: Stack is empty." );
	const IOperand *A = deque->front();
	deque->pop_front();
	delete A;
}

/**
 * Displays each value of the stack, from the most recent one to the oldest
 * one WITHOUT CHANGING the stack. Each value is separated from the next one
 * by a newline.
 */
void Instruction::dump() {
	std::deque<const IOperand *>::iterator it;
	if (debug)
		std::cout << "\x1B[34mdump >\x1B[0m" << std::endl;
	for (it = deque->begin(); it != deque->end(); ++it) {
		std::cout << (*it)->toString() << std::endl;
	}
}

/**
 * Asserts that the value at the top of the stack is equal to the one passed
 * as parameter for this instruction. If it is not the case, the program execution must
 * stop with an error. The value v has the same form that those passed as parameters
 * to the instruction push.
 */
void Instruction::assert_val(const IOperand *value) {
	const IOperand *test = deque->front();
	if (*value != *test) {
		delete value;
		throw Instruction::AssertException();
	}
	delete value;
}

/**
 * Unstacks the first two values on the stack, adds them together and stacks the
 * result. If the number of values on the stack is strictly inferior to 2, the program
 * execution must stop with an error.
 */
void Instruction::add() {
	if (deque->size() < 2)
		throw Instruction::StackException( "Add: Stack is lower 2." );
	const IOperand *A = deque->front();
	deque->pop_front();
	const IOperand *B = deque->front();
	deque->pop_front();
	const IOperand *C;
	C = *A + *B;
	push(C);
	delete A;
	delete B;
}

/**
 *  Unstacks the first two values on the stack, subtracts them, then stacks the
 * result. If the number of values on the stack is strictly inferior to 2, the program
 * execution must stop with an error.
 */
void Instruction::sub() {
	if (deque->size() < 2)
		throw Instruction::StackException( "Add: Stack is lower 2." );
	const IOperand *A = deque->front();
	deque->pop_front();
	const IOperand *B = deque->front();
	deque->pop_front();
	const IOperand *C;
	C = *A - *B;
	push(C);
	delete A;
	delete B;
}

/**
 * Unstacks the first two values on the stack, multiplies them, then stacks the
 * result. If the number of values on the stack is strictly inferior to 2, the program
 * execution must stop with an error.
 */
void Instruction::mul() {
	if (deque->size() < 2)
		throw Instruction::StackException( "Add: Stack is lower 2." );
	const IOperand *A = deque->front();
	deque->pop_front();
	const IOperand *B = deque->front();
	deque->pop_front();
	const IOperand *C;
	C = *A * *B;
	push(C);
	delete A;
	delete B;
}

/**
 * Unstacks the first two values on the stack, divides them, then stacks the result.
 * If the number of values on the stack is strictly inferior to 2, the program execution
 * must stop with an error. Moreover, if the divisor is equal to 0, the program execution
 * must stop with an error too. Chatting about floating point values is relevant a this
 * point. If you don’t understand why, some will understand. The linked question is
 * an open one, there’s no definitive answer.
 */
void Instruction::div() {
	if (deque->size() < 2)
		throw Instruction::StackException( "Add: Stack is lower 2." );
	const IOperand *A = deque->front();
	deque->pop_front();
	const IOperand *B = deque->front();
	deque->pop_front();
	const IOperand *C;
	C = *A / *B;
	push(C);
	delete A;
	delete B;
}

/**
 * Unstacks the first two values on the stack, calculates the modulus, then
 * stacks the result. If the number of values on the stack is strictly inferior to 2, the
 * program execution must stop with an error. Moreover, if the divisor is equal to 0,
 * the program execution must stop with an error too. Same note as above about fp
 * values.
 */
void Instruction::mod() {
	if (deque->size() < 2)
		throw Instruction::StackException( "Add: Stack is lower 2." );
	const IOperand *A = deque->front();
	deque->pop_front();
	const IOperand *B = deque->front();
	deque->pop_front();
	const IOperand *C;
	C = *A % *B;
	push(C);
	delete A;
	delete B;
}

/**
 * Asserts that the value at the top of the stack is an 8-bit integer. (If not,
 * see the instruction assert), then interprets it as an ASCII value and displays the
 * corresponding character on the standard output.
 */
void Instruction::print() {
	const IOperand *to_print = deque->front();
	if (to_print->getType() != eOperandType::Int8)
		throw Instruction::AssertException();
	if (debug)
		std::cout << "\x1B[34mprint >\x1B[0m" << std::endl;
	std::cout << static_cast<char>( std::stod( to_print->toString() ) ) << std::endl;
}

/**
 * Terminate the execution of the current program. If this instruction does not
 * appears while all others instruction has been processed, the execution must stop
 * with an error.
 */
void Instruction::exit() {
	while (deque->size() > 0) {
		pop();
	}
	instruction_exited = true;
}

void Instruction::test_exit() {
	if (!instruction_exited)
		throw Instruction::ExitException();
}
