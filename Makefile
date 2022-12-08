# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gissao-m <gissao-m@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/05 11:27:31 by gissao-m          #+#    #+#              #
#    Updated: 2022/12/07 15:58:26 by gissao-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell

CC = gcc
INCLUDE = -I ./include/
CFLAGS = -g $(INCLUDE) -Wall -Wextra -Werror
CREADLINE = -lreadline

RM = rm -rf

LIBFT = ./libft/libft.a
PATH_SRC = ./src/
PATH_LIBFT = $(PATH_INCLUDE)libft/
PATH_MAIN = $(PATH_SRC)main/
PATH_OBJS = ./objs/

SRC =	$(PATH_MAIN)main.c\
		$(PATH_SRC)parse.c\
		$(PATH_SRC)parse_utils.c\
		$(PATH_SRC)parse_cond.c\
		$(PATH_SRC)red_error.c\
		$(PATH_SRC)input.c\
		$(PATH_SRC)output.c\
		$(PATH_SRC)command.c\
		$(PATH_SRC)pwd.c\
		$(PATH_SRC)echo.c\
		$(PATH_SRC)exit.c\
		$(PATH_SRC)free.c\

OBJS = $(patsubst $(PATH_SRC)%.c, $(PATH_OBJS)%.o, $(SRC))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS)  $(OBJS) -o $(NAME) -L ./libft -lft $(CREADLINE)

$(PATH_OBJS)%.o: $(PATH_SRC)%.c
	@mkdir -p $(PATH_OBJS)
	@mkdir -p $(PATH_OBJS)libft/
	@mkdir -p $(PATH_OBJS)main/
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C ./libft

clean:
	$(RM) ./objs

fclean: clean
	$(RM) $(NAME) 
	make fclean -C ./libft

install: 
	@echo "Installing dependencies"
	@sudo apt-get install libreadline-dev

re: fclean all

.PHONY: all $(PATH_OBJS) clean fclean re