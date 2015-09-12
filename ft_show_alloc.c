/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_show_alloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <jwalle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/06 13:54:53 by jwalle            #+#    #+#             */
/*   Updated: 2015/08/08 10:59:13 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	print_mem(void *ptr, size_t size)
{
	size_t	i;
	char	*str;

	i = 0;
	str = (char *)ptr;
	while (i < size && i < 25)
	{
		if ((str[i]) > 33 && (int)(str[i]) < 127)
			ft_putchar(str[i]);
		else if (str[i] == 0)
			ft_putchar('0');
		else
			ft_putchar('.');
		ft_putchar(' ');
		i++;
	}
}

void	print_time(time_t time)
{
	char		buffer[80];
	struct tm	*info;
	info = localtime(&time);

	strftime(buffer, 80, "%x - %I:%M%p", info);
	ft_putstr(buffer);
}

void	align_size(char *str, size_t size)
{
	int	i;
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
	{
		align_size("Go", size / (M * M * M));
	}
	else if (size > M * M)
	{
		align_size("Mo", size / (M * M));
	}
	else if (size > M)
	{
		align_size("Ko", size / M);
	}
	else
	{
		align_size("o", size);
	}
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
	ft_putstr(" : ");
	print_size(size);
	ft_putstr_b(" | time of Malloc : ");
	print_time(time);
	ft_putstr_b(" | Memory : ");
	print_mem(ptr, size);
	ft_putchar('\n');
}

void	print_stuff(void *ptr, size_t size)
{	
	ft_atoi_hex(ptr);
	ft_putstr(" - ");
	ft_atoi_hex(ptr + size);
	ft_putstr(" : ");
	ft_putnbr(size);
	ft_putstr(" octets");
	ft_putchar('\n');
}

void	print_type_name(char type)
{
	if (type == TINY)
		ft_putstr("TINY");
	if (type == SMALL)
		ft_putstr("SMALL");
	if (type == LARGE)
		ft_putstr("LARGE");
}

void	swho_alloc_mem_ex(void)
{
	t_header	*header;
	t_page		*page;

	if (g_env.page)
	{
		page = g_env.page;
		while (page)
		{
			print_type_name(page->type);
			ft_putstr(" : ");
			ft_atoi_hex(page->start);
			ft_putchar('\n');
			header = page->start;
			while (header)
			{
				if (!header->free)
					print_stuff_two(header + 1, header->size, header->time);
				header = header->next;
			}
			page = page->next;
		}
	}
}

void	show_alloc_mem(void)
{
	t_header	*header;
	t_page		*page;

	if (g_env.page)
	{
		page = g_env.page;
		while (page)
		{
			print_type_name(page->type);
			ft_putstr(" : ");
			ft_atoi_hex(page->start);
			ft_putchar('\n');
			header = page->start;
			while (header)
			{
				if (!header->free)
					print_stuff_two(header + 1, header->size, header->time);
				header = header->next;
			}
			page = page->next;
		}
	}
}
