/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Instruction.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 16:46:12 by ebaudet           #+#    #+#             */
/*   Updated: 2020/01/07 18:18:29 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(INSTRUCTION_HPP)
#define INSTRUCTION_HPP

#include "IOperand.hpp"
#include <deque>

class Instruction {

public:
	Instruction();
	Instruction( Instruction const &src );
	Instruction &operator=( Instruction const &rhs );
	~Instruction();

	void push(const IOperand *value);
	void pop();
	void dump();
	void assert_val(const IOperand *value);
	void add();
	void sub();
	void mul();
	void div();
	void mod();
	void print();
	void exit();

	class StackException : public std::runtime_error {
	public:
		StackException();
		StackException(const char* what_arg);
	};
	class AssertException : public std::runtime_error {
	public:
		AssertException();
		// AssertException(const char* what_arg);
	};

// protected:
	std::deque<const IOperand *> *deque;
};

#endif // INSTRUCTION_HPP
