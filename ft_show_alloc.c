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

void show_tiny(void)
{
	ft_atoi_hex(g_env.tiny->start);
	ft_putstr(" - ");
	ft_atoi_hex(g_env.tiny->start + TINY_SIZE);
	ft_putstr(" : ");
	ft_putnbr(TINY_SIZE);
	ft_putstr(" octets.\n");
	ft_putchar('\n');
}

void	show_alloc_mem(void)
{
	if (g_env.tiny)
	{
		while (g_env.tiny)
		{
			ft_putstr("TINY :");
			ft_atoi_hex(g_env.tiny->start);
			ft_putchar('\n');
			while (g_env.tiny->block)
			{
				ft_atoi_hex(g_env.tiny->block->start);
				ft_putstr(" - ");
				ft_atoi_hex(g_env.tiny->block->start + g_env.tiny->block->size);
				ft_putstr(" : ");
				ft_putnbr(g_env.tiny->block->size);
				ft_putstr(" octets.\n");
				g_env.tiny->block = g_env.tiny->block->next;
			}
			g_env.tiny = g_env.tiny->next;
		}
		
	}
}
