/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argparse.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 19:45:30 by ebaudet           #+#    #+#             */
/*   Updated: 2020/03/13 20:47:59 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdio>
#include <getopt.h>
#include <stdlib.h>

#include "argparse.hpp"

/**
 * @brief Print short usage where error usage of program.
 *
 * @param file
 * @return int
 */
int		short_usage (char *file) {
	fprintf(stderr, "Usage: %s [-civh] [FILE]\n", file);
	return (EXIT_FAILURE);
}

/**
 * @brief Print usage for program.
 *
 * @param file
 * @return int
 */
int		usage(char *file) {
	short_usage(file);
	fprintf(stderr, "\n"
					"Abstract VM : Virtual Machine that can interpret programs "
					"written in basic assembly language.\n"
					"\n"
					"optional arguments:\n"
					"  -c, --continue	Continue after first error\n"
					"  -i, --interactive	Interactive mode for entry. Directl"
					"y execute the command without expecting \n"
					"  -v, --verbose		Verbose mode\n"
					"  -h, --help, --usage	Show this help message\n"
					);
	return (EXIT_FAILURE);
}

/**
 * @brief Parsing of the arguments of the program.
 * * interactive : Continue after first error
 * * continue : Interactive mode for entry. Directly execute the command without
 *              expecting
 * * verbose : Verbose mode
 * * help / usage : Show this help message
 *
 * @param ac
 * @param av
 * @param instruction
 * @return int
 */
int		argparse(int ac, char **av, Instruction &instruction) {
	struct option long_options[] = {
		{"interactive",	no_argument, 0, 'i'},
		{"continue",	no_argument, 0, 'c'},
		{"verbose",		no_argument, 0, 'v'},
		{"help",		no_argument, 0, 'h'},
		{"usage",		no_argument, 0, 'h'},
		{0, 0, 0, 0}
	};
	int opt;
	int option_index = 0;
	while ((opt = getopt_long(ac, av, "icvh", long_options, &option_index))
	!= EOF) {
		switch (opt) {
			case 'i':
				instruction.interactive = true;
				break;
			case 'v':
				instruction.verbose = true;
				break;
			case 'c':
				instruction.continue_error = true;
				break;
			case '?':
				return short_usage(av[0]);
			case 'h': default:
				return (usage(av[0]));
		}
	}
	return (EXIT_SUCCESS);
}
