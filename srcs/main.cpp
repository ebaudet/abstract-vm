/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 20:20:36 by ebaudet           #+#    #+#             */
/*   Updated: 2020/01/15 23:22:55 by ebaudet          ###   ########.fr       */
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

	return (EXIT_SUCCESS);
}

void	print_error(std::string error) {
	std::cerr << RED << error << EOC << std::endl;
}

int		readFromFile( char *file, Instruction &instruction ) {
	std::vector <Parser *> parsers;
	Factory factory = Factory();
	std::ifstream infile(file);
	std::string line;
	int error = 0;

	for (int line_row = 1; std::getline(infile, line); line_row++) {
		if (readLine(line, line_row, parsers, instruction, factory) == EXIT_FAILURE) {
			error++;
			if (!instruction.continue_error)
				return (EXIT_FAILURE);
		}
	}

	if (!instruction.interactive && !error) {
		if (executeInstruction( parsers, instruction, factory ) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	if (error) {
		std::cout << error << " errors." << std::endl;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int		readFromStdin( Instruction &instruction ) {
	std::vector <Parser *> parsers;
	Factory factory = Factory();
	std::string line;
	int error = 0;
	int result;

	if (instruction.interactive)
		std::cout << "> ";
	for (int line_row = 1; std::getline(std::cin, line); line_row++) {
		if (line == ";;")
			break ;
		result = readLine( line, line_row, parsers, instruction, factory );
		if ( result == EXIT_FAILURE ) {
			error++;
			if (!instruction.continue_error)
				return EXIT_FAILURE;
		} else if ( instruction.interactive && result == 42 )
			break ;
		if (instruction.interactive)
			std::cout << "> ";
	}
	if (!instruction.interactive && !error) {
		if (executeInstruction( parsers, instruction, factory ) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	if (error) {
		std::cout << error << " errors." << std::endl;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
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
