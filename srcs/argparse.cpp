/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argparse.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 19:45:30 by ebaudet           #+#    #+#             */
/*   Updated: 2020/01/20 19:43:17 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argparse.hpp"
#include <cstdio>
#include <getopt.h>
#include <stdlib.h>

int		short_usage ( char *file ) {
	fprintf(stderr, "Usage: %s [-civh] [FILE]\n", file);
	return (EXIT_FAILURE);
}

int		usage( char *file ) {
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

int		argparse( int ac, char **av, Instruction &instruction ) {
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
	while ( (opt = getopt_long( ac, av, "icvh", long_options, &option_index ))
	!= EOF ) {
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
				return short_usage( av[0] );
			case 'h': default:
				return (usage( av[0] ));
		}
	}
	return (EXIT_SUCCESS);
}
