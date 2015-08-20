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

void	*block_init(void *ptr, int size)
{
	t_header	*header;
	char		*next;

	header = ptr;
	while (header->next)
			header = header->next;
	if (header->size)
	{
		next = (char *)(header) + header->size + 16;
		header->next = (void *)next;
		header = header->next;
	}
	header->next = NULL;
	header->size = size;
	header->free = 0;
	return (header + 1);
}

void	*malloc_large(int size)
{
	t_page *page;

	g_env.page = page_push(g_env.page, ft_get_type(size));
	page = g_env.page;
	while (page->next)
		page = page->next;
	return (block_init(page->start, size));
}

void	*first_page(int size)
{
	t_page	*page;

	g_env.page = page_push(g_env.page, ft_get_type(size));
	page = g_env.page;
	page->size += size + 16;
	return (block_init(page->start, size));
}

void	*get_malloc(int size)
{
	t_page	*page;

	if (ft_get_type(size) == 'L')
		return (malloc_large(size));
	if (!g_env.page)
		return (first_page(size));
	page = g_env.page;
	while (page->next)
	{
		if (page->type == ft_get_type(size) && !page->full)
		{
			if ((page->size + size + 16) > get_max_size(size))
				page->full = 1;
			else
			{
				page->size += size + 16;
				return (block_init(page->start, size));
			}
		}
		page = page->next;
	}
	g_env.page = page_push(g_env.page, ft_get_type(size));
	page = g_env.page;
	while (page->next)
		page = page->next;
	page->size += size + 16;
	return (block_init(page->start, size));
}
