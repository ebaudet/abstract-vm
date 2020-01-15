/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argparse.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 19:45:52 by ebaudet           #+#    #+#             */
/*   Updated: 2020/01/15 22:21:46 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGPARSE_HPP_
#define ARGPARSE_HPP_

#include "Instruction.hpp"

int		short_usage ( char *file );
int		usage( char *file );
int		argparse( int ac, char **av, Instruction &instruction );

#endif  // ARGPARSE_HPP_
