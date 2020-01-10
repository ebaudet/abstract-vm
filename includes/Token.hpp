/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 10:24:54 by ebaudet           #+#    #+#             */
/*   Updated: 2020/01/10 19:12:59 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>

enum eTokenType { Unknown, InstructionNoArg, InstructionArg, Type, OpenPar, ClosePar, NValue, ZValue, Space };

class Token
{
	private:
		eTokenType _type;
		std::string _value;
		size_t _pos;

	public:
		static std::vector<std::string> token_name;
		Token();
		Token( eTokenType type, std::string value, size_t pos );
		Token( Token const &src );
		~Token();
		Token &operator=( Token const &rhs );

		// Accessors
		eTokenType GetType() const;
		std::string GetValue() const;
		size_t GetPos() const;
		void SetType( eTokenType type );
		void SetPos( size_t pos );
		void SetValue( std::string value );

		friend std::ostream& operator<<(std::ostream& os, const Token& tolken);
};

std::ostream &	operator<<( std::ostream &os, Token const &tolken );
