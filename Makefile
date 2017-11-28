# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: douglas <douglas@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/07/06 18:30:14 by douglas           #+#    #+#              #
#    Updated: 2017/11/19 22:46:38 by douglas          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
FLAGS = -Wextra -Wall -Werror
LIBFT = ./libft
LIB = libft/libft.a
CMDM = ./cmds

SRC = main.c ft_error.c cmds.c lst_functions.c env.c builtin.c env_cmds.c \
		system_cmd.c do_all_cmds.c ft_strnew_e.c ft_strlen_till.c \
		replacer.c handle_signal.c

SRCO = ${SRC:%.c=%.o}

all: make_lib $(NAME)

$(NAME): $(SRCO)
	gcc -o $(NAME) $(FLAGS) $(SRC) $(LIB)

make_lib:
	@make -C $(LIBFT)

%.o: %.c
	gcc -c $(FLAGS) $< -o $@

clean:
	/bin/rm -f $(SRCO)
	make clean -C $(LIBFT)

fclean: clean
	/bin/rm -f $(NAME)
	make fclean -C $(LIBFT)

re: fclean all

.PHONY: clean fclean re all compile
