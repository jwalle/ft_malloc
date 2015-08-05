# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jwalle <jwalle@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/08/05 11:39:59 by jwalle            #+#    #+#              #
#    Updated: 2015/08/05 15:32:35 by jwalle           ###   ########.fr        #
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

$(NAME) : $(OBJS)
	@$(BLU)
	@echo "Making $(NAME)..."
	@$(CC) -shared -o $(NAME) $^ $(LINK) 
	@ln -s $(NAME) $(LS)
	@$(GRN)
	@echo "Done !"
	@$(RESET)

$(OBJS): $(SRC)
	@mkdir -p $(ODIR)
	@$(BLU)
	@echo "making objects..."
	@$(CC) $(CFLAGS) -c $^ $(INC) -o $@
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
	/bin/rm -rf $(LS)
	make -C ./libft fclean
	/bin/rm -rf $(NAME)
	/bin/rm -rf test

re: fclean all

test: re
	gcc $(CFLAGS) -o test test.c $(LINK) $(NAME) $(INC) -g
