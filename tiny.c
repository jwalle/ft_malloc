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


void	free_tiny(void *ptr)
{
	t_tiny	*tiny;
	t_block	*block;

	if (!g_env.tiny)
		return ;
	tiny = g_env.tiny;
	while (tiny)
	{
		block = tiny->block;
		while (block)
		{
			if (block->start == ptr)
			{
				//munmap(block->start, block->size);
				printf("FREEEEEEEE");
				block->start = NULL;
				block->free = 1;
				return ;
			}
			block = block->next;
		}
		tiny = tiny->next;
	}
}

t_tiny	*page_push_tiny(t_tiny *first)
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

t_block	*block_push_tiny(size_t size, void *ptr, size_t size_total, t_block *first)
{
	t_block *tmp;

	if (!first)
	{
		first = mmap(0, sizeof(t_block), FLAGS_PROT, FLAGS_MAP , -1, 0);
		first->next = NULL;
		first->size = size;
		first->free = 0;
		first->start = ptr + size_total;
	}
	else
	{
		tmp = first;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = mmap(0, sizeof(t_block), FLAGS_PROT, FLAGS_MAP , -1, 0);
		tmp->next->size = size;
		tmp->next->free = 0;
		tmp->next->start = ptr + size_total;
		tmp->next->next = NULL;
	}
	return (first);
}

void	*find_last(void *ptr)
{
	void **ptr_mem;


	while (ptr)
	{
		ptr_mem = (void *)ptr;
	}
	return ((void*)ptr_mem);
}

void	*get_next(void *ptr)
{
	return (ptr);
}

void	*block_init(void *ptr, int size)
{
	int		*size_mem;
	int		*free_mem;
	void	**ptr_mem;

	//void	*tmp2;

	//tmp = find_last(ptr);

	//tmp = tmp2;
	//tmp = ptr + 16 + size;
	//tmp = (ptr + 8);
	ptr_mem = (void *)ptr;
	ptr_mem[0] = (void *)ptr + size;
	size_mem  = (int *)(ptr + 8);
	size_mem[0] = size;
	printf("size mem = %d\n", size_mem[0]);
	free_mem = (int *)(ptr + 12);
	free_mem[0] = 0;
	printf("test = %d\n", ((int*)(ptr + 8))[0]);
	return ((void *)(ptr + 16));
}

void	*get_tiny(size_t size)
{
	t_tiny	*tiny;
	void	*ptr;
	//t_block	*block;

	if (!g_env.tiny)
		g_env.tiny = page_push_tiny(g_env.tiny);
	tiny = g_env.tiny;
	while (tiny->next != NULL)
		tiny = tiny->next;
	if ((tiny->size + size > TINY_SIZE * 100))
	{
		g_env.tiny = page_push_tiny(g_env.tiny);
		tiny = tiny->next;
	}	
	ptr = block_init(tiny->start, (int)size);	
	tiny->size += size;
	return (ptr);



	/*tiny->block = block_push_tiny(size, tiny->start, tiny->size, tiny->block);

	//fill_tiny_block();
	tiny->size += size;
	block = tiny->block;
	while (block->next != NULL)
		block = block->next;
	return(block->start);*/
}



