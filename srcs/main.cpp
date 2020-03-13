/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 20:20:36 by ebaudet           #+#    #+#             */
/*   Updated: 2020/03/13 20:47:27 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "abstract-vm.hpp"
#include "argparse.hpp"
#include "Lexer.hpp"
#include "Color.hpp"

int		main(int ac, char**av) {
	Lexer lexer = Lexer();
	Instruction instruction = Instruction();

	if (argparse(ac, av, instruction) == EXIT_FAILURE)
		return EXIT_FAILURE;

	int result;
	switch (ac - optind) {
		case 0:
			result = readFromStdin(instruction);
			break;
		case 1:
			result = readFromFile(av[optind], instruction);
			break;
		default:
			return (usage(av[0]));
	}

	if (instruction.continue_error && result > 0) {
		std::cout << MAGENTA "______________________\n" << result
		<< " errors generated." EOC << std::endl;
		return (EXIT_FAILURE);
	}

	return (result);
}
