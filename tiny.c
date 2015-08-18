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

	 printf("FREE\n");
	ptr_head = (void *)(ptr) - 16;
	//size = get_mem_size((ptr_head));
	size = get_mem_size((ptr));
	//size = (int)(ptr_head) + 8;
	printf("size = %d\n", size);
	free_mem = (int *)(ptr_head) + 12;
	free_mem[0] = 1;
	munmap(ptr, size);
	ptr = NULL;
}

void	*block_init(void **ptr, int size)
{
	t_header	header;

	header = (t_header)ptr;
	while (header->next)
		header = header->next;
	header->next = size + sizeof(t_header);
	header = header->next;
	header->next = NULL;
	header->size = size;
	header->free = 0;
	return (header + sizeof(t_header));
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
	else if ((page->size + size + 16 + 1000 > get_max_size(ft_get_type(size)))
		|| (ft_get_type(size) == 'L'))
	{
		page->full = 1;
		g_env.page = page_push(g_env.page, ft_get_type(size));
		page = page->next;
	}
	while ((size) % 16 != 0)
		size++;
	page->size += size + 16;
	return (block_init(page->start, size));
}
