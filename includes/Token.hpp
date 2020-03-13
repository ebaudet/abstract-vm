/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 10:24:54 by ebaudet           #+#    #+#             */
/*   Updated: 2020/03/13 18:39:46 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_HPP_
#define TOKEN_HPP_

#include <iostream>
#include <vector>

enum eTokenType { Unknown, Comment, OpenPar, ClosePar, InstructionName, Type,
ZVal, NVal, Space };

class Token
{
	private:
		// members
		eTokenType	_type;
		std::string	_value;
		size_t		_pos;
		size_t		_line;

	public:
		// Members
		static std::vector<std::string> token_name;

		// Constructors
		Token();
		Token(eTokenType type, std::string value, size_t pos, size_t line);
		Token(Token const &src);
		~Token();

		// Operators
		Token &operator=(Token const &rhs);
		friend std::ostream& operator<<(std::ostream& os, const Token& tolken);

		// Methods
		std::string toString();

		// Accessors
		eTokenType GetType() const;
		std::string GetValue() const;
		size_t GetPos() const;
		size_t GetLine() const;
		size_t GetLength() const;
		void SetType(eTokenType type);
		void SetValue(std::string value);
		void SetPos(size_t pos);
		void SetLine(size_t line);
};

#endif  // TOKEN_HPP_
