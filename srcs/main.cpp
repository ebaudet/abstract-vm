/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 20:20:36 by ebaudet           #+#    #+#             */
/*   Updated: 2020/01/17 19:42:31 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argparse.hpp"
#include "Lexer.hpp"
#include "Color.hpp"
#include <unistd.h>
#include <fstream>
#include "main.hpp"

int		main( int ac, char**av ) {
	Lexer lexer = Lexer();
	Instruction instruction = Instruction();

	if (argparse(ac, av, instruction) == EXIT_FAILURE)
		return EXIT_FAILURE;

	int result;
	switch ( ac - optind ) {
		case 0:
			result = readFromStdin(instruction);
			break;
		case 1:
			result = readFromFile(av[optind], instruction);
			break;
		default:
			return (usage(av[0]));
	}

	if (result == EXIT_SUCCESS) {
		try {
			instruction.test_exit();
		} catch (std::exception &e) {
			print_error(e.what());
		}
	}

	return (result);
}

void	print_error(std::string error) {
	std::cerr << RED << error << EOC << std::endl;
}

template<class _CharT, class _Traits>
int		readFromInput( Instruction &instruction,
std::basic_istream<_CharT, _Traits>& input, bool stdin ) {
	std::vector <Parser *> parsers;
	Factory factory = Factory();
	std::string line;
	int error = 0;
	int result;

	if (stdin && instruction.interactive)
		std::cout << "> ";
	for (int line_row = 1; std::getline(input, line); line_row++) {
		if (stdin && line == ";;")
			break ;
		result = readLine( line, line_row, parsers, instruction, factory );
		if ( result == EXIT_FAILURE ) {
			error++;
			if (!instruction.continue_error)
				return EXIT_FAILURE;
		} else if ( stdin && instruction.interactive && result == 42 )
			break ;
		if (stdin && instruction.interactive)
			std::cout << "> ";
	}
	if (!instruction.interactive && !error) {
		if (executeInstruction( parsers, instruction, factory ) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	if (error) {
		std::cout << MAGENTA "______________________\n" << error
		<< " errors generated." EOC << std::endl;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int		readFromFile( char *file, Instruction &instruction  ) {
	std::ifstream infile(file);
	return readFromInput (instruction, infile, false);
}

int		readFromStdin( Instruction &instruction ) {
	return readFromInput (instruction, std::cin, true);
}

int		readLine( std::string line, int line_row, std::vector <Parser *> &parsers,
Instruction &instruction, Factory &factory) {
	Lexer lexer = Lexer();
	Parser *parser = new Parser( line );
	int result = EXIT_SUCCESS;

	try {
		lexer.lexLine( line, line_row );
		parser->parseToken( lexer.listToken, line, line_row );
		if (instruction.interactive) {
			result = parser->execute( factory, instruction );
			delete parser;
		}
		else
			parsers.push_back(parser);

	} catch (std::exception &e) {
		print_error( e.what() );
		return (EXIT_FAILURE);
	}

	return (result);
}

int		executeInstruction( std::vector <Parser *> parsers, Instruction &instruction, Factory &factory ) {
	bool execution = true;
	int result;

	try {
		for (auto &&parser : parsers) {
			if (execution)
				result = parser->execute( factory, instruction );
			delete parser;
			if (result == 42 || result == EXIT_FAILURE)
				execution = false;
		}
	} catch (std::exception &e) {
		print_error( e.what() );
		if (!instruction.continue_error)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
