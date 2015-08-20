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
	int			i;

	i = 0;
	header = ptr;
	while (header->next)
	{
			i++;
			header = header->next;
	}
	if (i < 1)
	{
		printf("lpop\n");
		next = (char *)(header) + 16;
		header->next = (void *)next;
	}
	else
	{
		next = (char *)(header) + header->size + 16;
		header->next = (void *)next;
		header = header->next;
		return (header + 1);
	}
	header->next = NULL;
	header->size = size;
	header->free = 0;
	return (header + 1);
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
	//while ((size) % 16 != 0)
	//	size++;
	page->size += size + 16;
	//printf("page->size = %d\n", page->size);
	return (block_init(page->start, size));
}
