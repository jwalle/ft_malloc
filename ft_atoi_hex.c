/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_hex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <jwalle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/06 15:35:04 by jwalle            #+#    #+#             */
/*   Updated: 2015/08/06 16:26:10 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void ft_atoi_hex(void *ptr)
{
	unsigned long long	adress;
	char				str[10];
	char				*base;
	int					i;

	ft_memset(str, 0, 10);
	i = 8;
	base = "0123456789ABCDEF";
	adress = (unsigned long long)ptr;
	while(adress)
	{
		str[i] = base[adress % 16];
		adress = adress / 16;
		i--;
	}
	ft_putstr("0x");
	ft_putstr(str);
}
