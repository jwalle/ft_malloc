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

t_page	*set_page(t_page *page, char type)
{
	page->size = 0;
	if (type == 'L')
		page->full = 1;
	else
		page->full = 0;
	page->type = type;
	page->next = NULL;
	return (page);
}

t_page	*page_push(t_page *first, char type)
{
	t_page	*tmp;

	if (!first)
	{
		first = mmap(0, sizeof(t_page), FLAGS);
		first->start = (void *)mmap(0, get_max_size(type) + 1, FLAGS);
		if (first->start == MAP_FAILED)
			print_error("MAPPING FAILED");
		first = set_page(first, type);
	}
	else
	{
		tmp = first;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = mmap(0, sizeof(t_page), FLAGS);
		tmp->next->start = (void *)mmap(0, get_max_size(type) + 1, FLAGS);
		if (tmp->next->start == MAP_FAILED)
			print_error("MAPPING FAILED");
		tmp->next = set_page(tmp->next, type);
	}
	return (first);
}
