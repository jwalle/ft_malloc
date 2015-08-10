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

t_block	*block_init(size_t size, void *ptr, size_t size_total, t_block *head)
{
	t_block *block;

	block = mmap(0, sizeof(t_block), FLAGS_PROT, FLAGS_MAP , -1, 0);
	block->next = head;
	head = block;
	block->size = size;
	block->start = ptr + size_total;
	return (block);
}

t_block	*block_fill(size_t size, void *ptr, size_t size_total, t_block *cur)
{
	t_block *block;

	block = mmap(0, sizeof(t_block), FLAGS_PROT, FLAGS_MAP , -1, 0);
	cur->next = block;
	block->next = NULL;
	block->size = size;
	block->start = ptr + size_total;
	return (block);
}

void	*get_tiny(size_t size)
{
	printf("TINY\n");
	t_tiny	*tiny;
	t_block	*block;

	if (!g_env.tiny)
		g_env.tiny = tiny_init();

	tiny = g_env.tiny;

	while (tiny->next != NULL)
		tiny = tiny->next;

	block = tiny->block;

	if ((tiny->size + size > TINY_SIZE * 100))
	{
		tiny = tiny_fill(tiny);
		block = block_init(size, tiny->start, tiny->size, block);
		return(block->start);	
	}

	while (block && block->next != NULL)
		block = block->next;

	printf("post next\n");

	block = block_fill(size, tiny->start, tiny->size, block);
	tiny->size += size;

	printf("PLPOPLOP\n");


	return(block->start);
}



