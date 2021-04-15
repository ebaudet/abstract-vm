/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Instruction.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 16:46:12 by ebaudet           #+#    #+#             */
/*   Updated: 2020/03/13 18:39:46 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(INSTRUCTION_HPP)
#define INSTRUCTION_HPP

#include "IOperand.hpp"
#include "Factory.hpp"
#include <stdexcept>
#include <deque>
#include <map>
#define EXIT_SUCCESS 0
#define EXIT_INSTR -42

class Instruction {

public:
	struct InstructionArg
	{
		int		nbArg;
		int		(Instruction::*instruction)(const IOperand *);
	};


	// -- Members --------------------------------------------------------------

	static std::map<std::string, InstructionArg>	instrArgs;
	std::deque<const IOperand *>	*deque;
	bool							verbose;
	bool							continue_error;
	bool							interactive;
	bool							instruction_exited;

	// -- Constructors ---------------------------------------------------------

	Instruction();
	Instruction(Instruction const &src);
	~Instruction();

	// -- Operators ------------------------------------------------------------

	Instruction &operator=(Instruction const &rhs);

	// -- Instructions ---------------------------------------------------------

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

	// -- Bonus instructions ---------------------------------------------------

	int		abs(const IOperand *value = NULL);
	int		min(const IOperand *value = NULL);
	int		max(const IOperand *value = NULL);
	int		pow(const IOperand *value = NULL);
	int		debug(const IOperand *value = NULL);
	int		clear(const IOperand *value = NULL);
	int		sep(const IOperand *value = NULL);
	int		help(const IOperand *value = NULL);

	// -- Publics méthods ------------------------------------------------------

	void		test_exit();
	std::string	dval(const IOperand *value);

	// -- Exceptions -----------------------------------------------------------

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
