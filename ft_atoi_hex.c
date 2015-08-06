/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_hex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <jwalle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/06 15:35:04 by jwalle            #+#    #+#             */
/*   Updated: 2015/08/06 18:45:57 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

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

