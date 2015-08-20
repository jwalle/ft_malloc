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

void	*get_malloc(int size)
{
	t_page	*page;

	if (ft_get_type(size) == 'L')
		return (malloc_large(size));
	
	if (!g_env.page)
		g_env.page = page_push(g_env.page, ft_get_type(size));
	
	page = g_env.page;
	
	while (page->next)
	{
		
	}



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
	
	else if ((page->size + size + 16 > get_max_size(size)))
	{
		page->full = 1;
		g_env.page = page_push(g_env.page, ft_get_type(size));
		page = page->next;
	}
	//while ((size) % 16 != 0)
	//	size++;
	page->size += size + 16;
	//printf("page->size = %d\n", page->size);
	//printf("page max = %i, actual = %i\n", get_max_size(ft_get_type(size)), page->size + size + 16);
	return (block_init(page->start, size));
}
