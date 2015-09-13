/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <jwalle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/05 12:17:05 by jwalle            #+#    #+#             */
/*   Updated: 2015/08/25 16:11:02 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_malloc.h"
# include <time.h>
# include <limits.h>
# include <stdio.h>

int test2(void)
{
	char	*addr;
	int		i;

	i = 0;
	while (i < 1024)
	{
		addr = (char*)malloc(1024);
		addr[0] = 42;
		free(addr);
		i++;
	}
	return (0);
}

int test1(void)
{
	char	*addr;
	int		i;

	i = 0;
	while (i < 1024)
	{
		addr = (char*)malloc(1024);
		addr[0] = 42;
		i++;
	}
	return (0);
}

int test0(void)
{
	int		i;

	i = 0;
	while (i < 1024)
	{
		i++;
	}
	return (0);
}

int main(int ac, char **av)
{
	if (ac == 2)
	{
		if (!strcmp(av[1], "test0"))
			test0();
	}
	else
	{
		system("./print_win.sh");
		printf("Press a key to start the test.\n");
		getchar();
		printf("test 0 : \n");
		getchar();
		system("/usr/bin/time -l ./test test0");
	}


	return (0);
}
