/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Color.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 16:45:36 by ebaudet           #+#    #+#             */
/*   Updated: 2020/01/21 13:10:18 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_HPP_
#define COLOR_HPP_

#define EOC	"\x1B[0m"
#define RED  "\x1B[31m"
#define GREEN  "\x1B[32m"
#define YELLOW	"\x1B[33m"
#define BLUE  "\x1B[34m"
#define MAGENTA  "\x1B[35m"
#define CYAN  "\x1B[36m"
#define WHITE  "\x1B[37m"
#define F_RED  "\x1B[41m"
#define F_GREEN  "\x1B[42m"
#define F_YELLOW	"\x1B[43m"
#define F_BLUE  "\x1B[44m"
#define F_MAGENTA  "\x1B[45m"
#define F_CYAN  "\x1B[46m"
#define F_WHITE  "\x1B[47m"
#define CLEAR "\033[H\033[2J"
#define BOLD "\e[1m"
#define RBOLD "\e[21m"
#define LIGHT "\e[2m"
#define RLIGHT "\e[22m"
#define ITALIC "\e[3m"
#define RITALIC "\e[23m"
#define ULINE "\e[4m"
#define RULINE "\e[24m"

#endif  // COLOR_HPP_
