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

int		is_free(void **ptr_head)
{
	int	*free_mem;

	free_mem = (int *)(ptr_head + 12);
	return (free_mem[0]);
}

void	print_mem(void *ptr)
{
	int		i;
	char	*str;

	i = 0;
	str = (char *)ptr;
	while (i++ < 16)
	{
		if ((str[i]) > 33 && (int)(str[i]) < 255)
			ft_putchar(str[i]);
		else
			ft_putchar('.');
		ft_putchar(' ');
	}
}

void	show_alloc_mem(void)
{
	//void	**ptr_mem;
	void	**ptr_head;
	void	*ptr;
	t_tiny	*tiny;

	if (g_env.tiny)
	{
		tiny = g_env.tiny;
		while (tiny)
		{
			ft_putstr("TINY : ");
			ft_atoi_hex(tiny->start);
			ft_putchar('\n');
			ptr_head = tiny->start;
			while (get_mem_size(ptr_head))
			{
				if (!is_free(ptr_head))
				{
					ptr = (void *)(ptr_head + 16);
					{
						ft_atoi_hex(ptr);
						ft_putstr(" - "); // oh no
						ft_atoi_hex(ptr + get_mem_size(ptr_head));
						ft_putstr(" : ");
						ft_putnbr(get_mem_size(ptr_head));
						ft_putstr(" octets");
						//ft_putstr("       ");
						//print_mem(*ptr_head);
						ft_putstr("       ");
						print_mem(ptr);
						ft_putchar('\n');
					}
				}
				ptr_head = *ptr_head;
			}
			tiny = tiny->next;
		}
	}
}
