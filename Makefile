# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jwalle <jwalle@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/08/05 11:39:59 by jwalle            #+#    #+#              #
#    Updated: 2015/08/05 13:00:36 by jwalle           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
	
ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)
endif

NAME = libft_malloc_$(HOSTTYPE).so
LS = libft_malloc.so

CC = gcc
CFLAGS = -Wall -Werror -Wextra
SRCDIR = .
SRCO = $(SRC:.c=.o)
ODIR = ./objs/
LIB = ./libft/libft.a
INC = -I./includes -I./libft/includes
LINK = -Llibft -lft
BLU = tput setaf 4
GRN = tput setaf 2
WHT = tput setaf 7
RESET = tput sgr 0

SRC = ft_malloc.c

OBJ = $(SRC:.c=.o)
OBJS = $(addprefix $(ODIR), $(OBJ))

all: $(LIB) $(NAME)

$(NAME) : objects
	@$(BLU)
	@echo "Making $(NAME)..."
	@$(CC) -shared -o $(NAME) $(addprefix $(ODIR), $(OBJ))
	@ln -s $(NAME) $(LS)
	@$(GRN)
	@echo "Done !"
	@$(RESET)

objects:
	@$(BLU)
	@echo "making objects..."
	@$(CC) $(CFLAGS) -c $(OBJS) $(INC) -o $(SRC)
	@mkdir -p $(ODIR)
	@mv $(OBJ) $(ODIR)
	@$(GRN)
	@echo "Done !"
	@$(RESET)

$(LIB):
	@$(BLU)
	@echo "Compiling libft..."
	@make -C libft
	@$(GRN)
	@echo "Done !"
	@$(RESET)

clean:
	/bin/rm -f $(addprefix $(ODIR), $(OBJ)) 
	make -C ./libft clean

fclean:
	/bin/rm -f $(LS)
	make -C ./libft fclean
	/bin/rm -f $(NAME)

re: fclean all

test: re
	gcc $(CFLAGS) -o test test.c -L . $(NAME) $(INC) -g
