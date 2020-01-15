/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Instruction.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 16:46:12 by ebaudet           #+#    #+#             */
/*   Updated: 2020/01/15 23:08:37 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(INSTRUCTION_HPP)
#define INSTRUCTION_HPP

#include "IOperand.hpp"
#include "Factory.hpp"
#include <deque>
#include <map>

class Instruction {

public:
	struct InstructionArg
	{
		int		nbArg;
		int		(Instruction::*instruction)(const IOperand *);
	};

	static std::map<std::string, InstructionArg>	instrArgs;
	std::deque<const IOperand *>	*deque;
	bool							verbose;
	bool							continue_error;
	bool							interactive;
	bool							instruction_exited;

	Instruction();
	Instruction( Instruction const &src );
	Instruction &operator=( Instruction const &rhs );
	~Instruction();

	int		push(const IOperand *value);
	int		pop(const IOperand *value = NULL);
	int		dump(const IOperand *value = NULL);
	int		assert_val(const IOperand *value);
	int		add(const IOperand *value = NULL);
	int		sub(const IOperand *value = NULL);
	int		mul(const IOperand *value = NULL);
	int		div(const IOperand *value = NULL);
	int		mod(const IOperand *value = NULL);
	int		print(const IOperand *value = NULL);
	int		exit(const IOperand *value = NULL);

	void	test_exit();
	void	clear();

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

};

#endif // INSTRUCTION_HPP
