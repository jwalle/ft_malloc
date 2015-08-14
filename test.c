/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <jwalle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/05 12:17:05 by jwalle            #+#    #+#             */
/*   Updated: 2015/08/12 22:13:03 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include <time.h>
#include <limits.h>

// av[1] = le char
// av[2] = le nombre

int main(int ac, char **av)
{
	int nb;
	int i;
	int j;
	char c;
	int r;
	char *str;
	char *str2;
	char **str3;
	srand(time(NULL));

	(void)ac;
	nb = atoi(av[2]);
	c = av[1][0];
	str = (char*)ft_malloc(nb);
	i = 0;
	while (i < nb)
	{
		str[i] = c;
		i++;
	}
	str[i] = 0;

	//show_alloc_mem();


	str2 = (char*)ft_malloc(nb);
	i = 0;
	while (i < nb)
	{
		str2[i] = c;
		i++;
	}
	str2[i] = 0;

	str3 = malloc(1000);
	i = 0;
	get_limit();
	while (i < 10)
	{
		str3[i] = (char*)ft_malloc((rand() % 200) + 100);
		i++;
	}
	i = 0;
	j = 0;	
	while (i < 10)
	{
		j = 0;
		while (j < 16)
		{
			r = (rand() % 100) + 1;
			str3[i][j] = r;
			j++;
		}
		i++;
	}

	//printf("test string = %s\n",str3[179]);
	show_alloc_mem();
	
	strcpy(str3[2], "FREEEEEE");

	free_tiny(str3[2]);

	printf("after free %s\n", str3[2]);

	i = 0;
	j = 0;	
	while (i++ < 10)
	{
		j = 5000;
		while (j < 100000)
			ft_malloc(j++);
	}

	show_alloc_mem();



	
	//printf("test string = %s\n",str3[179]);
	free(str3);


	return (0);
}
