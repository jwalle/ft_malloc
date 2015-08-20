# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lchenut <lchenut@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/19 14:14:39 by lchenut           #+#    #+#              #
#    Updated: 2015/05/06 16:32:49 by lchenut          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC         = gcc

OBJS_DIR   = ..
SRCS	   = test0.c		\
			 test1.c		\
			 test2.c		\
			 test3.c		\
			 test3bis.c		\
			 test4.c		\
			 test5.c		\
			 test6.c		\
			 test7.c
INCS	   = .

OBJS       = $(addprefix $(OBJS_DIR)/, $(notdir $(SRCS:.c=)))

.PHONY: all clean fclean re

all: $(OBJS)

$(OBJS_DIR)/%: %.c
	$(CC) -I$(INCS)/ $< -o $@ -L$(OBJS_DIR) -lft_malloc
	@echo "\033[A\033[K\033[A"

clean:
	rm -f $(OBJS)
	@echo "\033[4;1;34mClean OBJS       >>\033[0m     \033[1;32mok.\033[0m"

$(OBJS_DIR):

$(OBJS): | $(OBJS_DIR)

re: clean all
