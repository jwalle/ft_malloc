/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pages.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <jwalle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/15 20:22:45 by jwalle            #+#    #+#             */
/*   Updated: 2015/08/15 20:22:47 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	set_header(size_t size, t_header *header, void *next)
{
	header->time = time(NULL);
	header->next = next;
	header->size = size;
	header->free = 0;
}

t_page	*set_page(t_page *page, char type)
{
	page->size = 0;
	page->full = 0;
	page->type = type;
	page->next = NULL;
	page->start = page + 1;
	return (page);
}

t_page	*page_push(t_page *first, size_t size)
{
	t_page	*tmp;
	char	type;

	type = ft_get_type(size);
	// printf("size alocated = %zu\n", get_max_size(type, size) + 40);	
	if (!first)
	{
		first = (void *)mmap(0, get_max_size(type, size) + 40, FLAGS);
		if (first == MAP_FAILED)
			print_error("MAPPING FAILED");
		first = set_page(first, type);
	}
	else
	{
		tmp = first;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = (void *)mmap(0, get_max_size(type, size) + 40, FLAGS);
		if (tmp->next == MAP_FAILED)
			print_error("MAPPING FAILED");
		tmp->next = set_page(tmp->next, type);
		tmp = tmp->next;
		return (tmp);
	}
	return (first);
}
