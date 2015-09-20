# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jwalle <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/09/20 17:39:34 by jwalle            #+#    #+#              #
#    Updated: 2015/09/20 17:44:10 by jwalle           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LN = -I../libft/libft.h

all :
	make -C ../ re
	cp ../*.so .
	gcc test0.c -o test0
	gcc test1.c -o test1
	gcc test2.c -o test2
	gcc test3.c -o test3
	gcc test3bis.c -o test3bis
	gcc test4.c -o test4
	gcc test5.c -o test5 -L. -lft_malloc

clean :
	rm -rf test0 test1 test2 test3 test3bis test4 test5
	rm -rf *.so
