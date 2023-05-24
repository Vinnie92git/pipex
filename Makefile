# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vinni <vinni@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/24 21:13:28 by vinni             #+#    #+#              #
#    Updated: 2023/05/24 21:15:08 by vinni            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# COLOURS #
GREEN = \033[0;32m
COLOR_OFF = \033[0m

# VARIABLES #
RM = rm -rf
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I ./include -I ./libft/include
NAME = pipex
INCLUDE = include/

# OBJECTS #
SRC = child_processes.c main.c

SRC_PATH = src/
SRCS = $(addprefix $(SRC_PATH), $(SRC))

OBJ_PATH = obj/
OBJ = $(SRC:.c=.o)
OBJS = $(addprefix $(OBJ_PATH), $(OBJ))

LIBFT_PATH = libft/
LIBFT = $(LIBFT_PATH)libft.a

# RULES #
all: $(NAME)

$(LIBFT): $(LIBFT_PATH)
	@make -C $(LIBFT_PATH)
	
$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(LIBFT)
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@echo "$(GREEN)#### pipex has been created ####$(COLOR_OFF)"

clean:
	@make -C $(LIBFT_PATH) clean
	@$(RM) $(OBJ_PATH)

fclean: clean
	@make -C $(LIBFT_PATH) fclean
	@$(RM) $(NAME) 
	@echo "$(GREEN)#### pipex cleaned successfuly ####$(COLOR_OFF)"

re: fclean all

.PHONY: all clean fclean re
