# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: muel-bak <muel-bak@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/12 11:48:44 by muel-bak          #+#    #+#              #
#    Updated: 2023/12/13 23:51:56 by muel-bak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRC_FILES = pipex.c utils.c utils1.c
OBJ_FILES = $(SRC_FILES:.c=.o)
HEADER_FILE = pipex.h

BONUS_FILES = z_pipex_bonus.c z_utils_bonus.c z_utils1_bonus.c z_z_heredo.c\
	z_z_herdoc1.c z_z_herdoc2.c

OBJ_BONUS = $(BONUS_FILES:.c=.o)
BONUS_HEADER_FILE = z_pipex_bonus.h

NAME = pipex
NAME_BONUS = pipex_bonus
all: $(NAME)

$(NAME): $(OBJ_FILES) $(HEADER_FILE)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ_FILES)

bonus: $(OBJ_BONUS) $(BONUS_HEADER_FILE)
	$(CC) $(CFLAGS) -o $(NAME_BONUS) $(OBJ_BONUS)

%.o: %.c $(HEADER_FILE)
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c $(BONUS_HEADER_FILE)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_FILES) $(OBJ_BONUS)

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)

re: fclean all

