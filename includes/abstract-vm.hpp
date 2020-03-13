/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abstract-vm.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 19:40:57 by ebaudet           #+#    #+#             */
/*   Updated: 2020/03/13 20:39:50 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(ABSTRACT_VM)
#define ABSTRACT_VM

#include <iostream>
#include "Instruction.hpp"
#include "Parser.hpp"
#include "Factory.hpp"

void	print_error(std::string error);
int		readFromFile(char *file, Instruction &instruction);
int		readFromStdin(Instruction &instruction);
template<class _CharT, class _Traits>
int		readInput(Instruction &instruction,
std::basic_istream<_CharT, _Traits>& input, bool stdin);
int		readLine(std::string line, int line_row,
		std::vector <Parser *> &parsers, Instruction &instruction,
		Factory &factory);
int		executeInstructions(std::vector <Parser *> parsers,
		Instruction &instruction, Factory &factory);
bool	execute(Factory &factory, Instruction &instruction, Parser &p);

#endif // ABSTRACT_VM
