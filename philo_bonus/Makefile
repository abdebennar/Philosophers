# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abennar <abennar@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/15 00:54:37 by abennar           #+#    #+#              #
#    Updated: 2024/03/22 22:36:39 by abennar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRC= in_it.c parce.c philo.c proc.c util_s.c
CFLAGS = -Wall -Wextra -Werror
OBG = $(SRC:%.c=%.o)
NAME = philo_bonus

all : $(NAME)

%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBG)
	$(CC) $(CFLAGS) $^ -o $@

clean :
	rm -rf $(OBG)

fclean : 
	$(MAKE) clean
	rm -rf $(NAME)

re :
	$(MAKE) fclean
	$(MAKE) all