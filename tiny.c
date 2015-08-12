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


t_tiny	*page_push_tiny(t_tiny *first)
{
	t_tiny	*tmp;

	if (!first)
	{
		first = mmap(0, sizeof(t_tiny) + 1, FLAGS_PROT, FLAGS_MAP , -1, 0);
		first->start = mmap(0, TINY_SIZE * 100, FLAGS_PROT, FLAGS_MAP , -1, 0);
		ft_bzero(first->start, TINY_SIZE * 100);
		first->size = 0;
		first->next = NULL;
	}
	else
	{
		tmp = first;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = mmap(0, sizeof(t_tiny) + 1, FLAGS_PROT, FLAGS_MAP , -1, 0);
		tmp->next->start = mmap(0, TINY_SIZE * 100, FLAGS_PROT, FLAGS_MAP , -1, 0);
		ft_bzero(tmp->next->start, TINY_SIZE * 100);
		tmp->next->size = 0;
		tmp->next->next = NULL;
	}
	return (first);
}

void	**find_last(void **ptr_head, int size)
{
	int	i;
	int	*int_mem;
	//void **ptr_mem;

	i = 9;
	printf("post while last\n");
	while (i < (TINY_SIZE_MAX - size))
	{
	printf("post if last\n");
		int_mem = (int *)(ptr_head + i);
		if (*int_mem == 0)
		{
			int_mem[0] = size;
			printf("plodffdsfp\n");
			ptr_head = (void *)(int_mem + i + 8);
			return (ptr_head);
		}
		i += *int_mem;
		i += 8;
	}
	return (ptr_head);
}

void	*get_next(void **ptr)
{
	return (*ptr);
}

void	*get_ptr(void *ptr)
{
	return (ptr + 16);
}

int		get_mem_size(void *ptr)
{
	//printf("get mem size = %d\n", ((int*)(ptr + 8))[0]);
	return (((int*)(ptr + 8))[0]);
}

void	*block_init(void **ptr_head, int size)
{
	int		*size_mem;
	int		*free_mem;
	void	*ptr_mem;

	ptr_head = find_last(ptr_head, size);
	ptr_mem = *ptr_head;
	ptr_mem = (void *)(ptr_mem + size + 16);
	size_mem = (int *)(ptr_mem + 8);
	size_mem[0] = size;
	printf("size mem = %d\n", size_mem[0]);
	free_mem = (int *)(ptr_head + 12);
	free_mem[0] = 0;
	printf("test = %d\n", ((int*)(ptr_head + 8))[0]);
	return ((void *)(ptr_head + 16));
}

void	*get_tiny(size_t size)
{
	t_tiny	*tiny;
	void	*ptr;

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
}



