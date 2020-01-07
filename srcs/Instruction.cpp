/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Instruction.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 16:50:19 by ebaudet           #+#    #+#             */
/*   Updated: 2020/01/07 18:18:25 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Instruction.hpp"
// #include <deque>

Instruction::Instruction() {
	deque = new std::deque<const IOperand *>();
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

void Instruction::push(const IOperand *value) {
	deque->push_front(value);
}

void Instruction::pop() {
	deque->pop_front();
}

void Instruction::dump() {
	// TODO
}

void Instruction::assert_val(const IOperand *value) {
	const IOperand *test = deque->front();
	if (value != test)
		throw Instruction::AssertException();
}

void Instruction::add() {
	if (deque->size() < 2)
		throw Instruction::StackException( "Add: Stack is lower 2." );
	const IOperand *A = deque->front();
	deque->pop_front();
	const IOperand *B = deque->front();
	deque->pop_front();
	const IOperand *C;
	C = *A + *B;
	deque->push_front(C);
	delete A;
	delete B;
}
