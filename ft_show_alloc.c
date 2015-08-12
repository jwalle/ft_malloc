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

void	show_alloc_mem(void)
{
	//void	**ptr_mem;
	void	**ptr_head;
	void	*ptr;


	if (g_env.tiny)
	{
		while (g_env.tiny)
		{
			ft_putstr("TINY : ");
			ft_atoi_hex(g_env.tiny->start);
			ft_putchar('\n');
			ptr_head = g_env.tiny->start;
			while (get_mem_size(ptr_head))
			{
				ptr = (void *)(ptr_head + 16);
				{
					ft_atoi_hex(ptr);
					ft_putstr(" - ");
					ft_atoi_hex(ptr + get_mem_size(ptr_head));
					ft_putstr(" : ");
					ft_putnbr(get_mem_size(ptr_head));
					ft_putstr(" octets\n");
				}
				ptr_head = ptr_head + get_mem_size(ptr) + 16;
			}
			g_env.tiny = g_env.tiny->next;
		}
	}
}
