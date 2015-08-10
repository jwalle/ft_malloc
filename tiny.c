/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiny.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <jwalle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/10 14:21:41 by jwalle            #+#    #+#             */
/*   Updated: 2015/08/10 14:21:55 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

t_tiny	*page_push(t_tiny *first)
{

	t_tiny	*tmp;

	if (!first)
	{
		first = mmap(0, sizeof(t_tiny) + 1, FLAGS_PROT, FLAGS_MAP , -1, 0);
		first->start = mmap(0, TINY_SIZE * 100, FLAGS_PROT, FLAGS_MAP , -1, 0);
		first->size = 0;
		first->block = NULL;
		first->next = NULL;
	}
	else
	{
		tmp = first;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = mmap(0, sizeof(t_tiny) + 1, FLAGS_PROT, FLAGS_MAP , -1, 0);
		tmp->next->start = mmap(0, TINY_SIZE * 100, FLAGS_PROT, FLAGS_MAP , -1, 0);
		tmp->next->size = 0;
		tmp->next->block = NULL;
		tmp->next->next = NULL;
	}
	return (first);
}

t_block	*block_push(size_t size, void *ptr, size_t size_total, t_block *first)
{
	t_block *tmp;

	if (!first)
	{
		first = mmap(0, sizeof(t_block), FLAGS_PROT, FLAGS_MAP , -1, 0);
		first->next = NULL;
		first->size = size;
		first->start = ptr + size_total;
	}
	else
	{
		tmp = first;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = mmap(0, sizeof(t_block), FLAGS_PROT, FLAGS_MAP , -1, 0);
		tmp->next->size = size;
		tmp->next->start = ptr + size_total;
		tmp->next->next = NULL;
	}
	return (first);
}


void	*get_tiny(size_t size)
{
	t_tiny	*tiny;
	t_block	*block;

	if (!g_env.tiny)
		g_env.tiny = page_push(g_env.tiny);
	tiny = g_env.tiny;
	while (tiny->next != NULL)
		tiny = tiny->next;
	if ((tiny->size + size > TINY_SIZE * 100))
	{
		g_env.tiny = page_push(g_env.tiny);
		tiny = tiny->next;
	}
	tiny->block = block_push(size, tiny->start, tiny->size, tiny->block);
	tiny->size += size;
	block = tiny->block;
	while (block->next != NULL)
		block = block->next;
	return(block->start);
}



