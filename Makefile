# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebaudet <ebaudet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/09 20:29:34 by ebaudet           #+#    #+#              #
#    Updated: 2020/01/10 10:52:12 by ebaudet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= avm
CPP		= clang++
FLAGS	= -Wall -Wextra -Werror -std=c++11
# If os != macos add pthread FLAGS
UNAME_S := $(shell uname -s)
ifneq ($(UNAME_S), Darwin)
	FLAGS += -pthread
endif
SRC_PATH	= srcs
INC_PATH	= includes
OBJ_PATH	= .obj
SRC		=	main.cpp \
			Lexer.cpp \
			Parser.cpp \
			Factory.cpp \
			Exception.cpp \
			Instruction.cpp \
			Tolken.cpp
HEAD	=	Lexer.hpp \
			Parser.hpp \
			IOperand.hpp \
			Factory.hpp \
			Exception.hpp \
			Operand.hpp \
			Instruction.hpp \
			Tolken.hpp
OBJ		= $(SRC:.cpp=.o)
HEADP	= $(addprefix $(INC_PATH)/, $(HEAD))
OBJP	= $(addprefix $(OBJ_PATH)/, $(OBJ))
INCP	= $(foreach dir, $(INC_PATH), -I $(dir))
NORMAL	= "\x1B[0m"
RED		= "\x1B[31m"
GREEN	= "\x1B[32m"
YELLOW	= "\x1B[33m"
BLUE	= "\x1B[34m"
MAGENTA	= "\x1B[35m"
CYAN	= "\x1B[36m"
WHITE	= "\x1B[37m"
BOLD	= "\e[1m"
LIGHT	= "\e[2m"
ITALIC	= "\e[3m"
ULINE	= "\e[4m"
DEBUGFLG	= -fsanitize=address -g3
DEBUGFLG	=

all: $(NAME)

$(NAME): $(OBJ_PATH) $(OBJP)
	@printf $(CYAN)"-> create program : $(NAME)\n"$(NORMAL)
	@$(CPP) $(FLAGS) -o $(NAME) $(OBJP) $(DEBUGFLG)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.cpp $(HEADP)
	@printf $(YELLOW)"-> $<\n"$(NORMAL)
	@$(CPP) $(FLAGS) -c $< -o $@ $(INCP) $(DEBUGFLG)

$(OBJ_PATH):
	@mkdir -p $(dir $(OBJP))

clean:
	@rm -rf $(OBJ_PATH)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all re clean fclean exec
