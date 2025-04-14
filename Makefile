# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gromiti <gromiti@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/01 17:39:27 by gromiti           #+#    #+#              #
#    Updated: 2025/04/14 20:44:09 by gromiti          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = src/actions_utils.c src/actions.c src/dinner.c src/init_utils.c \
	  src/init.c src/main.c

OBJS = $(SRC:%.c=%.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror  -g
MAKEFLAGS += --silent

RM = rm -f

INC = -I./incl 
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INC)

$(NAME): $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)


all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus .c.oC = gcc
