# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aborges <aborges@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/19 08:44:39 by aborges           #+#    #+#              #
#    Updated: 2024/10/23 10:28:28 by aborges          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
FLAGS = -Wall -Wextra -Werror
SRCS = main.c ft_aux.c ft_aux1.c ft_checker.c\
	   ft_builtins.c ft_export.c ft_unset.c\
	   ft_comands.c ft_takesignal.c ft_redirect.c\
	   ft_echo.c
LIBS = -lreadline -lncurses

OBJ = $(SRCS:.c=.o)

all: $(NAME)
$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME) $(LIBS)
%.o:%.c
	$(CC) $(FLAGS) -c $< -o $@
clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)
re: fclean all
PHONY: clean fclean re all
