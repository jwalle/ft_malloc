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

void	*block_init(void *ptr, size_t size)
{
	t_header	*header;
	char		*next;

	header = ptr;
	while (header->next)
	{
		if (header->free && header->size >= size)
		{
			set_header(size, header, header->next);
			return (header + 1);
		}
		header = header->next;
	}
	if (header->size)
	{
		next = (char *)(header) + header->size + 32;
		header->next = (void *)next;
		header = header->next;
	}
	set_header(size, header, NULL);
	return (header + 1);
}

void	*malloc_large(size_t size)
{
	t_page *page;

	page = page_push(g_env.page, size);
	if (!g_env.page)
		g_env.page = page;
	page->size = size + 32;
	return (block_init(page->start, size));
}

void	*first_page(size_t size)
{
	t_page	*page;

	g_env.page = page_push(g_env.page, size);
	page = g_env.page;
	page->size += size + 32;
	return (block_init(page->start, size));
}

t_page	*find_page(size_t size)
{
	char	type;
	t_page	*page;

	type = ft_get_type(size);
	page = g_env.page;
	while (page)
	{
		if (page->type == type && !page->full)
		{
			if ((page->size + size + 32) > get_max_size(type, size))
			{
				page->full = 1;
				return (NULL);
			}
			else
			{
				page->size += size + 32;
				return (page);
			}
		}
		page = page->next;
	}
	return (NULL);
}

void	*get_malloc(size_t size)
{
	t_page	*page;

	if (ft_get_type(size) == 'L')
		return (malloc_large(size));
	else if (!g_env.page)
		return (first_page(size));
	else if ((page = find_page(size)) != NULL)
		return (block_init(page->start, size));
	page = page_push(g_env.page, size);
	page->size += size + 32;
	return (block_init(page->start, size));
}
