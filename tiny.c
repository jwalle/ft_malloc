/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiny.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <jwalle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/10 14:21:41 by jwalle            #+#    #+#             */
/*   Updated: 2015/08/12 21:51:02 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	free(void *ptr)
{
	void	**ptr_head;
	int		size;
	int		*free_mem;

	ptr_head = (ptr - 16);
	size = get_mem_size((ptr_head));
	free_mem = (int *)(ptr_head + 12);
	free_mem[0] = 1;
	ft_bzero(ptr, size);
	munmap(ptr, size);
	ptr = NULL;
}

void	*block_init(void **ptr, int size)
{
	int		*size_mem;
	int		*free_mem;
	void	**ptr_mem;

	while (get_mem_size(ptr))
		ptr = *ptr;
	ptr_mem = (void *)ptr;
	ptr_mem[0] = (void *)(ptr + (size + 16) / 8);
	size_mem = (int *)(ptr + 8);
	size_mem[0] = size;
	free_mem = (int *)(ptr + 12);
	free_mem[0] = 0;
	return ((void *)(ptr + 16));
}

void	*get_malloc(int size)
{
	t_page	*page;

	if (!g_env.page)
		g_env.page = page_push(g_env.page, ft_get_type(size));
	page = g_env.page;
	while (page->next != NULL)
	{
		if ((page->type != ft_get_type(size)) || page->full)
			page = page->next;
		break ;
	}
	if (page->type != ft_get_type(size))
	{
		g_env.page = page_push(g_env.page, ft_get_type(size));
		page = page->next;
	}
	else if ((page->size + size + 16 > get_max_size(ft_get_type(size)))
		|| (ft_get_type(size) == 'L'))
	{
		page->full = 1;
		g_env.page = page_push(g_env.page, ft_get_type(size));
		page = page->next;
	}
	page->size += size + 16;
	return (block_init(page->start, size));
}
