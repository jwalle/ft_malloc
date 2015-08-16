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

void	print_mem(void *ptr)
{
	int		i;
	char	*str;

	i = 0;
	str = (char *)ptr;
	while (i < 50)
	{
		if ((str[i]) > 33 && (int)(str[i]) < 127)
			ft_putchar(str[i]);
		else
			ft_putchar('.');
		ft_putchar(' ');
		i++;
	}
}

void	print_stuff(void *ptr, int size)
{
	ft_atoi_hex(ptr);
	ft_putstr(" - ");
	ft_atoi_hex(ptr + size);
	ft_putstr(" : ");
	ft_putnbr(size);
	ft_putstr(" octets");
	ft_putstr("       ");
	print_mem(ptr);
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

void	show_alloc_mem(void)
{
	void	**ptr_head;
	t_page	*page;

	if (g_env.page)
	{
		page = g_env.page;
		while (page)
		{
			print_type_name(page->type);
			ft_putstr(" : ");
			ft_atoi_hex(page->start);
			ft_putstr("       					");
			print_mem(page->start);
			ft_putchar('\n');
			ptr_head = page->start;
			while (get_mem_size(ptr_head))
			{
				if (!is_free(ptr_head))
					print_stuff((void *)(ptr_head) + 16,
								get_mem_size(ptr_head));
				ptr_head = *ptr_head;
			}
			page = page->next;
		}
	}
}
