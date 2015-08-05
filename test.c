/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <jwalle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/05 12:17:05 by jwalle            #+#    #+#             */
/*   Updated: 2015/08/05 15:32:12 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>

// av[1] = le char
// av[2] = le nombre

int main(int ac, char **av)
{
	int nb;
	int i;
	char c;
	char *str;

	(void)ac;
	nb = atoi(av[2]);
	c = av[1][0];
	str = (char*)mmap(0, nb + 1, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	i = 0;
	while (i < nb)
	{
		str[i] = c;
		i++;
	}
	str[i] = 0;
	printf("%s\n" ,str);
	//ft_malloc("testestest");
	return (0);
}
