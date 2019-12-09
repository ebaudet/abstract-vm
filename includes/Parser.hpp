/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 19:44:15 by ebaudet           #+#    #+#             */
/*   Updated: 2019/12/09 19:48:48 by ebaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(PARSER_HPP)
#define PARSER_HPP

class Parser {
    public:
        Parser();
        Parser(Parser const &src);
        virtual ~Parser();

        Parser &operator=(Parser const &rhs);

    private:
};

#endif // PARSER_HPP
