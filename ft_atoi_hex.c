/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_hex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <jwalle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/06 15:35:04 by jwalle            #+#    #+#             */
/*   Updated: 2015/08/07 14:47:15 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void ft_atoi_hex(void *ptr)
{
	char				*base;
	unsigned long long address;
	char			hex[10];
	int					i;

	base = "0123456789abcdef";
	address = (unsigned long long)ptr;	
	ft_bzero(hex, 10);
	i = 8;
	while (address)
	{
		hex[i] = base[address % 16];
		address = address / 16;
		i--;
	}
	ft_putstr("0x");
	ft_putstr(hex);
}

/*
void get_adress(void)
{
	char *address;

	address = malloc(10);
	
}

void ft_atoi_hex(void *ptr, unsigned long long address)
{
	char				*base;

	base = "0123456789ABCDEF";
	if (address == 0 && ptr != NULL)
	{
		address = (unsigned long long)ptr;
		ft_putstr("0x");
	}
	if (address < 16)
		ft_putchar(base[address % 16]);
	else if (address >= 16)
	{
		ft_atoi_hex(NULL , address / 16);
		ft_atoi_hex(NULL , address % 16);
	}
}
*/
