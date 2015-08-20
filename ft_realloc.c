/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <jwalle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/15 20:02:44 by jwalle            #+#    #+#             */
/*   Updated: 2015/08/15 20:02:51 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
/*
void	*smaller_realloc(int size, int size_mem, void *ptr, void **ptr_head)
{
	int *size_head;

	ft_bzero((void *)(ptr) + size, size_mem - size);
	size_head = (int *)(ptr_head) + 8;
	size_head[0] = size;
	return (ptr);
}

void	*realloc(void *ptr, size_t size)
{
	void	**ptr_head;
	void	*tmp;
	int		size_mem;

	if (!size && ptr)
		return (get_malloc(16));
	if (!ptr)
		return (get_malloc(size));
	ptr_head = (void *)(ptr) - 16;
	size_mem = get_mem_size(ptr_head);
	if ((int)size == size_mem)
		return (ptr);
	if ((int)size < size_mem)
		return (smaller_realloc((int)size, size_mem, ptr, ptr_head));
	else if (get_mem_size(*ptr_head))
	{
		tmp = get_malloc(size);
		ft_memcpy(tmp, ptr, size_mem);
		ft_bzero(ptr, size);
		ptr = ft_memcpy(ptr, tmp, size_mem);
		return (ptr);
	}
	else
		return (ft_memcpy(get_malloc(size), ptr, size));
	return (ptr);
}
*/