# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abennar <abennar@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/11 01:09:08 by abennar           #+#    #+#              #
#    Updated: 2024/03/23 20:45:17 by abennar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRC= in_it.c parce.c  philo.c rotine.c  threads.c util_s.c utils2.c
CFLAGS = -Wall -Wextra -Werror
OBG = $(SRC:%.c=%.o)
NAME = philo


all : $(NAME)

%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBG)
	$(CC) $(CFLAGS) $^ -o $@

clean :
	rm -rf $(OBG)

fclean : clean
	rm -rf philo

re :
	$(MAKE) fclean
	$(MAKE) all
