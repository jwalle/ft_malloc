/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem_ex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/12 18:45:09 by jwalle            #+#    #+#             */
/*   Updated: 2015/09/12 18:45:12 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	print_time(time_t time)
{
	char		buffer[80];
	struct tm	*info;

	info = localtime(&time);
	strftime(buffer, 80, "%x - %I:%M:%S%p", info);
	ft_putstr(buffer);
}

void	align_size(char *str, size_t size)
{
	int		i;
	size_t	temp;

	i = 0;
	temp = size;
	while (size)
	{
		i++;
		size /= 10;
	}
	i = 4 - i;
	while (i--)
		ft_putstr(" ");
	ft_putnbr(temp);
	ft_putstr(" ");
	ft_putstr(str);
}

void	print_size(size_t size)
{
	if (size > M * M * M)
		align_size("Go", size / (M * M * M));
	else if (size > M * M)
		align_size("Mo", size / (M * M));
	else if (size > M)
		align_size("Ko", size / M);
	else
		align_size("o", size);
}

void	ft_putstr_b(char *str)
{
	ft_putstr(BOLD);
	ft_putstr(str);
	ft_putstr(RESET);
}

void	print_stuff_two(void *ptr, size_t size, time_t time)
{
	ft_atoi_hex(ptr);
	ft_putstr(" - ");
	ft_atoi_hex(ptr + size);
	ft_putstr(" :");
	print_size(size);
	ft_putstr_b(" | time of Malloc : ");
	print_time(time);
	ft_putstr_b(" | Memory : ");
	print_mem(ptr, size);
	ft_putchar('\n');
}
