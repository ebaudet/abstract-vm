/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 20:20:36 by ebaudet           #+#    #+#             */
/*   Updated: 2020/01/14 20:05:09 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Factory.hpp"
#include "Instruction.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"
#include "Color.hpp"

#include <iostream>
#include <unistd.h>
#include <fstream>

void	print_error(std::string error) {
	std::cerr << RED << error << EOC << std::endl;
}

int		usage( char *file ) {
	fprintf(stderr, "Usage: %s [-ve] [FILE]\n", file);
	return (EXIT_FAILURE);
}

int		readLine( std::string line, int line_row, Instruction &instruction ) {
	Lexer lexer = Lexer();
	Parser parser = Parser( line );
	Factory factory = Factory();

	try {
		// listToken.erase( listToken.begin(), listToken.end() );
		lexer.lexLine( line, line_row );
		// std::cout << "listVector " << listToken << std::endl;

		parser.parseToken( lexer.listToken, line );
		parser.execute( factory, instruction );

	} catch (std::runtime_error &e) {
		print_error( e.what() );
		if (!instruction.continue_error)
			return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

void	readFromFile( char *file, Instruction &instruction ) {
	std::ifstream infile(file);
	std::string line;

	for (int line_row = 1; std::getline(infile, line); line_row++) {
		if (readLine(line, line_row, instruction) == EXIT_FAILURE)
			return ;
	}
}

void	readFromStdin( Instruction &instruction ) {
	std::string line;

	std::cout << "> ";
	for (int line_row = 1; std::getline(std::cin, line); line_row++) {
		if (line == ";;")
			return ;
		if (readLine(line, line_row, instruction) == EXIT_FAILURE)
			return ;
		std::cout << "> ";
	}
}

int		main( int ac, char**av ) {
	int opt;
	Lexer lexer = Lexer();
	Instruction instruction = Instruction();

	while ((opt = getopt(ac, av, "vhe")) != EOF) {
		switch (opt) {
			case 'v': // verbose
				instruction.verbose = true;
				break;
			case 'e': // continue on error
				instruction.continue_error = true;
				break;
			case 'h': default:
				return (usage(av[0]));
		}
	}

	if ( ac - optind == 1 ) {
		readFromFile(av[optind], instruction);
	}
	else if ( ac - optind == 0 ) {
		readFromStdin(instruction);
	}
	else
		return (usage(av[0]));

	try {
		instruction.test_exit();
	} catch (std::exception &e) {
		print_error(e.what());
	}

	return (EXIT_SUCCESS);
}
