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
		ft_bzero(first->start, TINY_SIZE * 100);
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
		//ft_bzero(tmp->next->start, TINY_SIZE * 100);
		tmp->next->size = 0;
		tmp->next->block = NULL;
		tmp->next->next = NULL;
	}
	return (first);
}

void	*find_last(void *ptr, int size)
{
	int	i;
	int	*int_mem;
	//void **ptr_mem;

	i = 9;
	printf("post while last\n");
	while (i < (TINY_SIZE_MAX - size))
	{
	printf("post if last\n");
		int_mem = (int *)(ptr + i);
		if (*int_mem == 0)
		{
			int_mem[0] = size;
			printf("plodffdsfp\n");
			return (int_mem + i + 8);
		}
		i += *int_mem;
		i += 8;
	}
	return (ptr);
}

int		get_mem_size(void **ptr)
{
	printf("size_mem = %i\n", ((int *)(ptr + 8))[0]);
	printf("ptr_mem = %p\n", ((void *)(ptr + 16)));
	return (((int *)(ptr + 8))[0]);
}

void	*block_init(void **ptr, int size)
{
	int		*size_mem;
	int		*free_mem;
	void	**ptr_mem;

	//ptr = find_last(ptr, size);
	//printf("TEST INIT\n");
	
	if (get_mem_size(ptr))
	{
		while (get_mem_size(ptr))
			ptr = *ptr;
	}
	ptr_mem = (void *)ptr;
	ptr_mem[0] = (void *)(ptr + size + 16);
	size_mem = (int *)(ptr + 8);
	size_mem[0] = size;
	free_mem = (int *)(ptr + 12);
	free_mem[0] = 0;
	printf("test = %d\n", ((int*)(ptr + 8))[0]);
	return ((void *)(ptr + 16));
}

void	*get_tiny(int size)
{
	t_tiny	*tiny;
	void	*ptr;
	//printf("TEST GET TINY\n");

	if (!g_env.tiny)
		g_env.tiny = page_push_tiny(g_env.tiny);
	tiny = g_env.tiny;
	while (tiny->next != NULL)
		tiny = tiny->next;
	if ((tiny->size + size + 16 > TINY_SIZE * 100))
	{
		printf("NEXT PAGE\n");
		g_env.tiny = page_push_tiny(g_env.tiny);
		tiny = tiny->next;
	}
	ptr = block_init(tiny->start, (int)size);
	tiny->size += size + 16;
	printf("total size = %i\n", (int)tiny->size);
	return (ptr);
}
