/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Instruction.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 16:46:12 by ebaudet           #+#    #+#             */
/*   Updated: 2020/01/14 17:58:48 by ebaudet          ###   ########.fr       */
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
		void	(Instruction::*instruction)(const IOperand *);
	};

	static std::map<std::string, InstructionArg>	instrArgs;
	std::deque<const IOperand *>	*deque;
	bool							verbose;
	bool							continue_error;
	bool							instruction_exited;

	Instruction();
	Instruction( Instruction const &src );
	Instruction &operator=( Instruction const &rhs );
	~Instruction();

	void	push(const IOperand *value);
	void	pop(const IOperand *value = NULL);
	void	dump(const IOperand *value = NULL);
	void	assert_val(const IOperand *value);
	void	add(const IOperand *value = NULL);
	void	sub(const IOperand *value = NULL);
	void	mul(const IOperand *value = NULL);
	void	div(const IOperand *value = NULL);
	void	mod(const IOperand *value = NULL);
	void	print(const IOperand *value = NULL);
	void	exit(const IOperand *value = NULL);

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
