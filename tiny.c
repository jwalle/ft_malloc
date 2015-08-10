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



t_tiny	*tiny_init(void)
{
	t_tiny	*tiny;

	tiny = mmap(0, sizeof(t_tiny) + 1, FLAGS_PROT, FLAGS_MAP , -1, 0);
	tiny->start = mmap(0, TINY_SIZE * 100, FLAGS_PROT, FLAGS_MAP , -1, 0);
	tiny->size = 0;
	tiny->block = NULL;
	tiny->next = NULL;
	return (tiny);
}

t_tiny	*tiny_fill(t_tiny *head)
{
	t_tiny	*tiny;

	tiny = mmap(0, sizeof(t_tiny) + 1, FLAGS_PROT, FLAGS_MAP , -1, 0);
	tiny->start = mmap(0, TINY_SIZE * 100, FLAGS_PROT, FLAGS_MAP , -1, 0);
	head->next = tiny;
	tiny->size = 0;
	tiny->block = NULL;
	tiny->next = NULL;
	return (tiny);
}



t_block	*block_push(size_t size, void *ptr, size_t size_total, t_block *first)
{
	t_block *tmp;

	if (!first)
	{
		//printf("!push\n");
		first = mmap(0, sizeof(t_block), FLAGS_PROT, FLAGS_MAP , -1, 0);
		first->next = NULL;
		first->size = size;
		first->start = ptr + size_total;
	}
	else
	{
		printf("plop\n");
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
	//printf("TINY\n");
	t_tiny	*tiny;
	t_block	*block;

	if (!g_env.tiny)
		g_env.tiny = page_push(g_env.tiny);

	tiny = g_env.tiny;

	while (tiny->next != NULL)
		tiny = tiny->next;

	//block = NULL;
	block = tiny->block;

	if ((tiny->size + size > TINY_SIZE * 100))
	{
		tiny = page_push(tiny);
		//tiny = tiny_fill(tiny);
		//block = block_init(size, tiny->start, tiny->size, block);
		//return(block->start);
	}
	while (tiny->next != NULL)
		tiny = tiny->next;

	block = block_push(size, tiny->start, tiny->size, block);
	tiny->size += size;

	while (block->next != NULL)
		block = block->next;


	return(block->start);
}



