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

t_block	*tiny_block_init(size_t size, void *ptr, size_t size_total)
{
	t_block *block;

	block = mmap(0, sizeof(t_block), FLAGS_PROT, FLAGS_MAP , -1, 0);
	block->size = size;
	block->start = ptr + size_total;
	block->next = NULL;
	return (block);
}

t_block	*tiny_block_fill(size_t size, void *ptr, size_t size_total, t_block *head)
{
	t_block *block;

	block = mmap(0, sizeof(t_block), FLAGS_PROT, FLAGS_MAP , -1, 0);
	block->size = size;
	block->start = ptr + size_total;
	block->next = NULL;
	head->next = block;
	return (block);
}

void	*get_tiny(size_t size)
{
	//printf("TINY\n");
	if (!g_env.tiny)
	{
		g_env.tiny = tiny_init();
		g_env.tiny->block = tiny_block_init(size, g_env.tiny->start, g_env.tiny->size);
		return(g_env.tiny->block->start);
	}

	while (g_env.tiny->next != NULL)
		g_env.tiny = g_env.tiny->next;

	if ((g_env.tiny->size + size > TINY_SIZE * 100))
	{
		g_env.tiny = tiny_fill(g_env.tiny);
		g_env.tiny->block = tiny_block_init(size, g_env.tiny->start, g_env.tiny->size);
		return(g_env.tiny->block->start);	
	}

	while(g_env.tiny->block->next != NULL)
		g_env.tiny->block = g_env.tiny->block->next;

	if (!g_env.tiny->start)
		g_env.tiny->start = mmap(0, TINY_SIZE * 100, FLAGS_PROT, FLAGS_MAP , -1, 0);

	g_env.tiny->block = tiny_block_fill(size, g_env.tiny->start, g_env.tiny->size, g_env.tiny->block);
	g_env.tiny->size += size;

	return(g_env.tiny->block->start);
}



