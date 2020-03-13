/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abstract-vm.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 19:46:19 by ebaudet           #+#    #+#             */
/*   Updated: 2020/03/13 20:51:24 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include "abstract-vm.hpp"
#include "Color.hpp"
#include "Lexer.hpp"

/**
 * @brief Error message.
 *
 * @param error
 */
void	print_error(std::string error) {
	std::cerr << RED << error << EOC << std::endl;
}

/**
 * @brief Read Input for a file.
 *
 * @param file
 * @param instruction
 * @return int
 */
int		readFromFile(char *file, Instruction &instruction ) {
	std::ifstream infile(file);

	if (infile.fail() || !infile.is_open()) {
		print_error("Error: Failed to open the file " ULINE + std::string(file)
		+ RULINE);
		return EXIT_FAILURE;
	}
	return readInput (instruction, infile, false);
}

/**
 * @brief Read Input from standard input.
 *
 * @param instruction
 * @return int
 */
int		readFromStdin(Instruction &instruction) {
	return readInput (instruction, std::cin, true);
}

/**
 * @brief Read input, line by line.
 *
 * @tparam _CharT
 * @tparam _Traits
 * @param instruction
 * @param input
 * @param stdin
 * @return int
 */
template<class _CharT, class _Traits>
int		readInput(Instruction &instruction,
std::basic_istream<_CharT, _Traits>& input, bool stdin)
{
	std::vector<Parser*> parsers;
	Factory factory = Factory();
	std::string line;
	int errors = 0;
	int result;

	if (stdin && instruction.interactive)
		std::cout << "> ";
	for (int line_row = 1; std::getline(input, line); line_row++) {
		if (stdin && line == ";;")
			break ;
		result = readLine(line, line_row, parsers, instruction, factory);
		if (result == EXIT_FAILURE) {
			errors++;
			if (!instruction.continue_error)
				return errors;
		} else if (stdin && instruction.interactive && result == EXIT_INSTR)
			break ;
		if (stdin && instruction.interactive)
			std::cout << "> ";
	}

	if (!instruction.interactive && errors)
		return errors;

	if (!instruction.interactive
	&& (!errors || (instruction.continue_error && stdin)))
	{
		errors += executeInstructions(parsers, instruction, factory);
	}

	if (errors == 0 || instruction.continue_error) {
		try {
			instruction.test_exit();
		} catch (std::exception &e) {
			++errors;
			print_error(e.what());
		}
	}

	return (errors);
}


int		readLine(std::string line, int line_row, std::vector<Parser *> &parsers,
Instruction &instruction, Factory &factory)
{
	Lexer lexer = Lexer();
	Parser *parser = new Parser(line);
	int result = EXIT_SUCCESS;

	try {
		lexer.lexLine(line, line_row);
		parser->parseToken(lexer.listToken, line, line_row);
		if (instruction.interactive) {
			result = execute(factory, instruction, *parser);
			delete parser;
		}
		else
			parsers.push_back(parser);

	} catch (std::exception &e) {
		print_error(e.what());
		return (EXIT_FAILURE);
	}

	return (result);
}

/**
 * @brief Go through all instructions
 *
 * @param parsers
 * @param instruction
 * @param factory
 * @return int
 */
int		executeInstructions(std::vector <Parser *> parsers,
Instruction &instruction, Factory &factory)
{
	bool execution = true;
	int result = 0;
	int errors = 0;

	for (auto &&parser : parsers) {
		try {
			if (execution)
				result = execute(factory, instruction, *parser);
			delete parser;
			if (result == EXIT_INSTR || result == EXIT_FAILURE)
				execution = false;
		} catch (std::exception &e) {
			errors++;
			print_error(e.what());
			if (!instruction.continue_error)
				return (errors);
		}
	}
	return (errors);
}

/**
 * @brief Execute instruction parsed.
 *
 * @param factory
 * @param instruction
 * @param p
 * @return true
 * @return false
 */
bool	execute(Factory &factory, Instruction &instruction, Parser &p) {
	int result = EXIT_SUCCESS;

	try {
		if (p.instructionFuncPtr == NULL)
			result = EXIT_SUCCESS;
		else if (p.getNbParams() == 0)
			result = (instruction.*p.instructionFuncPtr)(NULL);
		else
			result = (instruction.*p.instructionFuncPtr)(factory.createOperand(p.getOperantType(), p.getVal()));
	} catch (std::exception &e) {
		std::cerr << "Exception on line " << p.getLineRow() << ": " << p.getLine() << std::endl;
		throw;
	}
	return result;
}
