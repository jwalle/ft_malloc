/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <jwalle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/15 18:48:42 by jwalle            #+#    #+#             */
/*   Updated: 2015/08/15 18:48:44 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

int		get_max_size(char type)
{
	if (type == TINY)
		return (TINY_SIZE_MAX);
	if (type == SMALL)
		return (SMALL_SIZE_MAX);
	if (type == LARGE)
		return (LARGE_SIZE_MAX);
	return (0);
}

void	print_error(char *str)
{
	ft_putendl(str);
	exit(1);
}

char	ft_get_type(int size)
{
	if (size < TINY_SIZE)
		return ('T');
	if (size >= TINY_SIZE && size < SMALL_SIZE)
		return ('S');
	if (size >= SMALL_SIZE)
		return ('L');
	return ('W');
}
