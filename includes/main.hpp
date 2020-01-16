/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 22:12:22 by ebaudet           #+#    #+#             */
/*   Updated: 2020/01/16 21:09:29 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_HPP_
#define MAIN_HPP_

#include <iostream>
#include <vector>
#include "Instruction.hpp"
#include "Parser.hpp"
#include "Factory.hpp"

void	print_error(std::string error);
int		executeInstruction( std::vector <Parser *> parsers,
		Instruction &instruction, Factory &factory );
int		readLine( std::string line, int line_row,
		std::vector <Parser *> &parsers, Instruction &instruction,
		Factory &factory);
int		readFromFile( char *file, Instruction &instruction );
int		readFromStdin( Instruction &instruction );

#endif  // MAIN_HPP_
