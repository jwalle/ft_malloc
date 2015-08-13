/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiny.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalle <jwalle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/10 14:21:41 by jwalle            #+#    #+#             */
/*   Updated: 2015/08/12 21:51:02 by jwalle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

t_tiny	*page_push_tiny(t_tiny *first)
{
	t_tiny	*tmp;
	
	if (!first)
	{
		first = mmap(0, sizeof(t_tiny) + 1, FLAGS_PROT, FLAGS_MAP , -1, 0);
		first->start = (void *)mmap(0, TINY_SIZE_MAX * 16, FLAGS_PROT, FLAGS_MAP , -1, 0);
		if (first->start == MAP_FAILED)
			printf("MAP FAILED\n");
		ft_bzero(first->start, TINY_SIZE_MAX * 16);
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
		tmp->next->start = mmap(0, TINY_SIZE_MAX * 16, FLAGS_PROT, FLAGS_MAP , -1, 0);
		if (tmp->next->start == MAP_FAILED)
			printf("MAP FAILED\n");
		ft_bzero(tmp->next->start, TINY_SIZE_MAX * 16);
		tmp->next->size = 0;
		tmp->next->block = NULL;
		tmp->next->next = NULL;
	}
	return (first);
}
/*
void	**find_next_not_free(void **ptr_head)
{
	while (get_mem_size(ptr_head) && (int)(ptr_head + 12)[0] == 1)
		ptr_head = *ptr_head;
	return (ptr_head);
}

void	**find_previous(void **ptr_head)
{
	void	**previous;
}

void	**find_last_not_free(void **ptr_head)
{

}*/

void	*ft_realloc(void *ptr, size_t size)
{
	void	**ptr_head;
	void	*tmp;
	int		size_mem;

	if (!size && ptr)
		return (get_tiny(16));
	if (!ptr)
		return(get_tiny(size));
	ptr_head = (ptr - 16 * 8);
	size_mem = get_mem_size(ptr_head);

	if (get_mem_size(*ptr_head))
	{
		tmp = mmap(0, size + 1, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
		ft_memcpy(tmp, ptr, size_mem);
		ft_bzero(ptr, size);
		ptr = get_tiny(size);
		ft_memcpy(ptr, tmp, size_mem);
		munmap(tmp, size + 1);
		return (ptr);
	}
	else
	{
		tmp = get_tiny(size);
		ft_memcpy(tmp, ptr, size);
		free_tiny(ptr);
		return (tmp);
	}
	return (NULL);
}

void	free_tiny(void *ptr)
{
	void	**ptr_head;
	int		size;
	int		*free_mem;

	ptr_head = (ptr - 16 * 8);
	size = get_mem_size((ptr_head));
	free_mem = (int *)(ptr_head + 12);
	free_mem[0] = 1;
	ft_bzero(ptr, size);
}

int		get_mem_size(void **ptr)
{
	int		*size_mem;

	size_mem = (int *)(ptr + 8);
	if (size_mem)
		return (size_mem[0]);
	return (0);
}

void	*block_init(void **ptr, int size)
{
	int		*size_mem;
	int		*free_mem;
	void	**ptr_mem;

	while (get_mem_size(ptr))
		ptr = *ptr;
	ptr_mem = (void *)ptr;
	ptr_mem[0] = (void *)(ptr + size + 16);
	size_mem = (int *)(ptr + 8);
	size_mem[0] = size;
	free_mem = (int *)(ptr + 12);
	free_mem[0] = 0;
	return ((void *)(ptr + 16));
}

void	*get_tiny(int size)
{
	t_tiny	*tiny;
	void	*ptr;

	if (!g_env.tiny)
		g_env.tiny = page_push_tiny(g_env.tiny);
	tiny = g_env.tiny;
	while (tiny->next != NULL)
		tiny = tiny->next;
	if ((tiny->size + size + 16 > (TINY_SIZE_MAX)))
	{
		g_env.tiny = page_push_tiny(g_env.tiny);
		tiny = tiny->next;
	}
	ptr = block_init(tiny->start, size);
	tiny->size += size + 16;
	printf("total size = %i\n", tiny->size);
	return (ptr);
}
