/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Instruction.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 16:46:12 by ebaudet           #+#    #+#             */
/*   Updated: 2020/01/08 18:00:34 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(INSTRUCTION_HPP)
#define INSTRUCTION_HPP

#include "IOperand.hpp"
#include "Factory.hpp"
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
	void test_exit();

	class StackException : public std::runtime_error {
	public:
		StackException();
		StackException(const char* what_arg);
	};
	class AssertException : public std::runtime_error {
	public:
		AssertException();
	};
	class ExitException : public std::runtime_error {
	public:
		ExitException();
	};


	std::deque<const IOperand *>	*deque;
	bool							debug;
	bool							instruction_exited;
protected:
	// Factory F;
};

#endif // INSTRUCTION_HPP
