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
#define SHELLSCRIPT "\
#/bin/bash \n \
echo \"hello\" \
"

void	print_windows(void)
{

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

int main(void)
{
	system("./print_win.sh");
	test1();
	return (0);
}
