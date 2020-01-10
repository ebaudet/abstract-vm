/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tolken.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 10:24:54 by ebaudet           #+#    #+#             */
/*   Updated: 2020/01/10 12:39:03 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>

enum eTokenType { Unknown, InstructionNoArg, InstructionArg, Type, OpenPar, ClosePar, NValue, ZValue };

class Tolken
{
	private:
		eTokenType _type;
		std::string _value;
		size_t _pos;

	public:
		static std::vector<std::string> token_name;

		Tolken( eTokenType type, std::string value, size_t pos );
		Tolken( Tolken const &src );
		~Tolken();
		Tolken &operator=( Tolken const &rhs );

		// Accessors
		eTokenType GetType() const;
		std::string GetValue() const;
		size_t GetPos() const;
		void SetType( eTokenType type );
		void SetPos( size_t pos );
		void SetValue( std::string value );

		friend std::ostream& operator<<(std::ostream& os, const Tolken& tolken);
};

std::ostream &	operator<<( std::ostream &os, Tolken const &tolken );
