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

// av[1] = le char
// av[2] = le nombre

int main(int ac, char **av)
{
	int nb;
	int i;
	char c;
	char *str;
	char *str2;
	char **str3;

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
	while (i < 180)
	{
		str3[i] = (char*)ft_malloc(nb);
		i++;
	}
	i = 0;	
	while (i < nb)
	{
		str3[179][i] = c;
		i++;
	}
	printf("test string = %s\n",str3[179]);
	show_alloc_mem();
	free_tiny(str3[179]);
	printf("FREE\n");
	//printf("test string = %s\n",str3[179]);
	free(str3);


	return (0);
}
