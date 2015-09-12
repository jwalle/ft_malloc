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

void	print_error(char *str)
{
	ft_putendl_fd(str, 2);
	exit(1);
}

size_t	get_max_size(char type, size_t size)
{
	if (type == TINY)
		return (TINY_SIZE_MAX);
	else if (type == SMALL)
		return (SMALL_SIZE_MAX);
	else if (type == LARGE)
		return (size);
	print_error("Error max size");
	return (0);
}

char	ft_get_type(size_t size)
{
	if (size < TINY_SIZE)
		return ('T');
	if (size >= TINY_SIZE && size < SMALL_SIZE)
		return ('S');
	if (size >= SMALL_SIZE)
		return ('L');
	print_error("Wrong type");
	return (0);
}
