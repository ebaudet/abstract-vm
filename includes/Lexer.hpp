/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 19:27:25 by ebaudet           #+#    #+#             */
/*   Updated: 2019/12/09 20:15:54 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(LEXER_HPP)
#define LEXER_HPP

class Lexer {
    public:
        Lexer();
        Lexer(Lexer const &src);
        virtual ~Lexer();

        Lexer &operator=(Lexer const &rhs);

    private:
};

#endif // LEXER_HPP
