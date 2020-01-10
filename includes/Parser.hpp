/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 19:44:15 by ebaudet           #+#    #+#             */
/*   Updated: 2020/01/10 19:48:15 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(PARSER_HPP)
#define PARSER_HPP

#include <vector>
#include <sstream>

enum eInstruction { InstrPush, InstrPop, InstrDump, InstrAssert, InstrAdd,
InstrSub, InstrMul, InstrDiv, InstrMod, InstrPrint, InstrExit };

class Parser {
	public:
		static std::vector<int> instructionNbArg;
		Parser();
		Parser(Parser const &src);
		virtual ~Parser();

		Parser &operator=(Parser const &rhs);

	private:
};

#endif // PARSER_HPP
