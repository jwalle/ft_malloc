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
		first = mmap(0, sizeof(t_page) + 1, FLAGS);
		first->start = (void *)mmap(0, get_max_size(type) * 16, FLAGS);
		if (first->start == MAP_FAILED)
			print_error("MAPPING FAILED");
		ft_bzero(first->start, get_max_size(type) * 16);
		first = set_page(first, type);
	}
	else
	{
		tmp = first;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = mmap(0, sizeof(t_page) + 1, FLAGS);
		tmp->next->start = (void *)mmap(0, get_max_size(type) * 16, FLAGS);
		if (tmp->next->start == MAP_FAILED)
			print_error("MAPPING FAILED");
		ft_bzero(tmp->next->start, get_max_size(type) * 16);
		tmp->next = set_page(tmp->next, type);
	}
	return (first);
}
