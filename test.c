/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <jwalle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/05 12:17:05 by jwalle            #+#    #+#             */
/*   Updated: 2015/08/16 16:10:56 by jwalle           ###   ########.fr       */
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
	//int i;
	//int j;
	char c;
	//int r;
	//char *str;
	//char *str2;
	//char **str3;
	//char *str4;

	srand(time(NULL));

	(void)ac;
	
	nb = atoi(av[2]);
	
	c = av[1][0];
	/*str = (char*)malloc(nb);
	i = 0;
	while (i < nb)
	{
		str[i] = c;
		i++;
	}
	str[i] = 0;

	show_alloc_mem();


	str2 = (char*)malloc(nb);
	i = 0;
	while (i < nb)
	{
		str2[i] = c;
		i++;
	}
	str2[i] = 0;

	str3 = malloc(100000);
	i = 0;
	get_limit();
	while (i < 10)
	{
		str3[i] = (char*)malloc((rand() % 100) + 16);
		i++;
	}
	i = 0;
	j = 0;	
	while (i < 10)
	{
		j = 0;
		while (j < 16)
		{
			r = (rand() % 126) + 1;
			str3[i][j] = r;
			j++;
		}
		i++;
	}
	*/
	//printf("test string = %s\n",str3[179]);
	//show_alloc_mem();
	
	//strcpy(str3[2], "FREEEEEE");

	//free(str3[2]);

	//printf("after free %s\n", str3[2]);

	/*i = 0;
	j = 0;	
	while (i++ < 10)
	{
		j = 500;
		while (j < 1000)
			ft_malloc(j = j + 50);
	}*/

	// char *real;

	// real = malloc(10);
	
	// malloc(10);

	// malloc(1);

	// ft_strcpy(real, "COUCOUCOU");

	// printf("real 1 = %s\n", real);

	// printf("MEGA MALLOC\n");
	// str4 = malloc(100000);
	
	// ft_strcpy(str4, "PLOP LARGE PLOP");

	// show_alloc_mem();


	//realloc(real, 5);

	//printf("real 2 = %s\n", real);

	//show_alloc_mem();
	
	//printf("test string = %s\n",str3[179]);

	//free(str3);

	int i = 0;
	//char **str;
	//str = malloc(100);
	char *str;
	// char **str2;

	str = malloc(10);
	//str2 = malloc(10);
	ft_strcpy(str, "COUCOU");
	
	puts(str);
	while (i++ < 8)
{
		malloc(nb);
		//str2[i] = malloc(10);
		//ft_strcpy(str2[i], "COUCOUC");
	}
	show_alloc_mem();
	free(str);
	show_alloc_mem();
	puts(str);

	return (0);
}
